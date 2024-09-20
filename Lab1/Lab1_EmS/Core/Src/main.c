/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */

void traffic_light_control(void)

{
    uint32_t start_time = HAL_GetTick();  // Get the initial tick count
    uint32_t delay_time = 5000;           // Start with 5 seconds for Red
    uint8_t state = 0;                    // 0 = Red, 1 = Green, 2 = Yellow

    // Initial state: Red ON, Green and Yellow OFF
    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 1);    // Red ON (0 = ON)
    HAL_GPIO_WritePin(Output_0_GPIO_Port, Output_0_Pin, 0);// Yellow OFF (1 = OFF)
    HAL_GPIO_WritePin(Output_1_GPIO_Port, Output_1_Pin, 0);  // Green OFF (1 = OFF)

    while (1)
    {
        // Check if the delay time has passed
        if (HAL_GetTick() - start_time >= delay_time)
        {
            // Transition the traffic lights between Red, Green, and Yellow
            switch (state)
            {
                case 0:  // Red to Green
                    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 0);    // Red OFF
                    HAL_GPIO_WritePin(Output_0_GPIO_Port, Output_0_Pin, 0);  // yellow off
                    HAL_GPIO_WritePin(Output_1_GPIO_Port, Output_1_Pin, 1);  // Green ON
                    delay_time = 3000;  // Green for 3 seconds
                    state = 1;
                    break;

                case 1:  // Green to Yellow
                    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 0);    // Red OFF
                    HAL_GPIO_WritePin(Output_0_GPIO_Port, Output_0_Pin, 1); // Yellow ON
                    HAL_GPIO_WritePin(Output_1_GPIO_Port, Output_1_Pin, 0);   // Green OFF
                    delay_time = 1000;  // Yellow for 1 second
                    state = 2;
                    break;

                case 2:  // Yellow to Red
                    HAL_GPIO_WritePin(Output_1_GPIO_Port, Output_1_Pin, 0);   // Green OFF
                    HAL_GPIO_WritePin(Output_0_GPIO_Port, Output_0_Pin, 0);  // Yellow OFF
                    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 1);   // Red ON
                    delay_time = 5000;  // Red for 5 seconds
                    state = 0;
                    break;
            }

            // Reset the start time to the current time
            start_time = HAL_GetTick();
        }

    }
}

void toggle_gpio_delay(void)
{
    uint8_t gpio_state = 0;  // Initial state is GPIO OFF (LED OFF)
    uint32_t delay_time = 4000;  // Start with 4 seconds delay for LED OFF

    // Initial LED OFF
    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 0);  // LED OFF (LOW)

    while (1)
    {
        // Toggle LED state
        gpio_state = !gpio_state;

        // Write the new state to the LED
        HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, gpio_state ? 0 : 1);

        // Delay for either 2 or 4 seconds depending on the state
        HAL_Delay(delay_time);  // This is the only HAL_Delay()

        // After toggling, change the delay time
        delay_time = (gpio_state) ? 2000 : 4000;
    }
}


void toggle_gpio(void)
{
    uint32_t start_time = HAL_GetTick();  // Get the initial tick count
    uint32_t delay_time = 4000;           // Start with 4 seconds delay
    uint8_t gpio_state = 0;               // Initial state is GPIO HIGH (LED ON)

    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 0);  // Set LED to ON

    while (1)
    {
        // Check if the delay time has passed
        if (HAL_GetTick() - start_time >= delay_time)
        {
            // Toggle LED state
            gpio_state = !gpio_state;

            // Write the new state to the LED
            HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, gpio_state ? 1 : 0);


            delay_time = gpio_state ? 2000 : 4000;

            // Reset the start time to the current time
            start_time = HAL_GetTick();
        }

        // Other code can run here without blocking due to HAL_Delay
    }
}

void toogle_gpio_bai1(void){
	while (1){
	    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 1);    // Red ON
	    HAL_Delay(2000);
	    HAL_GPIO_WritePin(Output_LED_GPIO_Port, Output_LED_Pin, 0);    // Red off
	    HAL_Delay(4000);
	}
}

int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

//  toggle_gpio();
  traffic_light_control();
//  toogle_gpio_bai1();
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, Output_LED_Pin|Output_0_Pin|Output_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : Output_LED_Pin Output_0_Pin Output_1_Pin */
  GPIO_InitStruct.Pin = Output_LED_Pin|Output_0_Pin|Output_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : Input_0_Pin Input_1_Pin */
  GPIO_InitStruct.Pin = Input_0_Pin|Input_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : Input_2_Pin Input_3_Pin */
  GPIO_InitStruct.Pin = Input_2_Pin|Input_3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
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

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



