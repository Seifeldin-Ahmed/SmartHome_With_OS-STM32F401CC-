/****************************************************
 *********************************************************************************************************
AUTHOR  : Seifeldin Ahmed
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : UART_Driver
File    : source File
Version :1.0
********************************************************************************************************
*********************************************************þ
*/

#include "../../LIB/BIT_MATHS.h"
#include "../../LIB/STD_TYPES.h"
#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"
#include "../NVIC/NVIC_interface.h"



#define USARTDIV(__PCLK__,__BAUD__)             (u32) (__PCLK__/(16 * __BAUD__)) //19
#define USARTDIV_MUL100(__PCLK__,__BAUD__)      (u32) ( (25*__PCLK__) / (4 *__BAUD__) ) //1953
#define MANTISSA_MUL100(__PCLK__,__BAUD__)      (u32) (USARTDIV(__PCLK__,__BAUD__)* 100) // 19*100 = 1900
#define MANTISSA(__PCLK__,__BAUD__)             (u32) (USARTDIV(__PCLK__,__BAUD__))//19
#define DIV_FRACTION(__PCLK__,__BAUD__)         (u32) (   (    (    (USARTDIV_MUL100(__PCLK__,__BAUD__)) - (MANTISSA_MUL100(__PCLK__,__BAUD__))    ) * 16   )   / 100   ) // (1953 - 1900) * 16 / 100 = 53 * 16 / 100 --->(0.53*16)
#define UART_BRR_Register(__PCLK__,__BAUD__)    (u32) (    ((MANTISSA(__PCLK__,__BAUD__)) << 4)    |    ((DIV_FRACTION(__PCLK__,__BAUD__)) & 0x0f)   )



/* ===============================================================================================================
 *                                                Generic Vairables
 * ===============================================================================================================
 * */

UART_tstrConfiguration* Global_Uart_Config1=NULL;
UART_tstrConfiguration* Global_Uart_Config2=NULL;
UART_tstrConfiguration* Global_Uart_Config6=NULL;


/* ===============================================================================================================
 *                                                     APIs
 * ===============================================================================================================
 * */

