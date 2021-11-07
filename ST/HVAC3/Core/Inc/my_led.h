/*
 * my_led.h
 *
 *  Created on: 2021. 10. 29.
 *      Author: sobor
 */

#ifndef INC_MY_LED_H_
#define INC_MY_LED_H_

#define TURN_ON 1
#define TURN_OFF 0

#define LED_PORT		(GPIOA)
#define LED_1_RED		(GPIO_PIN_5)
#define LED_1_YELLOW	(GPIO_PIN_6)
#define LED_1_GREEN		(GPIO_PIN_7)
#define LED_2_RED		(GPIO_PIN_12)
#define LED_2_GREEN		(GPIO_PIN_11)

void led_init(void);
void led_out(uint16_t pin, uint8_t val);
void led_one_sec(uint16_t pin);
void led_all_on();

#endif /* INC_MY_LED_H_ */
