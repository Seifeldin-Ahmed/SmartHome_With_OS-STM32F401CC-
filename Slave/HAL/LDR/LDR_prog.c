/*
 * LDR_prog.c
 *
 *  Created on: Sep 12, 2023
 *      Author: Dell
 */

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATHS.h"

#include "../../MCAL/ADC/ADC_interface.h"
#include "LDR_interface.h"





void LDR_vidInit(void)
{
	ADC_voidInit();
}

u32 LDR_u32_Get_value(u16 copy_channel)
{
	u32 Local_u32ReadValue;
	Local_u32ReadValue = ADC_u16Read( copy_channel);
	/*
	 *  Vo = (Vcc* Rldr) / (RLDR*R)
	 *
	 *  4091 --> Dark
	 *  1365 --> Light
	 * */
//	Local_u16ReadValue = (Local_u16ReadValue * 5000ul)/4096;
//	Local_u16ReadValue = (1-(Local_u16ReadValue/(4.99*1000ul)))*100;
	Local_u32ReadValue =( ((Local_u32ReadValue - 1365) * 100) / 2726 ); // 272 600
    return Local_u32ReadValue;
}
