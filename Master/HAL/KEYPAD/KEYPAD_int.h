/*
 * KEYPAD_int.h
 *
 *  Created on: Aug 29, 2022
 *      Author: Dell
 */

#ifndef HAL_KEYPAD_KEYPAD_INT_H_
#define HAL_KEYPAD_KEYPAD_INT_H_

// check error status //

typedef enum {
	KEYPAD_OK,
	KEYPAD_NOK
}KEYPAD_tenuErrorStatus;


#define KEYPAD_u8_NOTPRESSED 100

void KEYPAD_vidInit();


KEYPAD_tenuErrorStatus KEYPAD_enuGetPressedKey(u8 *Add_u8KeyValue);


#endif /* HAL_KEYPAD_KEYPAD_INT_H_ */
