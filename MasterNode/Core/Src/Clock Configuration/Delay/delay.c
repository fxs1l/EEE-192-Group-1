#include "delay.h"

volatile int doDelay = 0;
const int default_ARR = 5000;
void TIM2_Init(void) {
	RCC->APB1ENR |= (1<<0); // Enable clock for TIM2
	TIM2->PSC = 32000-1; // Set PSC+1 = 320000

	// For a peripheral clock frequency of 32MHz,
	// each tick of the timer is 1ms
	// Frequency of 1.5Hz = Period of 666.667ms
	TIM2->ARR = default_ARR; // Set timer to reset after CNT = 5000 or 5s

	TIM2->DIER |= (1<<0); // Enable timer interrupt generation

	NVIC->IP[TIM2_IRQn] = (2 << 4); // Set priority to 2
//	NVIC_SetPriority(TIM2_IRQn, 2);
	NVIC->ISER[TIM2_IRQn >> 5] |= (1 << (TIM2_IRQn % 32)); // Enable interrupt
	TIM2->SR &= ~(1<<0);

	TIM2->EGR |= (1<<0);
	TIM2->CR1 &= ~(1<<0); // Disabletimer, for now
//	RCC->APB1ENR |= (1<<0); // Enable clock for TIM2
//	TIM2->PSC = 16000-1; // Set PSC+1 = 160000
//	TIM2->ARR = 100; // Set timer to reset after CNT = 100
//	TIM2->DIER |= (1<<0); // Enable timer interrupt generation
//	NVIC->IP[TIM2_IRQn] = (2 << 4); // Set priority to 2
//	NVIC->ISER[TIM2_IRQn >> 5] |= (1 << (TIM2_IRQn % 32)); // Enable interrupt
//	TIM2->SR &= ~(1<<0);
//	TIM2->SR &= ~(1<<0); // Clear UIF update interrupt flag
//	TIM2->EGR |= (1<<0);
	TIM2->CR1 &= ~(1<<0); // Disable timer, for now
}

void TIM2_IRQHandler(void){
	doDelay = 0; // release lock
	if (TIM2->SR & TIM_SR_UIF) {
		TIM2->SR &= ~(1<<0); // Clear UIF update interrupt flag
		TIM2->CR1 &= ~(1<<0);
		// Handle the update event (e.g., toggle an LED, update a variable, etc.)
	}
//	NVIC_SystemReset();
}

void startTimer(void){
//	TIM2->CR1 &= ~(1<<0);
	TIM2->EGR |= (1<<0); // Reset timer counter registers
	TIM2->CR1 |= (1<<0);
	doDelay = 1; // start code lock
}


void Delay(int delay){
    TIM2->CR1 &= ~(1<<0);
 	TIM2->ARR = delay;
 	TIM2->CR1 |= (1<<0);
    
 	while(doDelay); // Lock code
 	TIM2->ARR = default_ARR;
}

