/*
 * LCD_int.h
 *
 *  Created on: Aug 26, 2022
 *      Author: Dell
 */

#ifndef HAL_LCD_LCD_INT_H_
#define HAL_LCD_LCD_INT_H_

#include "LCD_cfg.h"

// Check Error Status //
typedef enum
{
  LCD_OK,
  LCD_NOK
}LCD_enutErrorStatus;


// Macros for Instruction //

//1- Clear Display //
#define LCD_u8_CLEAR_DISPLAY                         0X01 // set 0x20 at every location of ddram , and make AC=0x00

//2- Return Home //
#define LCD_u8_RETURN_HOME                           0X02 // set AC to 0x00



//3- Entry Mode Set // (increase or decreasing cursor && shifting  , happens when i write a character )
#define LCD_u8_CURSOR_INC_SHIFT_OFF                  0x06
#define LCD_u8_CURSOR_DEC_SHIFT_OFF                  0X04
#define LCD_u8_CURSOR_INC_SHIFT_ON                   0X07 // every time i write a character the cursor increase then the display shift left, so the cursor would look like as if it standstill
#define LCD_u8_CURSOR_DEC_SHIFT_ON                   0X05 // don't work on protous, only work in hardware

// 4- Display On/Off Control //
#define LCD_u8_DISPLAY_OFF                           0X08
#define LCD_u8_DISPLAY_ON_CURSOR_OFF                 0X0C
#define LCD_u8_DISPLAY_ON_CURSOR_ON                  0X0E
#define LCD_u8_DISPLAY_ON_CURSOR_ON_BLINK_ON         0X0F

// 5- Cursor or Display Shift //     (increase or decreasing cursor && shifting  , happens whithout  writing a character )
#define LCD_u8_SHIFT_CURSOR_LEFT			         0X10 // every time I send this instruction, the cursor decrease by 1
#define LCD_u8_SHIFT_CURSOR_RIGHT			         0X14
#define LCD_u8_SHIFT_DISPLAY_CURSOR_LEFT			 0X18
#define LCD_u8_SHIFT_DISPLAY_CURSOR_RIGHT			 0X1C

// 6- Function Set //
#define LCD_u8_FUNCTION_SET        0X20 | LCD_u8_DATA_LENGTH_MODE | LCD_u8_NUMBER_OF_LINES | LCD_u8_FONT_MODE

//CHECK INSTRUCTIONS//
#define LCD_u8_CHECK_INSTRUCTIONS(INSTRUCTION)  (INSTRUCTION==LCD_u8_CLEAR_DISPLAY)                   ||     \
		                                        (INSTRUCTION==LCD_u8_RETURN_HOME)                     ||     \
                                                (INSTRUCTION==LCD_u8_CURSOR_INC_SHIFT_OFF)            ||     \
                                                (INSTRUCTION==LCD_u8_CURSOR_DEC_SHIFT_OFF)            ||     \
                                                (INSTRUCTION==LCD_u8_CURSOR_INC_SHIFT_ON)             ||     \
                                                (INSTRUCTION==LCD_u8_CURSOR_DEC_SHIFT_ON)             ||     \
                                                (INSTRUCTION==LCD_u8_DISPLAY_OFF)                     ||     \
                                                (INSTRUCTION==LCD_u8_DISPLAY_ON_CURSOR_OFF)           ||     \
                                                (INSTRUCTION==LCD_u8_DISPLAY_ON_CURSOR_ON)            ||     \
                                                (INSTRUCTION==LCD_u8_DISPLAY_ON_CURSOR_ON_BLINK_ON)   ||     \
												(INSTRUCTION==LCD_u8_SHIFT_CURSOR_LEFT )              ||     \
												(INSTRUCTION==LCD_u8_SHIFT_CURSOR_RIGHT)              ||     \
												(INSTRUCTION==LCD_u8_SHIFT_DISPLAY_CURSOR_LEFT)       ||     \
												(INSTRUCTION==LCD_u8_SHIFT_DISPLAY_CURSOR_RIGHT)      ||     \
                                                (INSTRUCTION==LCD_u8_FIRST_CGRAM_ADDRESS)             ||     \
												(INSTRUCTION==LCD_u8_FIRST_DDRAM_ADDRESS)

