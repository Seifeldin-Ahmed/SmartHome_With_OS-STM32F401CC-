/*
 * LED_program.c
 *
 *  Created on: Aug 20, 2023
 *      Author: Dell
 */


#include "../../LIB/BIT_MATHS.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/MGPIO_interface.h"
#include "LED_interface.h"


void LED_vLedInit(u8 Copy_u8PortName , u8 Copy_u8PinNum)
{
	MGPIO_voidSetPinMode(Copy_u8PortName, Copy_u8PinNum, _MODE_OUTPUT);
}


void LED_vLedTurnOn(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidWriteData(Copy_u8PortName,Copy_u8PinNum, HIGH);

}


void LED_vLedTurnOFF(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidWriteData(Copy_u8PortName, Copy_u8PinNum, LOW);
}


void LED_vLedToggle(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidTogglePin( Copy_u8PortName , Copy_u8PinNum);
}
