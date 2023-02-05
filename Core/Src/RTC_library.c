/*
 * RTC_library.c
 *
 *  Created on: Feb 2, 2023
 *      Author: QUOC THANG
 */
#include "RTC_library.h"
#include "stdio.h"
#include "stm32f1xx_hal.h"
#include "Rotary_encoder.h"
#include "LCD_1602.h"
extern I2C_HandleTypeDef hi2c2;
#define RTC_Address 0xD0
typedef struct
{
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t day;
	uint8_t date;
	uint8_t month;
	uint8_t year;
}Data_time;

Data_time set_time;

static uint8_t DecimalToBcd(uint8_t num)
{
	return ((num / 10) << 4) | (num % 10);
}

static uint8_t BcdToDecimal(uint8_t num)
{
	return ((num >> 4) * 10) + (num & 0x0F);
}

void RTC_WriteTime(Data_time *dt)
{
	uint8_t buff[8];
	buff[0] = 0;
	buff[1] = DecimalToBcd(dt->second);
	buff[2] = DecimalToBcd(dt->minute);
	buff[3] = DecimalToBcd(dt->hour);
	buff[4] = DecimalToBcd(dt->day);
	buff[5] = DecimalToBcd(dt->date);
	buff[6] = DecimalToBcd(dt->month);
	buff[7] = DecimalToBcd(dt->year);
	HAL_I2C_Master_Transmit(&hi2c2, RTC_Address, buff, 8, 1000);
}

void RTC_ReadTime(Data_time *dt)
{
	uint8_t read_time[7];
	uint8_t addr_reg = 0;
	HAL_I2C_Master_Transmit(&hi2c2, RTC_Address, &addr_reg, 1, 1000);
	HAL_I2C_Master_Receive(&hi2c2, RTC_Address, read_time, 7, 1000);
	dt->second = BcdToDecimal(read_time[0]);
	dt->minute = BcdToDecimal(read_time[1]);
	dt->hour = BcdToDecimal(read_time[2]);
	dt->day = BcdToDecimal(read_time[3]);
	dt->date = BcdToDecimal(read_time[4]);
	dt->month = BcdToDecimal(read_time[5]);
	dt->year = BcdToDecimal(read_time[6]);
}
char buffer_time[9];
char buffer_day[11];
void RTC_Get_time(void)
{
	RTC_ReadTime(&set_time);
	sprintf(buffer_time,"%02d:%02d:%02d", set_time.hour,set_time.minute,set_time.second);
	Lcd_put_cur(4, 0);
	Lcd_write_string(buffer_time);
	sprintf(buffer_day,"%02d-%02d-20%02d", set_time.date,set_time.month,set_time.year);
	Lcd_put_cur(3, 1);
	Lcd_write_string(buffer_day);

	Rotary_Scroll();
	HAL_Delay(100);
}
