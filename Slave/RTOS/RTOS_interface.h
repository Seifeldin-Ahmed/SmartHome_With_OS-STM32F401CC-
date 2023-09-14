/*
 * RTOS_interface.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Dell
 */

#ifndef RTOS_RTOS_INTERFACE_H_
#define RTOS_RTOS_INTERFACE_H_

//Return: ErrorState(u8)
u8 RTOS_u8CreateTask(void(*handler)(void),u8 Copy_u8Periodicity,u8 Copy_u8Priority, u8 Copy_u8FirstDelay);



void RTOS_vStart_OS(void);
#endif /* MCAL_RTOS_RTOS_INTERFACE_H_ */
