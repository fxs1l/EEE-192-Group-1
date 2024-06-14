/**
    ADC Configuration

    Connection:     GPIOA -> PA1
    Prescaler:      2
    ADC Resolution:

*/

#include "adc.h"

void GPIOA_PA1_Init();

void ADC_Init() {
    // Configure PA1 for ADC
    GPIOA_PA1_Init();

	// Enable ADC1 clock
	RCC->APB2ENR |= (1 << 8);

	// Prescaler = 2
	ADC->CCR &= ~(1 << 16);
	ADC->CCR &= ~(1 << 17);

	// Configure ADC resolution
	ADC1->CR1 &= ~(1 << 25);
	ADC1->CR1 &= ~(1 << 24);

	// Configure to Scan mode
	ADC1->CR1 |= (1 << 8);
	// Enable Interrupt for EOC
	ADC1->CR1 |= (1 << 5);
	// Configure sampling time
	ADC1->SMPR2 &= ~(1 << 5);
	ADC1->SMPR2 &= ~(1 << 4);
	ADC1->SMPR2 |= (1 << 3);
	// End of conversion selection:
	ADC1->CR2 &= ~(1 << 10);

	// Configure data alignment: Right alignment
	ADC1->CR2 &= ~(1 << 11);

	// Regular channel sequence length: 1 conversion
	ADC1->SQR1 &= ~(1 << 23);
	ADC1->SQR1 &= ~(1 << 22);
	ADC1->SQR1 &= ~(1 << 21);
	ADC1->SQR1 &= ~(1 << 20);

	// Assign channel for first conversion
	ADC1->SQR3 |= (1 << 0);

	// Continuous conversion mode
	ADC1->CR2 |= (1 << 1);
}

void GPIOA_PA1_Init() {
	// Enable GPIOA clock
	RCC->AHB1ENR |= (1 << 0);

	// Configure PA1 to analog mode
	GPIOA->MODER |= (1 << 3);
	GPIOA->MODER |= (1 << 2);

}
