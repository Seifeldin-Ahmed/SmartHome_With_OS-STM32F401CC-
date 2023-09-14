/*
 * UART_private.h
 *
 *  Created on: Aug 24, 2023
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_PRIVATE_H_
#define MCAL_UART_UART_PRIVATE_H_




#define UART1_BASE_ADDRESS		 0x40011000
#define UART2_BASE_ADDRESS		 0x40004400
#define UART6_BASE_ADDRESS		 0x40011400



typedef struct{
	volatile u32 USART_SR   ;
	volatile u32 USART_DR   ;
	volatile u32 USART_BRR  ;
	volatile u32 USART_CR1  ;
	volatile u32 USART_CR2  ;
	volatile u32 USART_CR3  ;
	volatile u32 USART_GTPR ;
}MUART_T ;

#define UART1      		((volatile MUART_T*)UART1_BASE_ADDRESS)
#define UART2           ((volatile MUART_T*)UART2_BASE_ADDRESS)
#define UART6           ((volatile MUART_T*)UART6_BASE_ADDRESS)



#endif /* MCAL_UART_UART_PRIVATE_H_ */
