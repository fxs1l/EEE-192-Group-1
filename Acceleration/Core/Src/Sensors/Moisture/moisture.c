#include "moisture.h"

#include "adc.h"

void Moisture_Init(){
	ADC_Init();
}

int getMoistureValue(){
	// Enable the ADC 
	ADC1->CR2 |= (1 << 0); 
	HAL_Delay(1);

	// Start ADC conversion
	ADC1->CR2 |= (1 << 30);
	while (!((ADC1->SR) & (1 << 1))); // Wait for conversion to finish

	uint32_t moisture_value = ADC1->DR;
	return moisture_value;
}
