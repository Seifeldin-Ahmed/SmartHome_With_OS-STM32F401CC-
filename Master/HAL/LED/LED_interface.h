/*
 * LED_interface.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Dell
 */

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_


void LED_vLedInit(u8 Copy_u8PortName , u8 Copy_u8PinNum);

void LED_vLedTurnOn(u8 Copy_u8PortName, u8 Copy_u8PinNum);


void LED_vLedTurnOFF(u8 Copy_u8PortName, u8 Copy_u8PinNum);

void LED_vLedToggle(u8 Copy_u8PortName, u8 Copy_u8PinNum);

#endif /* HAL_LED_LED_INTERFACE_H_ */
