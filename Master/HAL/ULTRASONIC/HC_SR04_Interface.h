/*
 * HC_SR04_Interface.h
 *
 *  Created on: Sep 13, 2023
 *      Author: Michael-Malak
 */

#ifndef INC_HC_SR04_INTERFACE_H_
#define INC_HC_SR04_INTERFACE_H_

void HC_SR04_Trigger(u8 TRIG_PORT,u8 TRIG_PIN);

u32 HC_SR04_GetDistance(u8 TRIG_PORT, u8 TRIG_PIN, u8 ECHO_PORT, u8 ECHO_PIN);



#endif /* INC_HC_SR04_INTERFACE_H_ */
