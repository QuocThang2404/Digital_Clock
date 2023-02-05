/*
 * LCD_1602.c
 *
 *  Created on: Jan 13, 2023
 *      Author: QUOC THANG
 */
#include "LCD_1602.h"
#include "stdio.h"

static    void    lcd_write_command(uint8_t command);
static    void 	  lcd_write_data(uint8_t Data);
static    void    LCD_Configure(void);
static    void    lcd_write( uint8_t Data);


//-----------------------------------------------IMPORTANT_CODE----------------------------------------------------
void lcd_write( uint8_t Data)
{
	HAL_GPIO_WritePin(D4_GPIO_Port,D4_Pin,Data & 0x01);
	HAL_GPIO_WritePin(D5_GPIO_Port,D5_Pin,(Data>>1) & 0x01);
	HAL_GPIO_WritePin(D6_GPIO_Port,D6_Pin,(Data>>2) & 0x01);
	HAL_GPIO_WritePin(D7_GPIO_Port,D7_Pin,(Data>>3) & 0x01);

	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_SET);
	HAL_Delay(1);
	HAL_GPIO_WritePin(EN_GPIO_Port, EN_Pin, GPIO_PIN_RESET); 		// lcd_enable
}


void lcd_write_command(uint8_t command)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_RESET);

	lcd_write(command>>4);
	lcd_write(command);
}

void lcd_write_data( uint8_t data)
{
	HAL_GPIO_WritePin(RS_GPIO_Port, RS_Pin, GPIO_PIN_SET);

	lcd_write(data>>4);
	lcd_write(data);
}
//------------------------------------------------------------------------------------------------------------

//--------------------------------------------FUNCTION------------------------------------------------------------

void Lcd_Init(void)
{
		LCD_Configure();
		lcd_write_command(0x03);								//Di chuyển con trỏ về vị trí đầu màn hình
		lcd_write_command(0x02);								//					//
		lcd_write_command(Function_Set|Function_N);				// 4-bit mode <=> DL = 0
	    lcd_write_command(Clear_display);						// Clear screen
	    lcd_write_command(Display_On_Off | Display_D);			// Lcd-on, cursor-off, no-blink
    	lcd_write_command(Entry_mode | Entry_I_D);			    // Increment cursor
}

void Lcd_write_string(char * string)
{
	for(uint8_t i = 0; i < strlen(string); i++)
	{
		lcd_write_data( string[i]);
	}
}

void Lcd_clear(void)
{
	lcd_write_command(Clear_display);
}

void lcd_clear_xy(uint8_t x, uint8_t y)
{
	Lcd_put_cur(x, y);
	Lcd_write_string(" ");
}

void Lcd_put_cur( uint8_t x, uint8_t y)
{
	uint8_t address;
	if( y == 0) address = (0x80 + x);
	else if( y == 1) address = (0xC0 +x);
	lcd_write_command(address);
}

void Lcd_creat_customchar(unsigned char * Pattern, const char location)
{
	lcd_write_command(0x40 + (location*8));
	int i = 0;
	for(i = 0; i<8; i++)
	{
		lcd_write_data(Pattern[i]);
	}
}
void Lcd_print_customchar(uint8_t data, uint8_t x, uint8_t y)
{
	Lcd_put_cur(x, y);
	lcd_write_data(data);
}

//-----------------------------------------------------------------------------------



//-----------------------------Configure---------------------------------------------
void LCD_Configure()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	// Configure RS_PIN
	GPIO_InitStruct.Pin = RS_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(RS_GPIO_Port, &GPIO_InitStruct);

		// Configure EN_PIN
	GPIO_InitStruct.Pin = EN_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(EN_GPIO_Port, &GPIO_InitStruct);


	 //Configure RW_PIN

	GPIO_InitStruct.Pin = RW_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(RW_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(RW_GPIO_Port,RW_Pin,GPIO_PIN_RESET);

	//Configure RL_PIN

	GPIO_InitStruct.Pin = RL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(RL_GPIO_Port, &GPIO_InitStruct);

	HAL_GPIO_WritePin(RL_GPIO_Port,RL_Pin,GPIO_PIN_SET);

	// Configure D4_PIN
	GPIO_InitStruct.Pin = D4_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(D4_GPIO_Port, &GPIO_InitStruct);

	// Configure D5_PIN
	GPIO_InitStruct.Pin = D5_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(D5_GPIO_Port, &GPIO_InitStruct);

	// Configure D6_PIN
	GPIO_InitStruct.Pin = D6_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(D6_GPIO_Port, &GPIO_InitStruct);

	// Configure D7_PIN
	GPIO_InitStruct.Pin = D7_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(D7_GPIO_Port, &GPIO_InitStruct);

}
