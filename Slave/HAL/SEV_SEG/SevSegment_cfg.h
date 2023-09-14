/*
 * SevSegment_cfg.h
 *
 *  Created on: Aug 25, 2022
 *      Author: Dell
 */

#ifndef HAL_SEVENSEGMENT_SEVSEGMENT_CFG_H_
#define HAL_SEVENSEGMENT_SEVSEGMENT_CFG_H_

#define SevSegment_u8_COM_ANODE      0
#define SevSegment_u8_COM_CATHODE    1


// options (SevSegment_u8_COM_ANODE ,SevSegment_u8_COM_CATHODE )//
#define SevSegment_u8_MODE       SevSegment_u8_COM_ANODE


//*********************************** Options For BCD TO Sev Segment *********************************

#define SevSegment_u8_PIN0             DIO_u8_PIN0
#define SevSegment_u8_PIN1             DIO_u8_PIN1
#define SevSegment_u8_PIN2             DIO_u8_PIN2
#define SevSegment_u8_PIN3             DIO_u8_PIN3

#define SevSegment_u8_PIN0_PORT             DIO_u8_PORTC
#define SevSegment_u8_PIN1_PORT             DIO_u8_PORTC
#define SevSegment_u8_PIN2_PORT             DIO_u8_PORTC
#define SevSegment_u8_PIN3_PORT             DIO_u8_PORTC

#endif /* HAL_SEVENSEGMENT_SEVSEGMENT_CFG_H_ */
