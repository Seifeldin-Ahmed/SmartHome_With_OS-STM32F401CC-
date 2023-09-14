/****************************************************
 *********************************************************************************************************
AUTHOR  : Seifeldin Ahmed
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : NVIC_Driver
File    : source File
Version :1.0
********************************************************************************************************
*********************************************************þ
*/

#include "../../LIB/BIT_MATHS.h"
#include "../../LIB/STD_TYPES.h"
#include "NVIC_interface.h"
#include "NVIC_private.h"


/******************************************* APIS Definition *****************************/


void MNVIC_vInterrupt_SetEnable(u8 Copy_u8Interrupt_id)
 {
     u8 register_number = Copy_u8Interrupt_id / Register_bits ;
     u8 Bit_number      = Copy_u8Interrupt_id % Register_bits ;
     NVIC->NVIC_ISER[register_number] |= (1<<Bit_number);
 }



 /****************************************************************************************************
 *****************************************************************************************************/


 void MNVIC_vInterrupt_ClearEnable(u8 Copy_u8Interrupt_id)
 {
	  u8 register_number = Copy_u8Interrupt_id / Register_bits ;
	  u8 Bit_number      = Copy_u8Interrupt_id % Register_bits ;
	  NVIC->NVIC_ICER[register_number] |= (1<<Bit_number);
 }


 /****************************************************************************************************
 *****************************************************************************************************/



/*  Name          : MNVIC_SetGroupMode
 *  Return type   : void
 *  Functionality : Set Configuration on SCB Peripheral
 * */

 u8 Global_u8GroupMode;

 void MNVIC_SetGroupMode(Group_t Copy_GroupMode)
 {
	 Global_u8GroupMode  = Copy_GroupMode;
	 u32 AIRCR_VALUE = VICTKEY | (Global_u8GroupMode << 8);
	 AIRCR = AIRCR_VALUE;
 }



 /****************************************************************************************************
 *****************************************************************************************************/


 void MNVIC_SetPriority(u8 Copy_u8Interrupt_id, u8 Copy_u8GroupNumber, u8 Copy_u8SubGroupId)
 {
	 switch(Copy_u8GroupNumber)
	 {
	   case MNVIC_16G_0SG : NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8GroupNumber<<4); break;
	   case MNVIC_8G_2SG  : NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8GroupNumber<<5); NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8SubGroupId<<4); break;
	   case MNVIC_4G_4SG  : NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8GroupNumber<<6); NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8SubGroupId<<4); break;
	   case MNVIC_2G_8SG  : NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8GroupNumber<<7); NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8SubGroupId<<4); break;
	   case MNVIC_0G_16SG : NVIC->NVIC_IPR[Copy_u8Interrupt_id] |= (Copy_u8SubGroupId<<4 ); break;
	   default: break;
	 }

 }
