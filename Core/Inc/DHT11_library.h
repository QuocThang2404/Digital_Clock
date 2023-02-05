/*
 * DHT11_library.h
 *
 *  Created on: Jan 26, 2023
 *      Author: QUOC THANG
 */

#ifndef INC_DHT11_LIBRARY_H_
#define INC_DHT11_LIBRARY_H_

#include "stm32f1xx_hal.h"
#include "main.h"

#define DHT11_Pin           GPIO_PIN_0
#define DHT11_GPIO_Port     GPIOA


void Display_Humidity(float humidity);
void Display_Temperature(float temperature);
void Set_pin_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_pin_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void MCU_Signal(void);
uint8_t Check_reponse(void);
uint8_t Check_bit(void);
void Get_data_DHT11(void);
#endif /* INC_DHT11_LIBRARY_H_ */
