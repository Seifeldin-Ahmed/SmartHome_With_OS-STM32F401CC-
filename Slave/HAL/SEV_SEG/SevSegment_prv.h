/*
 * SevSegment_prv.h

 *
 *  Created on: Aug 25, 2022
 *      Author: Seif
 */

#ifndef HAL_SEVENSEGMENT_SEVSEGMENT_PRV_H_
#define HAL_SEVENSEGMENT_SEVSEGMENT_PRV_H_

#if  SevSegment_u8_MODE==SevSegment_u8_COM_CATHODE

// common cathode //
#define SevSegment_u8_ZERO       0x3F
#define SevSegment_u8_ONE        0x06
#define SevSegment_u8_TWO        0x5B
#define SevSegment_u8_THREE      0x4F
#define SevSegment_u8_FOUR       0x66
#define SevSegment_u8_FIVE       0x6D
#define SevSegment_u8_SIX        0x7d
#define SevSegment_u8_SEVEN      0x07
#define SevSegment_u8_EIGHT      0x7F
#define SevSegment_u8_NINE       0x6F

#elif  SevSegment_u8_MODE==SevSegment_u8_COM_ANODE
//common anode //
#define SevSegment_u8_ZERO       0xC0
#define SevSegment_u8_ONE        0xF9
#define SevSegment_u8_TWO        0xA4
#define SevSegment_u8_THREE      0xB0
#define SevSegment_u8_FOUR       0x99
#define SevSegment_u8_FIVE       0x92
#define SevSegment_u8_SIX        0x82
#define SevSegment_u8_SEVEN      0xF8
#define SevSegment_u8_EIGHT      0x80
#define SevSegment_u8_NINE       0x90

#endif

#endif /* HAL_SEVENSEGMENT_SEVSEGMENT_PRV_H_ */
