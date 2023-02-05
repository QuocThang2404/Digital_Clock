/*
 * Main_menu.c
 *
 *  Created on: Jan 27, 2023
 *      Author: QUOC THANG
 */
#include "Main_menu.h"
#include "LCD_1602.h"
#include "Rotary_encoder.h"
#include "DHT11_library.h"
#include "RTC_library.h"
#include "Alarm.h"
#include "stdio.h"

extern int count;
extern int scroll;
extern int hour;
extern int min;
int hour_count = 0;
int min_count = 0;
int is =0;
extern int button_count;
//---------------------------------------Custom--------------------------------------
//----------------------------------------UNIT---------------------------------------
unsigned char Temp_C[] = {0x0E,0x0E,0x0E,0x00,0x00,0x00,0x00,0x00};
void Print_Temp_C(void)
{
	Lcd_creat_customchar(Temp_C, 7);
	Lcd_print_customchar(7, 9, 0);
}

unsigned char Percentage[] = {0x18,0x19,0x03,0x06,0x0C,0x18,0x13,0x03};
void Print_Percentage(void)
{
	Lcd_creat_customchar(Percentage, 8);
	Lcd_print_customchar(8, 7, 1);
}

//----------------------------------------ARROW--------------------------------------
unsigned char Arrow[] = {0x00,0x08,0x0C,0x1E,0x0C,0x08,0x00,0x00};

//-----------------------------------------SUN---------------------------------------
unsigned char Sun_1[] = {0x00,0x00,0x0E,0x0C,0x08,0x01,0x03,0x03};
unsigned char Sun_2[] = {0x04,0x0E,0x00,0x0E,0x1F,0x1F,0x1F,0x1F};
unsigned char Sun_3[] = {0x00,0x00,0x0E,0x06,0x02,0x10,0x18,0x1C};
unsigned char Sun_4[] = {0x03,0x03,0x01,0x08,0x0C,0x0E,0x00,0x00};
unsigned char Sun_5[] = {0x1F,0x1F,0x1F,0x1F,0x0E,0x00,0x0E,0x04};
unsigned char Sun_6[] = {0x18,0x18,0x10,0x02,0x06,0x0E,0x00,0x00};
void Print_Sun(void)
{
	  //--------------SUN------------
	  Lcd_creat_customchar(Sun_1, 1);
	  Lcd_creat_customchar(Sun_2, 2);
	  Lcd_creat_customchar(Sun_3, 3);
	  Lcd_creat_customchar(Sun_4, 4);
	  Lcd_creat_customchar(Sun_5, 5);
	  Lcd_creat_customchar(Sun_6, 6);
	  //-----------------------------
	  Lcd_print_customchar(1, 13, 0);
	  Lcd_print_customchar(2, 14, 0);
	  Lcd_print_customchar(3, 15, 0);
	  Lcd_print_customchar(4, 13, 1);
	  Lcd_print_customchar(5, 14, 1);
	  Lcd_print_customchar(6, 15, 1);
}

//----------------------------------------CLOUD--------------------------------------
unsigned char Cloud_1[] = {0x00,0x00,0x00,0x00,0x00,0x0D,0x1F,0x1F};
unsigned char Cloud_2[] = {0x00,0x00,0x00,0x0E,0x1F,0x1F,0x1F,0x1F};
unsigned char Cloud_3[] = {0x00,0x00,0x00,0x00,0x00,0x10,0x1E,0x1F};
unsigned char Cloud_4[] = {0x0F,0x00,0x04,0x02,0x01,0x00,0x00,0x00};
unsigned char Cloud_5[] = {0x1F,0x00,0x12,0x09,0x04,0x00,0x00,0x00};
unsigned char Cloud_6[] = {0x1E,0x00,0x08,0x04,0x12,0x00,0x00,0x00};
void Print_Cloud(void)
{
	  //--------------CLOUD------------
	  Lcd_creat_customchar(Cloud_1, 1);
	  Lcd_creat_customchar(Cloud_2, 2);
	  Lcd_creat_customchar(Cloud_3, 3);
	  Lcd_creat_customchar(Cloud_4, 4);
	  Lcd_creat_customchar(Cloud_5, 5);
	  Lcd_creat_customchar(Cloud_6, 6);
	  //-------------------------------
	  Lcd_print_customchar(1, 13, 0);
	  Lcd_print_customchar(2, 14, 0);
	  Lcd_print_customchar(3, 15, 0);
	  Lcd_print_customchar(4, 13, 1);
	  Lcd_print_customchar(5, 14, 1);
	  Lcd_print_customchar(6, 15, 1);
}

