/*
 * my_dht11.c
 *
 *  Created on: 2021. 10. 29.
 *      Author: sobor
 */
#include "main.h"
#include "my_dht11.h"

void delay_us(volatile uint32_t us) {
	us *= (SystemCoreClock / 8U / 1000000U);
	while (us--);
}

// ------------------- GPIO Input Output Changer----------------------//
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef DHT11_DATA = {0};
	DHT11_DATA.Pin = GPIO_Pin;
	DHT11_DATA.Mode = GPIO_MODE_OUTPUT_PP;
	DHT11_DATA.Pull = GPIO_NOPULL;
	DHT11_DATA.Speed = GPIO_SPEED_FREQ_LOW;

	HAL_GPIO_Init(GPIOx, &DHT11_DATA);
}

void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
	GPIO_InitTypeDef DHT11_DATA = {0};
	DHT11_DATA.Pin = GPIO_Pin;
	DHT11_DATA.Mode = GPIO_MODE_INPUT;
	DHT11_DATA.Pull = GPIO_NOPULL;
	DHT11_DATA.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &DHT11_DATA);
}


// ------------------- DHT SETTING ----------------------//
void DHT_Start (void) {
	//DWT_Delay_Init();
	Set_Pin_Output (DHT_PORT, DHT_PIN);  // set the pin as output
	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 0);   // pull the pin low

	delay_us(18000);   // wait for 18ms

	HAL_GPIO_WritePin (DHT_PORT, DHT_PIN, 1);   // pull the pin high
	delay_us (20);   // wait for 30us
	Set_Pin_Input(DHT_PORT, DHT_PIN);    // set as input
}

uint8_t DHT_Check_Response (void) {
	uint8_t Response = 0;
	delay_us(40);
	if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) {
		delay_us(80);
		if ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) Response = 1;
		else Response = -1;
	}
	while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));   // wait for the pin to go low

	return Response;
}

uint8_t DHT_Read (void) {
  uint8_t i,j;
  for (j=0;j<8;j++) {
    while (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));   // wait for the pin to go high
    delay_us(40);   // wait for 40 us
    if (!(HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN))) {  // if the pin is low
      i&= ~(1<<(7-j));   // write 0
    }
    else i|= (1<<(7-j));  // if the pin is high, write 1
    while ((HAL_GPIO_ReadPin (DHT_PORT, DHT_PIN)));  // wait for the pin to go low
  }
  return i;
}

uint8_t Rh_byte1;
uint8_t Rh_byte2;
uint8_t Temp_byte1;
uint8_t Temp_byte2;
uint16_t SUM;
uint8_t Presence = 0;

void DHT_GetData (DHT_DataTypedef *DHT_Data) {
  DHT_Start ();
  Presence = DHT_Check_Response ();
  Rh_byte1 = DHT_Read ();
  Rh_byte2 = DHT_Read ();
  Temp_byte1 = DHT_Read ();
  Temp_byte2 = DHT_Read ();
  SUM = DHT_Read();

  if (SUM == (Rh_byte1+Rh_byte2+Temp_byte1+Temp_byte2)) {
	DHT_Data->Temperature = Temp_byte1;
	DHT_Data->Humidity = Rh_byte1;
  }
}
