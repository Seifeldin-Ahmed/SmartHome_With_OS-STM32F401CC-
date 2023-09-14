/*
 * BUZZER_prog.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Seifeldin Ahmed
 */

#include "../../LIB/BIT_MATHS.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/MGPIO_interface.h"
#include "BUZZER_interface.h"


void BUZZER_vInit(u8 Copy_u8PortName , u8 Copy_u8PinNum)
{
	MGPIO_voidSetPinMode(Copy_u8PortName, Copy_u8PinNum, _MODE_OUTPUT);
}


void BUZZER_vTurnOn(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidWriteData(Copy_u8PortName,Copy_u8PinNum, HIGH);

}


void BUZZER_vTurnOFF(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidWriteData(Copy_u8PortName, Copy_u8PinNum, LOW);
}
