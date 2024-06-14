#include "rcc.h"

void SystemClock_HSIConfig(void) {
    // RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	// RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	*/
	// __HAL_RCC_PWR_CLK_ENABLE();
	RCC->APB1ENR |= (1 << 28); // Resets the power interface

	// __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	// Power scale mode 3 <= 64 MHz
	PWR->CR &= ~(1 << 15);
	PWR->CR |= (1 << 14);

	/** Initializes the RCC Oscillators according to the specified parameters
	* in the RCC_OscInitTypeDef structure.
	*/
	// Turn on Internal high-speed clock (HSI)
	// RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC->CR |= (1 << 1);
	while ((RCC->CR & (1<<1)) == 0); // Wait until HSI is ready

	// Initialize and configure PLL
	RCC->PLLCFGR |= (8 << 0); // PLLM = 8
	RCC->PLLCFGR |= (72 << 6); // PLLN = 72
	RCC->PLLCFGR |= (2 << 16); // PLLP  = 2
	RCC->PLLCFGR |= (4 << 24); // PLLQ = 4

	RCC->CR |= (1 << 24); // Enable PLL Clock
	while ((RCC->CR & (1<<25)) == 0); // Wait until PLL is ready

	// Configure Flash prefetch, Instruction cache, Data cache and wait state
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_2WS;

	// Select PLL as system clock source
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL); // Wait until PLL is used as system clock source

	// Set AHB prescaler
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1; // HCLK = SYSCLK

	// Set APB1 prescaler
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2; // APB1 = HCLK/2

	// Set APB2 prescaler
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1; // APB2 = HCLK
}

void Error_Handler(void);
//void SystemClock_HSEConfig (void){
//		/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************
//
//	1. ENABLE HSE and wait for the HSE to become Ready
//	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
//	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
//	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
//	5. Configure the MAIN PLL
//	6. Enable the PLL and wait for it to become ready
//	7. Select the Clock Source and wait for it to be set
//
//	********************************************************/
//
//
//	// #define PLL_M 	4
//	// #define PLL_N 	72
//	// #define PLL_P 	0  // PLLP = 2
//
//	// // 1. ENABLE HSE and wait for the HSE to become Ready
//	// RCC->CR |= RCC_CR_HSEON;
//	// while (!(RCC->CR & RCC_CR_HSERDY));
//
//	// // 2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
//	// RCC->APB1ENR |= (1 << 28);
//	// // PWR->CR |= PWR_CR_VOS;
//	// PWR->CR &= ~(1 << 15);
//	// PWR->CR |= (1 << 14);
//
//
//	// // 3. Configure the FLASH PREFETCH and the LATENCY Related Settings
//	// FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;
//
//	// // 4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
//	// // AHB PR
//	// RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
//
//	// // APB1 PR
//	// RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
//
//	// // APB2 PR
//	// RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
//
//
//	// // 5. Configure the MAIN PLL
//	// RCC->PLLCFGR = (PLL_M <<0) | (PLL_N << 6) | (PLL_P <<16) | (RCC_PLLCFGR_PLLSRC_HSE);
//
//	// // 6. Enable the PLL and wait for it to become ready
//	// RCC->CR |= RCC_CR_PLLON;
//	// while (!(RCC->CR & RCC_CR_PLLRDY));
//
//	// // 7. Select the Clock Source and wait for it to be set
//	// RCC->CFGR |= RCC_CFGR_SW_PLL;
//	// while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
//
//	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
//	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
//
//	/** Configure the main internal regulator output voltage
//	*/
//	__HAL_RCC_PWR_CLK_ENABLE();
//	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
//
//	/** Initializes the RCC Oscillators according to the specified parameters
//	* in the RCC_OscInitTypeDef structure.
//	*/
//	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//	RCC_OscInitStruct.PLL.PLLM = 4;
//	RCC_OscInitStruct.PLL.PLLN = 72;
//	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
//	RCC_OscInitStruct.PLL.PLLQ = 4;
//	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//	{
////		Error_Handler();
//	}
//
//	/** Initializes the CPU, AHB and APB buses clocks
//	*/
//	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
//								|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
//	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
//	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//
//	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
//	{
////		Error_Handler();
//	}
//
//	void Error_Handler(void)
//	{
//	/* USER CODE BEGIN Error_Handler_Debug */
//	/* User can add his own implementation to report the HAL error return state */
//	__disable_irq();
//	while (1){
//	}
//	/* USER CODE END Error_Handler_Debug */
//	}
//}

void SystemClock_HSEConfig(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
