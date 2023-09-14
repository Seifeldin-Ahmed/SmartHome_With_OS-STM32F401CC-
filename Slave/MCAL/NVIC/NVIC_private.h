/****************************************************
 *********************************************************************************************************
AUTHOR  : Seifeldin Ahmed
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : NVIC_Driver
File    : Private File
Version :1.0
********************************************************************************************************
*********************************************************þ
*/

#ifndef MCAL_NVIC_NVIC_PRIVATE_H_
#define MCAL_NVIC_NVIC_PRIVATE_H_

typedef struct {

	 u32 NVIC_ISER[8]  ;   // Interrupt set-enable register x
	 u32 Reserved1[24] ;
	 u32 NVIC_ICER[8]  ;   // Interrupt clear-enable register x (NVIC_ICERx)
	 u32 Reserved2[24] ;
	 u32 NVIC_ISPR[8]  ;   // Interrupt set-pending register x (NVIC_ISPRx)
	 u32 Reserved3[24] ;
	 u32 NVIC_ICPR[8]  ;   // Interrupt clear-pending register x (NVIC_ICPRx)
	 u32 Reserved4[24] ;
	 u32 NVIC_IABR[8]  ;   // Interrupt active bit register x (NVIC_IABRx)
	 u32 Reserved5[24] ;
	 u8 NVIC_IPR  [240];   // Interrupt priority register x (NVIC_IPRx) ---> Byte Access able
	 u32 Reserved6[580];
	 u32 STIR          ;   // Software trigger interrupt register (NVIC_STIR)
}MNVIC_T;


#define MNVIC_BASE_ADDRESS         (0XE000E100)
#define NVIC           ((volatile MNVIC_T *)MNVIC_BASE_ADDRESS)
#define Register_bits                    32
#define VICTKEY                      0X05FA0000
#define AIRCR              *((volatile u32 *)0XE000ED0C)


#endif
