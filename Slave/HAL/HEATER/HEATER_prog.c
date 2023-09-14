/*
 * HEATER_prog.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Dell
 */


#include "../../LIB/BIT_MATHS.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/MGPIO_interface.h"
#include "HEATER_interface.h"


void HEATER_vInit(u8 Copy_u8PortName , u8 Copy_u8PinNum)
{
	MGPIO_voidSetPinMode(Copy_u8PortName, Copy_u8PinNum, _MODE_OUTPUT);
}
/*
 *  1v ------> 0%
 *  0.75v ---> 25%
 *  0.5v ----> 50%
 *  0.25v----> 75%
 *  0v ------> 100%
 * */

void HEATER_vTurnOn(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidWriteData(Copy_u8PortName,Copy_u8PinNum, LOW);

}

void HEATER_vTurnOFF(u8 Copy_u8PortName, u8 Copy_u8PinNum)
{
	MGPIO_voidWriteData(Copy_u8PortName, Copy_u8PinNum, HIGH);
}
