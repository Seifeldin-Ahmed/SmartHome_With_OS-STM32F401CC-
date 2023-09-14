/*
 * HC_SR04_Program.c
 *
 *  Created on: Sep 13, 2023
 *      Author: Michael-Malak
 */


#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATHS.h"

#include "HC_SR04_Interface.h"

#include "../../MCAL/GPIO/MGPIO_Interface.h"
#include "../../MCAL/SysTick/SysTick_interface.h"
#define SystemCoreClock 16000000UL


void HC_SR04_Trigger(u8 TRIG_PORT,u8 TRIG_PIN) {



	MGPIO_voidWriteData(TRIG_PORT, TRIG_PIN, HIGH);

	Systic_vDelay_us(10); // Delay for at least 10us

	MGPIO_voidWriteData(TRIG_PORT, TRIG_PIN, LOW);

}


u32 HC_SR04_GetDistance(u8 TRIG_PORT, u8 TRIG_PIN, u8 ECHO_PORT, u8 ECHO_PIN) {
    // Send a trigger pulse
    HC_SR04_Trigger(TRIG_PORT, TRIG_PIN);

    // Wait for the ECHO pin to go high (start of the pulse)
    while (MGPIO_u8ReadData(ECHO_PORT, ECHO_PIN) == 0);
     SysTick_start_time();
    // Start the timer

    // Wait for the ECHO pin to go low (end of the pulse)
    while (MGPIO_u8ReadData(ECHO_PORT, ECHO_PIN) == 1);

    // Stop the timer
    u32 endTime = SysTick_stop_and_return_time();

    // Calculate the pulse duration in microseconds
    u32 pulseDuration = (0xffffff-1) - endTime;

    pulseDuration=(pulseDuration)/SystemCoreClock;

    // Calculate the distance in centimeters
    // Speed of sound at sea level is approximately 343 meters per second or 34300 centimeters per second
    u32 distance = (pulseDuration * 34300) / 2.0; // Divide by 2 for one-way trip

    return distance;
}
