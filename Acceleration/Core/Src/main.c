// Choose whether uploading for sensor or vibration
const int isMaster = 0;
/* Choose which to determine which sender node is being used
 * 0 -> GY521
 * 1 -> Vibration
 * 2 -> Moisture
 * */
const int sender = 0;

#include "main.h"

// Include clock configuration
#include "rcc.h"
#include "delay.h"

// Include communication components
#include "lora.h"
#include "ESPDataLogger.h"
#include "usart.h"
//#include "liquidcrystal_i2c.h"

// Include sensor components
#include "gy521.h"
#include "vibration.h"
#include "moisture.h"


// Include library functions
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

LoRa myLoRa;

//#define WIFI_SSID "EEE192-429"
//#define WIFI_PASSWD "EEE192_Room429"
#define WIFI_SSID "TESTING"
#define WIFI_PASSWD "12345678"
#define MASTER_THINGSPEAK_API_KEY "R748GIFD3RXHFQDD"
#define VIBRATION_THINGSPEAK_API_KEY "TZ53H0ZH5J9OIEDY"
#define MOISTURE_THINGSPEAK_API_KEY "VQ03QYWSY4SBP6AY"
#define ACCEGYRO_THINGSPEAK_API_KEY "SFITOT4DQFFNK9IF"
#define NUMBER_OF_FIELDS 5

const float moisture_bias = 20.01f;
const float vibration_bias = 20.00f;
const float vibration_threshold = 0.0f;
const float moisture_threshold = 0.0f;

// Main functions
void initializeSystem();
void doMasterNode();
void doSensorNode();

// Utility functions
void floatToString(float value, char* buffer, int precision);
int compareString(char* message, char* compareTo);
void removeFirstChar(char* str);
void IWDG_Init(void);
void IWDG_Refresh(void);

int main(){
	initializeSystem();
	while(1){
		isMaster ? doMasterNode() : doSensorNode();
	}
	return 1;
}

void doMasterNode(){

	char* field_values [5] = {"0.00", "0.00", "0.00", "0.00", "0.00"};
	uint8_t received_data[10]; // Data buffer for data received from LoRa
	uint8_t packet_size = 0; // Size of packet received from LoRa

	// Poll data from the sensors
	for (int i=0; i < 5; i++){
		int correct_packet_received = 0;
		startTimer();
		while(doDelay || correct_packet_received){
			packet_size = LoRa_receive(&myLoRa, received_data, 5);
			IWDG_Refresh();
			// if DATA exists, parse it and check if sender_id matches what we want
			if (packet_size >= 5){
				char sender_id[1];
				if (i == 0){
					sender_id[0] = 'X';
					int is_same = received_data[0] == sender_id[0];
					if (is_same){ // data packet matches ID
						char parsed_data[10 + 1];
						memcpy(parsed_data, received_data, 10);
						parsed_data[10] = '\0';
						removeFirstChar(parsed_data);
						field_values[0] = parsed_data;
						correct_packet_received = 1;
						break;
					}

				}
				else if (i == 1){
					sender_id[0] = 'Y';
					int is_same = received_data[0] == sender_id[0];
					if (is_same){ // data packet matches ID
						char parsed_data[10 + 1];
						memcpy(parsed_data, received_data, 10);
						parsed_data[10] = '\0';
						removeFirstChar(parsed_data);
						field_values[1] = parsed_data;
						correct_packet_received = 1;
						break;
					}

				}
				else if (i == 2){
					sender_id[0] = 'Z';
					int is_same = received_data[0] == sender_id[0];
					if (is_same){ // data packet matches ID
						char parsed_data[10 + 1];
						memcpy(parsed_data, received_data, 10);
						parsed_data[10] = '\0';
						removeFirstChar(parsed_data);
						field_values[2] = parsed_data;
						correct_packet_received = 1;
						break;
					}

				}
				else if (i == 3){
					sender_id[0] = 'M';
					int is_same = received_data[0] == sender_id[0];
					if (is_same){ // data packet matches ID
						char parsed_data[10 + 1];
						memcpy(parsed_data, received_data, 10);
						parsed_data[10] = '\0';
						removeFirstChar(parsed_data);
						field_values[3] = parsed_data;
						correct_packet_received = 1;
						break;
					}
				}
				else if (i == 4){
					sender_id[0] = 'V';
					int is_same = received_data[0] == sender_id[0];
					if (is_same){ // data packet matches ID
						char parsed_data[10 + 1];
						memcpy(parsed_data, received_data, 10);
						parsed_data[10] = '\0';
						removeFirstChar(parsed_data);
						field_values[4] = parsed_data;
						correct_packet_received = 1;
						break;
					}
				}


			}
			HAL_Delay(500);
		}
	}
	// Display to LCD
	// insert function for LCD here

	// Send all polled data to Master channel
	ESP_Send_Multi(MASTER_THINGSPEAK_API_KEY, 5, field_values);
	IWDG_Refresh();
}