void UART_vInit(u8 Copy_u8UartNumber, UART_tstrConfiguration* Add_pstrConfigue)
{

   switch(Copy_u8UartNumber)
   {
        case UART_1:
        	    Global_Uart_Config1 = Add_pstrConfigue; //buffer the Add_pstrConfigue
        		//Enable USART Module
        		//Bit 13 UE: USART Enable
        		UART1->USART_CR1 |= 1<<13;


        		//Enable USART Tx and Rx engines accordingto the UART_Mode Configuration item
        		// USART_CR1  bit3(TE): Transmitter enable     &    bit2(RE): Receiver enable
        		UART1->USART_CR1   |=  Add_pstrConfigue->UART_Mode;


        		//Data Length
        		UART1->USART_CR1   |=  Add_pstrConfigue->UART_WordLength;


        		//Configuration of Parity Control bit Fields
        		//USART_C1   bit10(PCE): Parity Control Enable    &    bit9(PS): Parity Selection
        		UART1->USART_CR1   |=  Add_pstrConfigue->UART_ParityBit;


        		//Configure the number of stop bits
        		//USART_C2   bits 13:12
        		UART1->USART_CR2   |=  Add_pstrConfigue->UART_PStopBits;


        		//Configuration of BRR(Baudrate Register)
        	    // APB2, PCLK2 --->  for USART1,6
        		// APB1, PCLK1 --->  for USART2
        		 UART1->USART_BRR    =  (UART_BRR_Register(PCLK2 , Add_pstrConfigue->UART_BaudRate)) ;

        		 if(Add_pstrConfigue->UART_Interrupt_Enable != UART_INT_DISABLE)
        		 {
        			 UART1->USART_CR1 |= (Add_pstrConfigue->UART_Interrupt_Enable);
        			 MNVIC_vInterrupt_SetEnable(37); //enable uart1 from nvic
        		 }
        		 break;

        case UART_2:
    	        Global_Uart_Config2 = Add_pstrConfigue; //buffer the Add_pstrConfigue
        		//Enable USART Module
        		//Bit 13 UE: USART Enable
        		UART2->USART_CR1 |= 1<<13;


        		//Enable USART Tx and Rx engines accordingto the UART_Mode Configuration item
        		// USART_CR1  bit3(TE): Transmitter enable     &    bit2(RE): Receiver enable
        		UART2->USART_CR1   |=  Add_pstrConfigue->UART_Mode;


        		//Data Length
        		UART2->USART_CR1   |=  Add_pstrConfigue->UART_WordLength;


        		//Configuration of Parity Control bit Fields
        		//USART_C1   bit10(PCE): Parity Control Enable    &    bit9(PS): Parity Selection
        		UART2->USART_CR1   |=  Add_pstrConfigue->UART_ParityBit;


        		//Configure the number of stop bits
        		//USART_C2   bits 13:12
        		UART2->USART_CR2   |=  Add_pstrConfigue->UART_PStopBits;


        		//Configuration of BRR(Baudrate Register)
        	    // APB2, PCLK2 --->  for USART1,6
        		// APB1, PCLK1 --->  for USART2
        		UART2->USART_BRR    =  UART_BRR_Register( PCLK1 , Add_pstrConfigue->UART_BaudRate );

        		 if(Add_pstrConfigue->UART_Interrupt_Enable != UART_INT_DISABLE)
        		 {
        			 UART2->USART_CR1 |= (Add_pstrConfigue->UART_Interrupt_Enable);
        			 MNVIC_vInterrupt_SetEnable(38);  //enable uart2 from nvic
        		 }
        		 break;

        case UART_6:

    	        Global_Uart_Config6 = Add_pstrConfigue; //buffer the Add_pstrConfigue
        		//Enable USART Module
        		//Bit 13 UE: USART Enable
        		UART6->USART_CR1 |= 1<<13;


        		//Enable USART Tx and Rx engines accordingto the UART_Mode Configuration item
        		// USART_CR1  bit3(TE): Transmitter enable     &    bit2(RE): Receiver enable
        		UART6->USART_CR1   |=  Add_pstrConfigue->UART_Mode;


        		//Data Length
        		UART6->USART_CR1   |=  Add_pstrConfigue->UART_WordLength;


        		//Configuration of Parity Control bit Fields
        		//USART_C1   bit10(PCE): Parity Control Enable    &    bit9(PS): Parity Selection
        		UART6->USART_CR1   |=  Add_pstrConfigue->UART_ParityBit;


        		//Configure the number of stop bits
        		//USART_C2   bits 13:12
        		UART6->USART_CR2   |=  Add_pstrConfigue->UART_PStopBits;


        		//Configuration of BRR(Baudrate Register)
        	    // APB2, PCLK2 --->  for USART1,6
        		// APB1, PCLK1 --->  for USART2
        		UART6->USART_BRR    =  UART_BRR_Register( PCLK2 , Add_pstrConfigue->UART_BaudRate );

        		 if(Add_pstrConfigue->UART_Interrupt_Enable != UART_INT_DISABLE)
        		 {
        			 UART6->USART_CR1 |= (Add_pstrConfigue->UART_Interrupt_Enable);
        			 MNVIC_vInterrupt_SetEnable(71);  //enable uart6 from nvic
        		 }
        		 break;
          default: break;

   }



}



void UART_vTransmite(u8 Copy_u8UartNumber, u16 Copy_u8Data, enum Polling_Mechanism PollingEN)
{
	switch( Copy_u8UartNumber)
	{
			case UART_1 :
				// wait until TXE flag is set in the Status Register (USART_SR)
				if(PollingEN == enable)
					while(! (UART1->USART_SR & (1<<7)) );

				//check the USART_WordLength item for 9-bit or 8-bit in a frame
				if(Global_Uart_Config1->UART_WordLength == UART_NINE_DATA_BITS)
				{
					 UART1->USART_DR = (Copy_u8Data & (u16)0x01ff);
				}
				else
				{
					 UART1->USART_DR = (Copy_u8Data & (u8)0xff);
				}
				break;

			case UART_2 :
						// wait until TXE flag is set in the Status Register (USART_SR)
						if(PollingEN == enable)
							while(! (UART2->USART_SR & (1<<7)) );

						//check the USART_WordLength item for 9-bit or 8-bit in a frame
						if(Global_Uart_Config2->UART_WordLength == UART_NINE_DATA_BITS)
						{
							UART2->USART_DR = (Copy_u8Data & (u16)0x01ff);
						}
						else
						{
							UART2->USART_DR = (Copy_u8Data & (u8)0xff);
						}
						break;
			case UART_6 :
						// wait until TXE flag is set in the Status Register (USART_SR)
						if(PollingEN == enable)
							while(! (UART6->USART_SR & (1<<7)) );

						//check the USART_WordLength item for 9-bit or 8-bit in a frame
						if(Global_Uart_Config6->UART_WordLength == UART_NINE_DATA_BITS)
						{
							UART6->USART_DR = (Copy_u8Data & (u16)0x01ff);
						}
						else
						{
							UART6->USART_DR = (Copy_u8Data & (u8)0xff);
						}
						break;
			default: break;
	}


}



