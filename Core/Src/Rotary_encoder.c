/*
 * Rotary_encoder.c
 *
 *  Created on: Jan 27, 2023
 *      Author: QUOC THANG
 */
#include "Rotary_encoder.h"
#include "stm32f1xx_hal.h"
#include "LCD_1602.h"
extern int is;
int count = 0;
int scroll = 0;
int hour = 0;
int min = 0;
int button_count = 1;

uint8_t button_current_state = 1;
uint8_t button_last_state = 1;
uint8_t button_filter = 1;
uint8_t is_debouncing = 0;
uint32_t time_debounce;
uint32_t time_start_press;
uint8_t holding_press = 0;

void Rotary_encoder_Handle(void)
{
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET)
	  {
		  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET)
		  {
			  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET);
			  count++;
			  scroll++;
			  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET); // doi pha A het muc 0, len muc 1
			  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);//doi pha B het muc 0, len muc 1
			  HAL_Delay(10);
		  }
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET)
	  {
		  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
		  {
			  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET );//doi pha A het muc 1, len muc 0
			  count--;
			  scroll--;
			  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);
			  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET);// doi pha A het muc 0, len muc 1
			  HAL_Delay(10);
		  }
	  }
	  if(count < 0) count = 0;
	  if(count > 1) count = 1;
	  if(scroll < 0) scroll = 0;
	  if(scroll > 3) scroll = 3;
}
void Button(void)
{
	uint8_t sta = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
	if(sta != button_filter)
	{
		button_filter = sta;
		is_debouncing = 1;
		time_debounce = HAL_GetTick();
	}
	if(is_debouncing  && HAL_GetTick() - time_debounce >= 15)
	{
		button_current_state = button_filter;
		is_debouncing = 0;
	}

	if(button_current_state != button_last_state)
	{
		if(button_current_state == 0)//nhan xuong
		{
			button_count = 0;
		}
		else//nha ra
		{
			button_count = 1;
		}
		button_last_state = button_current_state;
	}
}
void Rotary_Scroll(void)
{
	  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET)
	  {
		  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET)
		  {
			  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET);
			  scroll++;
			  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET); // doi pha A het muc 0, len muc 1
			  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);//doi pha B het muc 0, len muc 1
			  HAL_Delay(10);
		  }
	  }
	  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET)
	  {
		  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
		  {
			  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET );//doi pha A het muc 1, len muc 0
			  scroll--;
			  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);
			  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET);// doi pha A het muc 0, len muc 1
			  HAL_Delay(10);
		  }
	  }
		  if(scroll < 0) scroll = 0;
		  if(scroll > 4) scroll = 3;
}
void Rotary_Hour(void)
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET)
		  {
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET)
			  {
				  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET);
				  hour++;
				  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET); // doi pha A het muc 0, len muc 1
				  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);//doi pha B het muc 0, len muc 1
				  HAL_Delay(10);
			  }
		  }
		  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET)
		  {
			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
			  {
				  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET );//doi pha A het muc 1, len muc 0
				  hour--;
				  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);
				  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET);// doi pha A het muc 0, len muc 1
				  HAL_Delay(10);
			  }
		  }
		  if(hour < 0) hour = 0;
		  if(hour > 23)
		  {
			  lcd_clear_xy(4, 0);
			  lcd_clear_xy(5, 0);
			  is = 3;
			  hour = 0;
		  }

}
void Rotary_Min(void)
{
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET)
		  {
			  if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET)
			  {
				  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_SET);
				  min++;
				  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET); // doi pha A het muc 0, len muc 1
				  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);//doi pha B het muc 0, len muc 1
				  HAL_Delay(10);
			  }
		  }
		  else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET)
		  {
			  if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET)
			  {
				  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_SET );//doi pha A het muc 1, len muc 0
				  min--;
				  while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET);
				  while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET);// doi pha A het muc 0, len muc 1
				  HAL_Delay(10);
			  }
		  }
		  if(min < 0) min = 0;
		  if(min > 59)
			  {
			  	  lcd_clear_xy(7, 0);
				  lcd_clear_xy(8, 0);
				  is = 6;
				  min = 0;
			  }


}
