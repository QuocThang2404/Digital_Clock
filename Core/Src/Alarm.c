/*
 * Alarm.c
 *
 *  Created on: 3 thg 2, 2023
 *      Author: QUOC THANG
 */
#include "stdio.h"
#include "LCD_1602.h"
#include "Rotary_encoder.h"
#include "RTC_library.h"
#include "Alarm.h"
#include "Main_menu.h"

extern int hour;
extern int min;
extern int is;
extern int hour_count;
extern int min_count;
extern int button_count;
extern int scroll;

char buff_min[2];
char buff_hour[2];
extern char buffer_time[9];


void Set_hour_1(void)
{
    HAL_Delay(150);
	Lcd_put_cur(4, 0);
	Lcd_write_string("00:00:00");
	while(is == 3 && button_count == 1)
	{
	  Button();
	  Rotary_Hour();
	  sprintf(buff_hour, "%d", hour);
	  Lcd_put_cur(5, 0);
	  Lcd_write_string(buff_hour);
	  if(hour >9)
	  {
		  lcd_clear_xy(6, 0);
		  Lcd_put_cur(6, 0);
		  Lcd_write_string(":");
		  hour_count = 1;
		  is = 7;
		  break;
	  }
	  if(button_count == 0)
	  {
		  is = 6;
		  button_count = 1;// min
		  break;
	  }
	}
}
void Set_hour_2(void)
{
	while(is == 7 && button_count == 1)
	  {
		  Button();
		  Rotary_Hour();
		  sprintf(buff_hour, "%d", hour);
		  Lcd_put_cur(4, 0);
		  Lcd_write_string(buff_hour);
		  if(button_count == 0)
		  {
			  is = 6;
			  button_count = 1;// min
			  break;
		  }
	  }
}

void Set_minute_1(void)
{
	while(is == 6 && button_count == 1)
	  {
		  Button();
		  Rotary_Min();
		  sprintf(buff_min, "%d", min);
		  Lcd_put_cur(8, 0);
		  Lcd_write_string(buff_min);
		  if(button_count == 0)
		  	{
		  		Lcd_put_cur(6, 1);
		  		Lcd_write_string("DONE");
		  		HAL_Delay(1000);
		  		is = 9;
		  		break;
		  	}
		  if(min >9)
		  {
			  lcd_clear_xy(9, 0);
			  Lcd_put_cur(9, 0);
			  Lcd_write_string(":");
			  min_count = 1;
			  is = 8;
			  break;
		  }
	  }
}
void Set_minute_2(void)
{
	while(is == 8 && button_count == 1)
	  {
		  Button();
		  Rotary_Min();
		  sprintf(buff_min, "%d", min);
		  Lcd_put_cur(7, 0);
		  Lcd_write_string(buff_min);
		  if(button_count == 0)
		  {
			  Lcd_put_cur(6, 1);
			  Lcd_write_string("DONE");
			  HAL_Delay(1000);
			  is = 9;
			  break;
		  }
	  }
}
void Check_alarm(void)
{
		RTC_Get_time();
		while(buff_hour[0] == buffer_time[0] && buff_hour[1] == buffer_time[1] && buff_min[0] == buffer_time[3] && buff_min[1] == buffer_time[4])
		{
			RTC_Get_time();
			HAL_Delay(1000);
			Lcd_clear();
			Lcd_put_cur(0, 0);
			Lcd_write_string("****************");
		}
		Lcd_clear();
		Main_menu();
		is = 0;
		scroll = 0;
}

void See_alarm(void)
{
	Lcd_put_cur(6, 0);
	Lcd_write_string(":");
	Lcd_put_cur(9, 0);
	Lcd_write_string(":00");
	if(hour > 9)
	{
		lcd_clear_xy(4, 0);
		Lcd_put_cur(4, 0);
		Lcd_write_string(buff_hour);
	}
	else
	{
		Lcd_put_cur(4, 0);
		Lcd_write_string("0");
		Lcd_put_cur(5, 0);
		Lcd_write_string(buff_hour);
	}
	if(min > 9)
	{
		lcd_clear_xy(7, 0);
		Lcd_put_cur(7, 0);
		Lcd_write_string(buff_min);
	}
	else
	{
		Lcd_put_cur(7, 0);
		Lcd_write_string("0");
		Lcd_put_cur(8, 0);
		Lcd_write_string(buff_min);
	}
	HAL_Delay(100);
	if(button_count == 0)
	{
		Lcd_clear();
		is = 0;
		Main_menu();
	}
}

