/*
 * my_led.c
 *
 *  Created on: 2021. 10. 29.
 *      Author: sobor
 */

#include "main.h"
#include "my_led.h"

void led_init(void){
	HAL_GPIO_WritePin(LED_PORT, LED_1_RED, TURN_OFF);
	HAL_GPIO_WritePin(LED_PORT, LED_1_YELLOW, TURN_OFF);
	HAL_GPIO_WritePin(LED_PORT, LED_1_GREEN, TURN_OFF);
	HAL_GPIO_WritePin(LED_PORT, LED_2_RED, TURN_OFF);
	HAL_GPIO_WritePin(LED_PORT, LED_2_GREEN, TURN_OFF);
}

// led 출력 함수
void led_out(uint16_t pin, uint8_t val){
	HAL_GPIO_WritePin(LED_PORT, pin, (GPIO_PinState)val);
}

void led_one_sec(uint16_t pin){
	led_out(pin, TURN_ON);
	HAL_Delay(1000);
	led_out(pin, TURN_OFF);
	HAL_Delay(1000);
}

void led_all_on(){
	led_out(LED_1_RED, TURN_ON);
	led_out(LED_1_YELLOW, TURN_ON);
	led_out(LED_1_GREEN, TURN_ON);
	led_out(LED_2_RED, TURN_ON);
	led_out(LED_2_GREEN, TURN_ON);
}
