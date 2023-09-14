/*
 * DCMOTOR_prg.c
 *
 *  Created on: Aug 31, 2022
 *      Author: Dell
 */
#include "../../LIB/STD_Types.h"
#include "../../MCAL/GPIO/MGPIO_interface.h"
#include "DCMOTOR_inth.h"

u8 Transistor0_PORT;
u8 Transistor0_PIN;
u8 Transistor1_PORT;
u8 Transistor1_PIN;
u8 connection_type;

void DCMOTOR_vidInit(DCMOTOR_tstrOptions* Add_strOptions)
{
	MGPIO_voidSetPinMode(Add_strOptions->Transistor0_PORT ,Add_strOptions->Transistor0_PIN , _MODE_OUTPUT);
	MGPIO_voidSetPinMode(Add_strOptions->Transistor1_PORT ,Add_strOptions->Transistor1_PIN , _MODE_OUTPUT);
	Transistor0_PORT = Add_strOptions->Transistor0_PORT;
	Transistor0_PIN  = Add_strOptions->Transistor0_PIN;
	Transistor1_PORT = Add_strOptions->Transistor1_PORT;
	Transistor1_PIN  = Add_strOptions->Transistor1_PIN;
	connection_type  = Add_strOptions->Connection_Type;
}

void DCMOTOR_enuRotateOneDirection(u8 Copy_u8PORT,u8 Copy_u8PIN,u8 Copy_u8Value)
{
	 MGPIO_voidWriteData(Copy_u8PORT,Copy_u8PIN,Copy_u8Value);
}

void DCMOTOR_enuRotateTwoDirection(u8 Copy_u8Direction)
{

	if(connection_type == DCMOTOR_u8_4NPN_CONNECTION)
	{
		if(Copy_u8Direction == DCMOTOR_u8_CLOCK_WISE)
		 {
			MGPIO_voidWriteData(Transistor0_PORT,Transistor0_PIN,HIGH);
			MGPIO_voidWriteData(Transistor1_PORT,Transistor1_PIN,LOW);
		 }
		else if(Copy_u8Direction == DCMOTOR_u8_COUNTER_CLOCK_WISE)
		 {
			MGPIO_voidWriteData(Transistor0_PORT,Transistor0_PIN,LOW);
			MGPIO_voidWriteData(Transistor1_PORT,Transistor1_PIN,HIGH);
		 }

	}
	else if(connection_type == DCMOTOR_u8_2NPN_2PNP_CONNECTION || connection_type == DCMOTOR_u8_RELAY_CONNECTION)
	{
		        if(Copy_u8Direction == DCMOTOR_u8_CLOCK_WISE)
				 {
					MGPIO_voidWriteData(Transistor0_PORT,Transistor0_PIN,LOW);
					MGPIO_voidWriteData(Transistor1_PORT,Transistor1_PIN,HIGH);
				 }
				else if(Copy_u8Direction == DCMOTOR_u8_COUNTER_CLOCK_WISE)
				 {
					MGPIO_voidWriteData(Transistor0_PORT,Transistor0_PIN,HIGH);
					MGPIO_voidWriteData(Transistor1_PORT,Transistor1_PIN,LOW);
				 }

	}
	else
	{

	}

}
