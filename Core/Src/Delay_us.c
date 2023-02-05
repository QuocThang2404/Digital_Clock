/*
 * Delay_us.c
 *
 *  Created on: Jan 26, 2023
 *      Author: QUOC THANG
 */
#include "Delay_us.h"

extern TIM_HandleTypeDef htim2;

//-------------------------------------------------------------------
void delay_us(uint16_t us)
{
	htim2.Instance->CNT =0;
	HAL_TIM_Base_Start(&htim2);
	while(htim2.Instance->CNT < us);
	HAL_TIM_Base_Stop(&htim2);
}

void delay_ms(uint16_t ms)
{
	for(uint16_t i =0 ; i<ms; i++)
	{
		delay_us(1000);
	}
}
//-------------------------------------------------------------------