u8 UART_u8Recive(u8 Copy_u8UartNumber, enum Polling_Mechanism PollingEN)
{

	switch(Copy_u8UartNumber)
	{
		case UART_1:
			   // wait until RXNE flag is set in the Status Register (USART_SR)
			    if(PollingEN == enable)
				    while(! (UART1->USART_SR & (1<<5)) );

				//check the USART_WordLength item for 9-bit or 8-bit in a frame
				if(Global_Uart_Config1->UART_WordLength == UART_NINE_DATA_BITS)
				{
					if(Global_Uart_Config1->UART_ParityBit == UART_NONE_PARITY)
					{
						 // no parity, so all 9-bits are considered data
						 return UART1->USART_DR;
					}
					else
					{
						// parity is used, so 8-bits will be of user data and the msb is parity
						 return (UART1->USART_DR & (u8)0xff);
					}
				}
				else
				{
					if(Global_Uart_Config1->UART_ParityBit == UART_NONE_PARITY)
					{
						 // no parity, so all 8-bits are considered data
						 return UART1->USART_DR;
					}
					else
					{
						// parity is used, so 7-bits will be of user data and the msb is parity
						 return (UART1->USART_DR & (u8)0x7f);
					}
				}
				break;
		case UART_2:
					   // wait until RXNE flag is set in the Status Register (USART_SR)
					    if(PollingEN == enable)
						    while(! (UART2->USART_SR & (1<<5)) );

						//check the USART_WordLength item for 9-bit or 8-bit in a frame
						if(Global_Uart_Config2->UART_WordLength == UART_NINE_DATA_BITS)
						{
							if(Global_Uart_Config2->UART_ParityBit == UART_NONE_PARITY)
							{
								 // no parity, so all 9-bits are considered data
								 return UART2->USART_DR;
							}
							else
							{
								// parity is used, so 8-bits will be of user data and the msb is parity
								 return (UART2->USART_DR & (u8)0xff);
							}
						}
						else
						{
							if(Global_Uart_Config2->UART_ParityBit == UART_NONE_PARITY)
							{
								 // no parity, so all 8-bits are considered data
								 return UART2->USART_DR;
							}
							else
							{
								// parity is used, so 7-bits will be of user data and the msb is parity
								 return (UART2->USART_DR & (u8)0x7f);
							}
						}
						break;
		case UART_6:
					   // wait until RXNE flag is set in the Status Register (USART_SR)
					    if(PollingEN == enable)
						    while(! (UART6->USART_SR & (1<<5)) );

						//check the USART_WordLength item for 9-bit or 8-bit in a frame
						if(Global_Uart_Config6->UART_WordLength == UART_NINE_DATA_BITS)
						{
							if(Global_Uart_Config6->UART_ParityBit == UART_NONE_PARITY)
							{
								 // no parity, so all 9-bits are considered data
								 return UART6->USART_DR;
							}
							else
							{
								// parity is used, so 8-bits will be of user data and the msb is parity
								 return (UART6->USART_DR & (u8)0xff);
							}
						}
						else
						{
							if(Global_Uart_Config6->UART_ParityBit == UART_NONE_PARITY)
							{
								 // no parity, so all 8-bits are considered data
								 return UART6->USART_DR;
							}
							else
							{
								// parity is used, so 7-bits will be of user data and the msb is parity
								 return (UART6->USART_DR & (u8)0x7f);
							}
						}
						break;
		  default: break;
	}

}


/**************** GPIO *****************/
// ??????????????????????????????

void USART1_IRQHandler(void)
{
	Global_Uart_Config1->p_IRQ_CallBack();
}


void USART2_IRQHandler(void)
{
	Global_Uart_Config2->p_IRQ_CallBack();
}


void USART6_IRQHandler(void)
{
	Global_Uart_Config6->p_IRQ_CallBack();
}
