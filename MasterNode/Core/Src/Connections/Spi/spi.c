/*
 * spi.c
 *
 *  Created on: May 26, 2024
 *      Author: fxs1l
 */
#include "spi.h"

SPI_HandleTypeDef hspi1;

void SPI1_GPIOA_Init();
void SPI1_GPIOB_Init();

void SPI_Init(){

    /**
	Register-Based Code
	*/

    // RCC->APB2ENR |= (1 << 12); // Enable SPI1 clock

    // SPI1->CR1 |= (1 << 2); // Set as Master Configuration
    // SPI1->CR1 |= (1 << 0); // Clock phase: The first clock transition is the first data capture edge
    // SPI1->CR1 &= ~(1 << 1); // Clock polarity: CK to 0 when idle
    // SPI1->CR1 |= (2 << 3); // Baud rate control: fPLCK / 8;
    // SPI1->CR1 &= ~(1 << 15); // Bidirectional data mode enable: 2-line unidirectional data mode selected
    // SPI1->CR1 &= ~(1 << 11); // Data frame format: 8-bit data frame is selected for transmission/reception
    // SPI1->CR1 &= ~(1 << 7); // MSB transmitted first
    // SPI1->CR1 |= (1 << 9); // Software slave management enabled

    // SPI1->CR2 &= ~(1 << 4); // Motorola mode

    // SPI1->CR1 &= ~(1 << 13); // CRC calculation disabled
    // SPI1->CRCPR |= (10 << 0); // CRC Polynomial = 10

    /**
	HAL-Based Code
	*/

	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 10;
    SPI1_GPIOA_Init(&hspi1);
    SPI1_GPIOB_Init();

    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        // Error_Handler();
    }

}

void SPI1_GPIOA_Init(SPI_HandleTypeDef* spiHandle){
    /**SPI1 GPIOA Configuration
    PA5     ------> SPI1_SCK
    PA6     ------> SPI1_MISO
    PA7     ------> SPI1_MOSI
    */

    /**
	Register-Based Code
	*/

    // RCC->AHB1ENR |= (1 << 0); // Enable GPIOA Clock
    // GPIOA->MODER |= (2 << 10) | (2 << 12) | ( 2 << 14); // Alternate Function mode for PA5, PA6, and PA7
    // GPIOA->OSPEEDR |= (3 << 10) | (3 << 12) | (3 << 14); // HIGH Speed for PA5, PA6, PA7
    // // GPIOx->PUPDR |= (0 << 10) | (0 << 12) | (0 << 14); // No PU PD
    // GPIOA->AFR[0] |= (5 << 20) | (5 << 24) | (5 << 28); // AF5: SPI1 for  PA5, PA6, PA7

    /**
	HAL-Based Code
	*/

    GPIO_InitTypeDef GPIO_InitStruct = {0};
      if(spiHandle->Instance==SPI1)
      {
      /* USER CODE BEGIN SPI1_MspInit 0 */

      /* USER CODE END SPI1_MspInit 0 */
        /* SPI1 clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();

        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**SPI1 GPIO Configuration
        PA5     ------> SPI1_SCK
        PA6     ------> SPI1_MISO
        PA7     ------> SPI1_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

      /* USER CODE BEGIN SPI1_MspInit 1 */

      /* USER CODE END SPI1_MspInit 1 */
      }
}

void SPI1_GPIOB_Init(){
	/**SPI1 GPIOB Configuration
	PB0     ------> NSS
	PB1     ------> RST
	PB2     ------> DIO0
	*/

	/**
	Register-Based Code
	*/
    // RCC-> AHB1ENR |= (1 << 1); // Enable GPIOB Clock
    // GPIOB->MODER |= (1 << 0) | (1 << 2); // General purpose output mode for PB0, PB1
    // GPIOB->MODER &= ~((1 << 1) | (1 << 3)); // General purpose output mode for PB0, PB1
    // GPIOB->MODER &= ~(1 << 4) | (1 << 5); // Input for PB2

    // GPIOB->PUPDR &= ~((1 << 5) | (1 << 4) | (1 << 3) | (1 << 2) | (1 << 1) | (1 << 0));   // No PU PD

    //    EXTI->IMR |= EXTI_IMR_IMx;               // Unmask the interrupt for PAx
    //    EXTI->RTSR |= EXTI_RTSR_TRx;
    //    NVIC_EnableIRQ(EXTIx_IRQn);


    /**
	HAL-Based Code
	*/
    GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, NSS_Pin|RST_Pin, GPIO_PIN_SET);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pins : PBPin PBPin */
	GPIO_InitStruct.Pin = NSS_Pin|RST_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Pin = DIO0_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DIO0_GPIO_Port, &GPIO_InitStruct);
}
