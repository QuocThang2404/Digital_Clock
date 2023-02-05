/*
 * Main_menu.h
 *
 *  Created on: Jan 27, 2023
 *      Author: QUOC THANG
 */

#ifndef INC_MAIN_MENU_H_
#define INC_MAIN_MENU_H_
#include "stm32f1xx_hal.h"
//-------------------------------
void Main_menu_Init(void);
void Main_menu(void);
void Inside(void);
void Menu_1(void);
void Main_begin_2(void);
void Main_menu_2(void);
//-------------------------------
void Print_Sun(void);
void Print_Cloud(void);
void Print_Temp_C(void);
void Print_Percentage(void);
//-------------------------------
#endif /* INC_MAIN_MENU_H_ */