void doSensorNode(){
	IWDG_Refresh();

	int adc_value;
	char lora_send[10];
	char sensor_data_buffer[6];

	switch(sender){
		case 0:
			// Read sensor value and prepare it for sending
			GY521_Read_Accel();
			char Ax_char[6], Ay_char[6], Az_char[6];
			floatToString(Ax, Ax_char, 2);
			floatToString(Ay, Ay_char, 2);
			floatToString(Az, Az_char, 2);
			char* acceleration_values[3];
			acceleration_values[0] = Ax_char;
			acceleration_values[1] = Ay_char;
			acceleration_values[2] = Az_char;

			// Upload data to cloud
			ESP_Send_Multi(ACCEGYRO_THINGSPEAK_API_KEY, 3, acceleration_values);
			IWDG_Refresh();
//			HAL_Delay(15000);

			// Transmit data to Master
			char loraX[10], loraY[10], loraZ[10];
			sprintf(loraX, "%c%s", 'X',Ax_char);
			sprintf(loraY, "%c%s", 'Y',Ay_char);
			sprintf(loraZ, "%c%s", 'Z',Az_char);
			LoRa_transmit(&myLoRa, (uint8_t*)loraX, 6, 100);
			LoRa_transmit(&myLoRa, (uint8_t*)loraY, 6, 100);
			LoRa_transmit(&myLoRa, (uint8_t*)loraZ, 6, 100);
			IWDG_Refresh();
			break;
		case 1:
			// Read sensor value and prepare it for sending
			adc_value = getVibrationValue();
			float vibration_data = abs(((adc_value * 5.0) / 1023)-vibration_bias);

			floatToString(vibration_data, sensor_data_buffer, 2);
			// Upload data to cloud
			ESP_Send_Data(VIBRATION_THINGSPEAK_API_KEY, 1, sensor_data_buffer);
			IWDG_Refresh();
			// Transmit data to Master

			sprintf(lora_send, "%c%s", 'V', sensor_data_buffer); // merge sendID and data
			LoRa_transmit(&myLoRa, (uint8_t*)lora_send, 6, 1000);
			IWDG_Refresh();
			HAL_Delay(500);
//			HAL_Delay(15000);
			break;
		case 2:
			// Read sensor value and prepare it for sending
			adc_value = getMoistureValue();
			float moisture_data = abs(((adc_value * 5.0) / 1023)-moisture_bias);
			floatToString(moisture_data, sensor_data_buffer, 2);
			// Upload data to cloud
			ESP_Send_Data(MOISTURE_THINGSPEAK_API_KEY, 1, sensor_data_buffer);
			IWDG_Refresh();
			// Transmit data to Master

			sprintf(lora_send, "%c%s", 'M', sensor_data_buffer); // merge sendID and data
			LoRa_transmit(&myLoRa, (uint8_t*)lora_send, 6, 1000);
			IWDG_Refresh();
			HAL_Delay(500);
//			HAL_Delay(15000);
			break;
	}
}


void initializeSystem(){
	SystemClock_HSEConfig();
	MX_USART1_UART_Init();
	TIM2_Init();

	// Initialize watchdog to reset the system when encountering code halting loops
	IWDG_Init();

	// Initialize LORA
	IWDG_Refresh();
	myLoRa = newLoRa();
	int loraInitSuccess = 0;
	loraInitSuccess = LoRa_init(&myLoRa);
	while (!loraInitSuccess){
		loraInitSuccess = LoRa_init(&myLoRa);
		HAL_Delay(5000);
	}
	ESP_Init(WIFI_SSID, WIFI_PASSWD);


	LoRa_startReceiving(&myLoRa);


	if (isMaster){
		// Setup LCD
//		MX_I2C1_Init();

	}
	else {
		IWDG_Refresh();
		switch(sender){
			case 0:
				GY521_Init();
				break;
			case 1:
				Vibration_Init();
				break;
			case 2:
				Moisture_Init();
				break;
		}
	}
}

/* ------ Helper functions -------*/
void IWDG_Init(void){
	IWDG->KR = 0x5555;
	IWDG->PR = 0x07;
	IWDG->RLR = 0xFFFF;
	IWDG->KR = 0xAAAA;
	IWDG->KR = 0xCCCC;
}

void IWDG_Refresh(void){
	IWDG->KR = 0xAAAA;
}

void floatToString(float value, char* buffer, int precision) {
    // Check if the value is negative
    int isNegative = value < 0;

    // Get the absolute value for processing
    float absValue = fabs(value);
    int integerPart = (int)absValue;
    float fractionalPart = absValue - integerPart;
    int fractionalPartAsInt = (int)(fractionalPart * pow(10, precision));

    // Print the result to the buffer with the correct sign
    sprintf(buffer, "%s%d.%0*d", isNegative ? "-" : "", integerPart, precision, fractionalPartAsInt);
}

int compareString(char* message, char* compareTo){
	if (strcmp(message, compareTo) == 0) {
		return 1;
	}
	return 0;
}

void removeFirstChar(char* str) {
    // Get the length of the string
    int length = strlen(str);

    // Shift each character one position to the left
    for (int i = 0; i < length; i++) {
        str[i] = str[i + 1];
    }
}

