/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "my_buz.h"
#include "my_led.h"
#include "my_dht11.h"
// #include "my_dht11.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define TRUE 1
#define FALSE 0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

bool key_0_flag = FALSE;
bool key_1_flag = FALSE;
bool key_2_flag = FALSE;
bool key_3_flag = FALSE;

int cooler = 0;
int heater = 0;
int temp_mode = 0; // 0: min temp set mode, 1: Max temp set mode
int min_temp = 15;
int max_temp = 20;
uint16_t tx_cnt = 0;

DHT_DataTypedef DHT11_Data;
float temp = 0.0f;
float humi = 0.0f;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// ------------------------------ stdio prinf scanf ------------------------------ //
// scanf
int _read(int file, char* ptr,int len){
  HAL_UART_Receive(&huart2,(uint8_t*)ptr, 1, 0xFFFFFFFF);
  HAL_UART_Transmit(&huart2, (uint8_t*)ptr, 1, 0xFFFFFFFF);
  return 1;
}

// printf
int _write(int file, char* ptr,int len){
  HAL_UART_Transmit(&huart2,(uint8_t*)ptr, (uint16_t)len, 0xFFFFFFFF);
  return len;
}

// ------------------------------ BTN Interrupt ------------------------------ //

// btn click check
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  /*
  - 버튼을 누르면 부저가 200ms동안 울리게 하기위해 Callback함수에 HAL_Delay를 넣었으나
  -> HAL_Delay가 제대로 동작하지 않음
  !!! ISR 사이에 HAL_Delay가 들어가면 제대로 동작하지 않는다 !!!
  - HAL_Delay를 Callback 내에서 사용하기 위해서는 NVIC의 SysTick_Handler 우선순위를 바꿔주거나( https://stackoverflow.com/questions/53899882/hal-delay-stuck-in-a-infinite-loop)
  - 플래그만 설정한 뒤, main의 while문에서 처리하면 됨.

  두번째 방법을 이용해, 오래걸리지 않는 데이터 변경 및 간단한 출력은 Callback에서 처리,
  HAL_Delay를 사용하는 부저 울리기는 main의 while문 내에서 처리했다.
  */
	switch(GPIO_Pin){
		case GPIO_PIN_0 :
			key_0_flag = TRUE;
			temp_mode = 0;
			printf("Min temperature setting mode \r\n");
			break;
		case GPIO_PIN_1 :
			key_1_flag = TRUE;
			temp_mode = 1;
			printf("Max temperature setting mode \r\n");
			break;
		case GPIO_PIN_2 :
			key_2_flag = TRUE;
			if(temp_mode == 0){ // min_mode
				if(min_temp > 5) min_temp--;
				printf("Min temp : %d\r\n", min_temp);
			}
			else {
				if(max_temp > min_temp) max_temp--;
				printf("Max temp : %d\r\n", max_temp);
			}
			break;
		case GPIO_PIN_3 :
			key_3_flag = TRUE;
			if(temp_mode == 0){ // min_mode
				if(min_temp < max_temp) min_temp++;
				printf("Min temp : %d\r\n", min_temp);
			}
			else {
				if(max_temp < 40) max_temp++;
				printf("Max temp : %d\r\n", max_temp);
			}
			break;
	}
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  // ------------------------------ btn buz_beep ------------------------------ //
	if(key_0_flag == TRUE){
	  key_0_flag = FALSE;
	  buz_beep();
	}
	if(key_1_flag == TRUE){
	  key_1_flag = FALSE;
	  buz_beep();
	}
	if(key_2_flag == TRUE){
	  key_2_flag = FALSE;
	  buz_beep();
	}
	if(key_3_flag == TRUE){
	  key_3_flag = FALSE;
	  buz_beep();
	}

	  // ------------------------------ LED DISPLAY ------------------------------ //
	// 1. temperature LED 
	if(temp < min_temp){ // current temperature is below than min_temp
		led_out(LED_1_YELLOW, TURN_ON);

		led_out(LED_1_RED, TURN_OFF);
		led_out(LED_1_GREEN, TURN_OFF);

		cooler = 0;
		heater = 1; // turn on heater
	}
	else if(temp > max_temp){
		led_out(LED_1_RED, TURN_ON);
		led_out(LED_1_YELLOW, TURN_OFF);
		led_out(LED_1_GREEN, TURN_OFF);
		heater = 0;
		cooler = 1; // turn on the air conditioner
	}
	else{ // proper temperature
		led_out(LED_1_RED, TURN_OFF);
		led_out(LED_1_YELLOW, TURN_OFF);
		led_out(LED_1_GREEN, TURN_ON);
		heater = 0; // both turn off
		cooler = 0;
	}

	// 2. cooler and heater LED
	if(heater == 1){
		led_out(LED_2_RED, TURN_ON);
		led_out(LED_2_GREEN, TURN_OFF);
	}
	else if(cooler == 1){
		led_out(LED_2_RED, TURN_OFF);
		led_out(LED_2_GREEN, TURN_ON);
	}
	else{
		led_out(LED_2_RED, TURN_OFF);
		led_out(LED_2_GREEN, TURN_OFF);
	}
	// ------------------------------ DHT11 GET DATA ------------------------------ //
	DHT_GetData(&DHT11_Data);
	temp = DHT11_Data.Temperature;
	humi = DHT11_Data.Humidity;

	  // ------------------------------ UART ------------------------------ //
	printf("[%d] Temp / Humi // Heater / Cooler / min// Max : [%4.2fºC]/[%4.2f%%] // [%d]/[%d] // [%d]/[%d] \r\n", tx_cnt++, temp, humi, heater, cooler, min_temp, max_temp);

	HAL_Delay(1500); // 딜레이 시간이 너무 적으면, DHT가 데이터를 제대로 읽어오지 못한다
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11
                          |GPIO_PIN_12, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA6 PA7 PA11
                           PA12 */
  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_11
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI2_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

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