//-----------------------------------------------------------------------------------


//---------------------------------------Function------------------------------------
void Main_menu_Init(void)
{
	Lcd_put_cur(4, 0);
	Lcd_write_string("WELCOME");
	Lcd_put_cur(2, 1);
	Lcd_write_string("TO MY DEVICE");
	HAL_Delay(1000);
	Lcd_clear();
}
void Main_menu(void)
{
	Lcd_creat_customchar(Arrow, 1);
	switch(count)
	{
	case 0:
		Lcd_print_customchar(1, 0, 0);
		lcd_clear_xy(0, 1);
		break;
	case 1:
		Lcd_print_customchar(1, 0, 1);
		lcd_clear_xy(0, 0);
		break;
		default:
			break;
	}
	Lcd_put_cur(1, 0);
	Lcd_write_string("TEMP/RH");
	Lcd_put_cur(1, 1);
	Lcd_write_string("TIME");
}
//-------------------------------------ARROW-------------------------------
void Main_menu_2(void)
{
	switch(count)
	{
		case 0:
		Lcd_print_customchar(1, 0, 0);
		lcd_clear_xy(0, 1);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
		  {
			  Lcd_clear();
			  is= 1;
		  }
		break;
		case 1:
		Lcd_print_customchar(1, 0, 1);
		lcd_clear_xy(0, 0);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
		  {
			  Lcd_clear();
			  is = 2;
		  }
		break;
		default:
			break;
	}
}
//--------------------------------------------------------------------------
void Main_begin_2(void)
{
	  while(button_count == 1 && is == 0 )
	  	{
		  Rotary_encoder_Handle();
		  Main_menu_2();
	  	}
}


void Menu_set_Time_Alarm(void)
{
	switch(scroll)
		{
		case 0:
		Lcd_print_customchar(1, 0, 0);
		lcd_clear_xy(0, 1);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
		  {
			  Lcd_clear();
			  is= 3;
		  }
		break;
		case 1:
		Lcd_print_customchar(1, 0, 1);
		lcd_clear_xy(0, 0);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 0)
		  {
			  Lcd_clear();
			  is = 4;
		  }
		break;
		default:
			break;
		}
}

void Menu_1(void)
{
	Lcd_put_cur(1, 0);
	Lcd_write_string("SET ALARM");
	Lcd_put_cur(1, 1);
	Lcd_write_string("SEE YOUR ALARM");
	lcd_clear_xy(10, 0);
	lcd_clear_xy(11, 0);
}

void Inside(void)
{
	Button();
	  if(is == 1 && count  == 0)
	  {
		  	  Rotary_encoder_Handle();
		  	  Button();
			  Get_data_DHT11();
			  if(button_count == 0)
			  {
				  Lcd_clear();
				  is = 0;
				  count  = 0;
				  Main_menu();
			  }
	  }
	  else if(is == 2 && count == 1)
	  {
		  while(button_count == 1 && is == 2)
		  {
			  Button();
			  RTC_Get_time();
			  if(scroll == 3)
			  {
				is = 5;
				count = 0;
				scroll = 0;
				break;
			  }
		  }
		  if(button_count == 0)
		  {
			  Lcd_clear();
			  is = 0;
			  count = 1;
			  Main_menu();
		  }
	  }
	  else if(is == 3) // Set Alarm
	  {
		  Set_hour_1();
	  }
	  else if(is == 4)
	  {
		  See_alarm();
	  }
	  else if(is == 5)
	  {
		  Menu_1();
		  while(button_count == 1 && is == 5)
		  {
			  Rotary_Scroll();
			  Menu_set_Time_Alarm();
			  if(button_count == 0)
			  {
				  Lcd_clear();
				  is = 0;
				  Main_menu();
			  }
		  }
	  }
	  else if(is == 6) // MINUTE
	  {
		  Set_minute_1();
	  }
	  else if(is == 7 && hour_count == 1)
	  {
		  Set_hour_2();
	  }
	  else if(is == 8 && min_count == 1)
	  {
		  Set_minute_2();
	  }
	  else if(is == 9)
	  {
		  while(button_count == 1 && is == 9)
		  {
 			  Check_alarm();
		  }
	  }
	  else
	  {
		  Main_menu();
	  }
}

