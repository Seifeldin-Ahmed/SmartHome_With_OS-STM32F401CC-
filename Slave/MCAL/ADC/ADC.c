/*AUTHOR  : AHMED SHERIF
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : ADC
File    :  ADC.c
Version :1.0
********************************************************************************************************
*********************************************************/
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATHS.h"


#include"ADC_private.h"
#include"ADC_config.h"
#include"ADC_interface.h"



void ADC_voidInit()
{
	#if RESOLUTION == _12_BIT
		CLEAR_BIT(ADC->CR1,RES0);
		CLEAR_BIT(ADC->CR1,RES1);
	#elif RESOLUTION == _10_BIT
		SET_BIT(ADC->CR1,RES0);
		CLEAR_BIT(ADC->CR1,RES1);
	#elif RESOLUTION == _8_BIT
		CLEAR_BIT(ADC->CR1,RES0);
		SET_BIT(ADC->CR1,RES1);
	#elif RESOLUTION == _8_BIT
		SET_BIT(ADC->CR1,RES0);
		SET_BIT(ADC->CR1,RES1);
#endif

SET_BIT(ADC_CCR,23);//VREFINT enable
SET_BIT(ADC->CR2,ADON);//ENABLE ADC
}


u16 ADC_u16Read(u16 copy_channel)
{
	ADC->SQR3=0x00000000; // WRITE 0 TO PREVENT CONFLICT
	ADC->SQR3=copy_channel;

	SET_BIT(ADC->CR2,SWSTART);//START CONVERSION
	while(!GET_BIT(ADC->SR,EOC));
	return ADC->DR;

}