// addresses //
#define LCD_u8_FIRST_CGRAM_ADDRESS			0X40
#define LCD_u8_FIRST_DDRAM_ADDRESS			0X80 // 1 000 0000 >> first 7 bits will be assigned to AC ----- the MSB just tell the mc of lcd to put this 7 bits into AC


/* macros for row and column */
#define LCD_u8_ROW0		0X00
#define LCD_u8_ROW1		0X01

#define LCD_u8_COL0		0X00
#define LCD_u8_COL1		0X01
#define LCD_u8_COL2		0X02
#define LCD_u8_COL3		0X03
#define LCD_u8_COL4		0X04
#define LCD_u8_COL5		0X05
#define LCD_u8_COL6		0X06
#define LCD_u8_COL7		0X07
#define LCD_u8_COL8		0X08
#define LCD_u8_COL9		0X09
#define LCD_u8_COL10	0X0A
#define LCD_u8_COL11	0X0B
#define LCD_u8_COL12	0X0C
#define LCD_u8_COL13	0X0D
#define LCD_u8_COL14	0X0E
#define LCD_u8_COL15	0X0F



// Needed Functions //


/* Name:LCD_VidInit
 * Description: initialize the LCD in 8 bit mode
 * Argument: void
 * Return: void
 * */
void LCD_VidInit(void);


/* name: LCD_enuSendCharacter
 * Description: send ASCII CODE Character to LCD Microcontroller
 * Argument: Copy_u8Character   (The Desired Character to be Displayed)
 * Return: void
 * */
void LCD_enuSendCharacter(u8 Copy_u8Character);



/* name: LCD_enuSendInstruction
 * Description: send instruction to LCD Microcontroller
 * Argument: Copy_u8Instruction   (The Desired Instruction to be Executed)
 * Return: Error Status >>>>> LCD_OK , LCD_NOK
 * */
LCD_enutErrorStatus LCD_enuSendInstruction(u8 Copy_u8Instruction);



/* name: LCD_enuGoTo
 * Description: send Ac to desired addresss in DDRAM
 * Argument:            First Argument: Copy_u8Row          options(LCD_u8_ROW0,LCD_u8_ROW1)
 *                     Second Argument: Copy_u8Col          options(LCD_u8_COL0,LCD_u8_COL15)
 * Return: Error Status >>>>> LCD_OK , LCD_NOK
 * */
LCD_enutErrorStatus LCD_enuGoTo(u8 Copy_u8Row , u8 Copy_u8Col);


/* name: LCD_enuSendString
 * Description: sendcharchters to LCD_enuSendCharacter fundtion
 * Argument: Add_pu8String   (array of characters)
 * Return: Error Status >>>>> LCD_OK , LCD_NOK
 * */
LCD_enutErrorStatus	LCD_enuSendString( u8* Add_pu8String);



/* name: LCD_enuSendCustomCharacter
 * Description: generate custom character to the CGRAM
 * Argument:           First Argument:   Add_u8Pattern      (the desired array to be generated)
 *                    Second Argument:   Copy_u8NumOfBlock  (the number of block in the DDRAM )
 *                     Third Argument:   Copy_u8Row          options(LCD_u8_ROW0,LCD_u8_ROW1)
 *                    Fourth Argument:   Copy_u8Col          options(LCD_u8_COL0,LCD_u8_COL15)
 * Return: Error Status >>>>> LCD_OK , LCD_NOK
 * */
LCD_enutErrorStatus LCD_enuSendCustomCharacter(u8 *Add_u8Pattern,u8 Copy_u8NumOfBlock , u8 Copy_u8Row , u8 Copy_u8Col);





void LCD_enuSendNumber(u32 Copy_u32Number);



#endif /* HAL_LCD_LCD_INT_H_ */

