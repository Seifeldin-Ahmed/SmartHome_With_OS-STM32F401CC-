/*
 * BUZZER_interface.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Dell
 */

#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_

void BUZZER_vInit(u8 Copy_u8PortName , u8 Copy_u8PinNum);

void BUZZER_vTurnOn(u8 Copy_u8PortName, u8 Copy_u8PinNum);


void BUZZER_vTurnOFF(u8 Copy_u8PortName, u8 Copy_u8PinNum);



#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
