/*
 * KEYPAD_cfg.c
 *
 *  Created on: Aug 29, 2022
 *      Author: Dell
 */



#include "../../LIB/STD_Types.h"
#include "../../MCAL/GPIO/MGPIO_interface.h"
#include "KEYPAD_cfg.h"

const  u8 row =KEYPAD_u8_ROWS_NUM ;
const u8 col = KEYPAD_u8_COLS_NUM;
 const u8 KEYPAD_au8Buttons[KEYPAD_u8_ROWS_NUM][KEYPAD_u8_COLS_NUM] =
{
		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'#','0','=','+'}
};


const u8 KEYPAD_au8RowsPins[KEYPAD_u8_ROWS_NUM]=
{
		_PIN_7,
		_PIN_8,
		_PIN_9,
		_PIN_10

};

const u8 KEYPAD_au8RowsPORT[KEYPAD_u8_ROWS_NUM]=
{
		_GPIOA_PORT,
		_GPIOA_PORT,
		_GPIOA_PORT,
		_GPIOA_PORT

};

const u8 KEYPAD_au8ColsPins[KEYPAD_u8_COLS_NUM]=
{
		_PIN_5,
		_PIN_6,
		_PIN_7,
		_PIN_8

};

const u8 KEYPAD_au8ColsPORT[KEYPAD_u8_COLS_NUM]=
{
		_GPIOB_PORT,
		_GPIOB_PORT,
		_GPIOB_PORT,
		_GPIOB_PORT

};


