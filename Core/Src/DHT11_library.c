/*
 * DHT11_library.c
 *
 *  Created on: Jan 26, 2023
 *      Author: QUOC THANG
 */
#include "DHT11_library.h"
#include "stdio.h"
#include "Delay_us.h"
#include "LCD_1602.h"
#include "Main_menu.h"

uint8_t Reponse;
uint8_t RH_data, RH_decimal, T_data, T_decimal, Check_sum;
uint16_t SUM,RH,TEMP;
//
float temperature = 0;
float humidity = 0;
uint8_t Presence = 0;

//-------------------------------------------------------------------
void Display_Humidity(float humidity)
{
	char str[20];
	Lcd_put_cur(0, 1);
	sprintf(str, " RH: %.0f%s", humidity, "%");
	Lcd_write_string(str);
}

void Display_Temperature(float temperature)
{
	Print_Temp_C();
	char str[20];
	Lcd_put_cur(0, 0);
	sprintf(str, " TEMP: %.f", temperature);
	Lcd_write_string(str);
	Lcd_put_cur(10, 0);
	Lcd_write_string("C");
}

void Set_pin_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void Set_pin_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Pin = GPIO_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

void MCU_Signal(void)
{
	Set_pin_output(DHT11_GPIO_Port, DHT11_Pin);
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 0); // pull down
	delay_ms(18);
	HAL_GPIO_WritePin(DHT11_GPIO_Port, DHT11_Pin, 1); // pull up
	delay_us(20);
	Set_pin_input(DHT11_GPIO_Port, DHT11_Pin);
}

uint8_t Check_reponse(void)
{
	uint8_t Reponse;
	delay_us(40);
	if(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == 0)
	{
		delay_us(80);
		if(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == 1)
		{
			Reponse = 1;
		}else Reponse = -1;
	}
	while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin) == 1);

	return Reponse;
}

uint8_t Check_bit(void)
{
	uint8_t i,j;
	for(j=0; j< 8; j++)
	{
			while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)==0);// wait pin go up (50us)
			delay_us(40);
			if(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)==0) // if pin go down -> bit 0
			{
				i = i<<1; // bit 0
			}
			else
			{
				i = (i<<1) | 0x01; // bit 1
			}
			while(HAL_GPIO_ReadPin(DHT11_GPIO_Port, DHT11_Pin)==1); // wait pin go down to transmit next bit data
	}
	return i;
}
void Get_data_DHT11(void)
{
	  Display_Temperature(temperature);
	  Display_Humidity(humidity);

	  MCU_Signal();
	  Presence = Check_reponse();
	  RH_data = Check_bit();
	  RH_decimal = Check_bit();
	  T_data = Check_bit();
	  T_decimal = Check_bit();
	  Check_sum = Check_bit();

	  TEMP = T_data;
	  RH = RH_data;

	  temperature = (float) TEMP;
	  humidity = (float) RH;
	  if(humidity > 70)
	  {
		  Print_Cloud();
	  }
	  else
	  {
		  Print_Sun();
	  }

	  HAL_Delay(100);
}
//-------------------------------------------------------------------
