/*
 * my_dht11.h
 *
 *  Created on: 2021. 10. 29.
 *      Author: sobor
 */
#ifndef INC_MY_DHT11_H_
#define INC_MY_DHT11_H_

#define DHT_PORT 	(GPIOA)
#define DHT_PIN 	(GPIO_PIN_1)

typedef struct {
	float Temperature;
	float Humidity;
} DHT_DataTypedef;

void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void DHT_Start (void);
uint8_t DHT_Check_Response (void);
uint8_t DHT_Read (void);
void DHT_GetData (DHT_DataTypedef *DHT_Data);


#endif /* INC_MY_DHT11_H_ */
