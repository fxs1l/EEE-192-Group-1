#include "vibration.h"

#include "adc.h"

void Vibration_Init(){
	ADC_Init();
}

uint16_t getVibrationValue(){
	// Enable the ADC 
	ADC1->CR2 |= (1 << 0); 
	HAL_Delay(0.5);

	// Start ADC conversion
	ADC1->CR2 |= (1 << 30);
	while (!((ADC1->SR) & (1 << 1))); // Wait for conversion to finish

	uint32_t vibration_value = ADC1->DR;
	return vibration_value;
}
