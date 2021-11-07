/*
 * my_buz.c
 *
 *  Created on: 2021. 10. 29.
 *      Author: sobor
 */

#include "main.h"
#include "my_buz.h"

void buz_beep(){
	HAL_GPIO_WritePin(BUZ_PORT, BUZ_1, GPIO_PIN_SET);
	HAL_Delay(200);
	HAL_GPIO_WritePin(BUZ_PORT, BUZ_1, GPIO_PIN_RESET);
}


