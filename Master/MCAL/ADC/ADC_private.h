/*AUTHOR  : AHMED SHERIF
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : ADC
File    :  ADC_private.h
Version :1.0
********************************************************************************************************
*********************************************************/
#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_



#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATHS.h"
typedef struct{
	u32 SR;
	u32 CR1;
	u32 CR2;
	u32 SMPR1;
	u32 SMPR2;
	u32 JOFRx1;
	u32 JOFRx2;
	u32 HTR;
	u32 LTR;
	u32 SQR1;
	u32 SQR2;
	u32 SQR3;
	u32 JSQR;
	u32 JDR1;
	u32 JDR2;
	u32 JDR3;
	u32 DR;
}ADC_t;

#define ADC_BASE_ADDRESS 0x40012000
#define ADC    ((volatile ADC_t *)ADC_BASE_ADDRESS)
#define	ADC_CCR (*(volatile u32 *)(ADC_BASE_ADDRESS+0x304))
#define RES0	24
#define RES1	25
#define ADON	0
#define SWSTART 30
#define EOC		1
#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
