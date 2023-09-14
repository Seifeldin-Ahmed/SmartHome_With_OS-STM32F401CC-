

#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATHS.h"

#include "../../MCAL/ADC/ADC_interface.h"
#include "LM35_interface.h"
#include "LM35_config.h"
#include "LM35_private.h"

void LM35_vidInit()
{
	ADC_voidInit();
}

u16 LM35_u16_Get_Temp(u16 copy_channel)
{

	u16 temp;
	u16 Local_u16ReadValue;
	/* Return Digital value*/
	Local_u16ReadValue = ADC_u16Read( copy_channel);
	/*
	 * Analog value = Digital value * V_step
	 * Analog value = Analog value / 1000
	 *  1c ---> 10mv
	 *   ??  ----- analog value in mv
	 *   temp = anaglo value in mv / 10 mv
	 * */
	Local_u16ReadValue = (Local_u16ReadValue * 5000UL)/4096 ;
	temp = Local_u16ReadValue / 10;
	return temp;
}
