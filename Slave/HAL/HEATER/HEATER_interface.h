/*
 * HEATER_interface.h
 *
 *  Created on: Sep 12, 2023
 *      Author: Dell
 */

#ifndef HAL_HEATER_HEATER_INTERFACE_H_
#define HAL_HEATER_HEATER_INTERFACE_H_


void HEATER_vInit(u8 Copy_u8PortName , u8 Copy_u8PinNum);

void HEATER_vTurnOn(u8 Copy_u8PortName, u8 Copy_u8PinNum);


void HEATER_vTurnOFF(u8 Copy_u8PortName, u8 Copy_u8PinNum);



#endif /* HAL_HEATER_HEATER_INTERFACE_H_ */
