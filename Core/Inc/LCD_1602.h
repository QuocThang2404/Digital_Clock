/*
 * LCD_1602.h
 *
 *  Created on: Jan 13, 2023
 *      Author: QUOC THANG
 */

#ifndef INC_LCD_1602_H_
#define INC_LCD_1602_H_

#include "stm32f1xx_hal.h"
#include "string.h"

//-------------Pin---------------------
#define RS_Pin           GPIO_PIN_12
#define RS_GPIO_Port     GPIOB

#define RW_Pin           GPIO_PIN_13
#define RW_GPIO_Port     GPIOB

#define EN_Pin           GPIO_PIN_14
#define EN_GPIO_Port     GPIOB

#define RL_Pin           GPIO_PIN_15
#define RL_GPIO_Port     GPIOB

#define D4_Pin           GPIO_PIN_8
#define D4_GPIO_Port     GPIOA

#define D5_Pin           GPIO_PIN_9
#define D5_GPIO_Port     GPIOA

#define D6_Pin           GPIO_PIN_10
#define D6_GPIO_Port     GPIOA

#define D7_Pin           GPIO_PIN_11
#define D7_GPIO_Port     GPIOA
//----------------------------------------


////----------Register_Command--------------
#define Clear_display			0x01
#define Return_home 			0x02
#define Entry_mode				0x04
#define Display_On_Off			0x08
#define Cursor_display_shift	0x10
#define Function_Set			0x20
#define LINE					2
#define Start_Line_1			0x00
#define Start_Line_2			0x40
////--------Entry_mode_set-------------
#define Entry_S					0x01
#define Entry_I_D				0x02
//
////---------LCD_Control---------------
#define Display_B				0x01
#define Display_C				0x02
#define Display_D				0x04
//
////--------Cursor_Diplay_Shift-------------
#define CDS_RL					0x04
#define CDS_SC					0x08

////--------Function_Set-------------------
#define Function_F				0x04
#define Function_N				0x08
#define Function_DL				0x10

//------------------------------------FUNCTION---------------------------------
void    Lcd_Init(void);
void    Lcd_put_cur( uint8_t x, uint8_t y);
void    Lcd_clear(void);
void    Lcd_write_string(char * string);
void 	Lcd_creat_customchar(unsigned char * Pattern, const char location);
void 	Lcd_print_customchar(uint8_t data, uint8_t x, uint8_t y);
void 	lcd_clear_xy(uint8_t x, uint8_t y);

#endif /* INC_LCD_1602_H_ */
