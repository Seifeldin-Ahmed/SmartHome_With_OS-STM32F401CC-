/****************************************************
 *********************************************************************************************************
AUTHOR  : Seifeldin Ahmed
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : NVIC_Driver
File    : interface File
Version :1.0
********************************************************************************************************
*********************************************************þ
*/

#ifndef MCAL_NVIC_NVIC_INTERFACE_H_
#define MCAL_NVIC_NVIC_INTERFACE_H_

typedef enum {
	MNVIC_16G_0SG =3, // 0xx --> x:don't care , so we choose 011
	MNVIC_8G_2SG ,    // 100
	MNVIC_4G_4SG ,    // 101
	MNVIC_2G_8SG ,    // 110
	MNVIC_0G_16SG,    // 111
}Group_t;

/******************************* PROTOTYPES  **************þ
**********************************************************/
/* Return type = void
 * Arguments = u8 Copy_u8Interrupt_id
 * Functionality = Enable for any external interrupt (Peripherals)
 * */


void MNVIC_vInterrupt_SetEnable(u8 Copy_u8Interrupt_id);



void MNVIC_vInterrupt_ClearEnable(u8 Copy_u8Interrupt_id);



void MNVIC_SetPriority(u8 Copy_u8Interrupt_id, u8 Copy_u8GroupNumber, u8 Copy_u8SubGroupId);


void MNVIC_SetGroupMode(Group_t Copy_GroupMode);




#endif
