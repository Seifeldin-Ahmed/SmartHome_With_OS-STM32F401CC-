/*
 * UART_interface.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_INTERFACE_H_
#define MCAL_UART_UART_INTERFACE_H_


typedef struct
{
	u16 UART_Mode;
	u16 UART_ParityBit;
	u16 UART_PStopBits;
	u16 UART_WordLength;
	u32 UART_BaudRate;
    u16 UART_Interrupt_Enable;
    void (* p_IRQ_CallBack)(void);
}UART_tstrConfiguration;


enum Polling_Mechanism{
	enable,
	disable
};
/***************************************************** Interrupt Options *********************************************************/
#define UART_INT_DISABLE                     (u32)0x00
#define UART_INT_ENABLE_TXE                  (u32)0x80     //Transmit Data Register Empty
#define UART_INT_ENABLE_TC                   (u32)0x40     //Transmission Compelete
#define UART_INT_ENABLE_RXNEIE               (u32)0x20     //Received data ready to be read
#define UART_INT_ENABLE_PE                   (u32)0x100    //Parity Error
//*******************************************************************************************************************************



//***************************************************** Mode Options ************************************************************
#define UART_Transmite                      (u32)0x08
#define UART_Recieve                        (u32)0x04
#define UART_FULL_DUPLEX                    (u32)0x0C
//*******************************************************************************************************************************


//***************************************************** Parity Bit Options ******************************************************
#define UART_EVEN_PARITY                    (u32)0X200  //   0010 0000 0000  --> bit10: PCE(Parity Control Enable)=1 , bit9: PS(Parity Selection) =0
#define UART_ODD_PARITY                     (u32)0X0300 //   0011 0000 0000  --> bit10: PCE(Parity Control Enable)=1 , bit9: PS(Parity Selection) =1
#define UART_NONE_PARITY					(u32)0X00
//*******************************************************************************************************************************

//**************************************************** Stop Bit Options *********************************************************
#define UART_HALF_STOP_BIT                   (u32)0X1000     //0001 0000 0000 0000
#define UART_ONE_STOP_BIT                    (u32)0X0000     //0000 0000 0000 0000
#define UART_ONE_HALF_STOP_BIT               (u32)0X3000     //0011 0000 0000 0000
#define UART_TWO_STOP_BIT                    (u32)0X2000     //0010 0000 0000 0000
//*******************************************************************************************************************************



//**************************************************** Word Length Options ***************************************************

#define UART_EIGHT_DATA_BITS                (u32)0X0
#define UART_NINE_DATA_BITS                 (u32)0X1000
//*******************************************************************************************************************************



//*************************************************** Baud rate Options *************************************************************
#define UART_BAUDRATE_2400                  2400
#define UART_BAUDRATE_9600                  9600
#define UART_BAUDRATE_19200           		19200
#define UART_BAUDRATE_57600            	    5760
#define UART_BAUDRATE_115200                115200
#define UART_BAUDRATE_230400                230400
#define UART_BAUDRATE_460800                460800
#define UART_BAUDRATE_921600                921600
#define UART_BAUDRATE_2250000               2250000
#define UART_BAUDRATE_4500000               4500000
/************************************************************************************************************************************/


/************************************************* UART Numbers *********************************************************************/
#define UART_1                        0
#define UART_2                        1
#define UART_6                        3
/************************************************************************************************************************************/

void UART_vInit(u8 Copy_u8UartNumber, UART_tstrConfiguration* Add_pstrConfigue);


void UART_vTransmite(u8 Copy_u8UartNumber, u16 Copy_u8Data, enum Polling_Mechanism PollingEN);


u8 UART_u8Recive(u8 Copy_u8UartNumber, enum Polling_Mechanism PollingEN);

/* to do :
 * void UART_vEnable(u8 Copy_u8UartNumber);

   void UART_vDisable(u8 Copy_u8UartNumber);

   void UART_vTransmiteString(u8* Add_u8Data);

 * */

#endif /* MCAL_UART_UART_INTERFACE_H_ */
