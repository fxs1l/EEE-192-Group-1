#include "gy521.h"

// Raw variables
int16_t Accel_X_RAW = 0;
int16_t Accel_Y_RAW = 0;
int16_t Accel_Z_RAW = 0;

int16_t Gyro_X_RAW = 0;
int16_t Gyro_Y_RAW = 0;
int16_t Gyro_Z_RAW = 0;

// Processed variables
float Ax, Ay, Az, Gx, Gy, Gz;

// Bias variables for calibration
static float Accel_X_Bias = 0.0f;
static float Accel_Y_Bias = 0.0f;
static float Accel_Z_Bias = 0.0f;

static float Gyro_X_Bias = 0.0f;
static float Gyro_Y_Bias = 0.0f;
static float Gyro_Z_Bias = 0.0f;

void GY521_Write (uint8_t Address, uint8_t Reg, uint8_t Data)
{
	I2C_Start();
	I2C_Address (Address);
	I2C_Write (Reg);
	I2C_Write (Data);
	I2C_Stop ();
}

void GY521_Read (uint8_t Address, uint8_t Reg, uint8_t *buffer, uint8_t size)
{
	I2C_Start();
	I2C_Address (Address);
	I2C_Write (Reg);
	I2C_Start ();  // repeated start
	I2C_Read (Address+0x01, buffer, size);
	I2C_Stop ();
}

// void LD_Init(void){
// 	RCC->AHB1ENR |= (1<<0); // Enables GPIOA peripheral
// 	GPIOA->MODER &= ~(1<<11); // PA5 as Output, MODER = 0b01
// 	GPIOA->MODER |= (1<<10); // PA5 as Output, MODER = 0b01
// 	GPIOA->OTYPER &= ~(1<<5); // Sets GPIOA, PIN 5 as push-pull
// 	GPIOA->ODR &= ~(1<<5); // PA5 initially LOW
// }


void GY521_Read_Accel (void)
{

	uint8_t Rx_data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	GY521_Read (GY521_ADDR, ACCEL_X_OUT_H_REG, Rx_data, 6);

	Accel_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data [1]);
	Accel_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data [3]);
	Accel_Z_RAW = (int16_t)(Rx_data[4] << 8 | Rx_data [5]);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/
	//	static float factor = 32678.0f/16000.0f; // factor for 16G
	static int g = 2;
	float scalingFactor = (32678.0f/g);

	Ax = (Accel_X_RAW/scalingFactor) - Accel_X_Bias;
	Ay = (Accel_Y_RAW/scalingFactor) - Accel_Y_Bias;
	Az = (Accel_Z_RAW/scalingFactor) - Accel_Z_Bias;
}

void GY521_Read_Gyro (void)
{

	uint8_t Rx_data[6];

	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	GY521_Read (GY521_ADDR, GYRO_X_OUT_H_REG, Rx_data, 6);

	Gyro_X_RAW = (int16_t)(Rx_data[0] << 8 | Rx_data [1]);
	Gyro_Y_RAW = (int16_t)(Rx_data[2] << 8 | Rx_data [3]);
	Gyro_Z_RAW= (int16_t)(Rx_data[4] << 8 | Rx_data [5]);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	Gx = Gyro_X_RAW/131.0;
	Gy = Gyro_Y_RAW/131.0;
	Gz = Gyro_Z_RAW/131.0;

}

void GY521_Init (void)
{
	I2C_Config();
	// SystemClockConfig();

	uint8_t check;
	uint8_t Data;

	// check device ID WHO_AM_I

	GY521_Read (GY521_ADDR,WHO_AM_I_REG, &check, 1);

	if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		GY521_Write (GY521_ADDR, PWR_MGMT_1_REG, Data);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		GY521_Write(GY521_ADDR, SMPLRT_DIV_REG, Data);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> ? 2g
		Data = 0x00;
		GY521_Write(GY521_ADDR, ACCEL_CONFIG_REG, Data);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> ? 250 ?/s
		Data = 0x00;
		GY521_Write(GY521_ADDR, GYRO_CONFIG_REG, Data);
	}

	// TIM2->EGR |= (1<<0); // Reset timer counter registers
	// TIM2->CR1 |= (1<<0); // Enable timer
}



