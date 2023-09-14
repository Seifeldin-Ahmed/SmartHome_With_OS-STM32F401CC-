/*
 * RTOS_private.h
 *
 *  Created on: Aug 16, 2023
 *      Author: Dell
 */

#ifndef RTOS_RTOS_PRIVATE_H_
#define RTOS_RTOS_PRIVATE_H_

typedef enum{
	Suspend ,
	Ready
}Task_State ;


typedef struct {

	void (*TaskHandler)(void);
	u8 periodicity ;
	u8 firstdelay;
	Task_State Tstate;
}Task;



#endif /* MCAL_RTOS_RTOS_PRIVATE_H_ */
