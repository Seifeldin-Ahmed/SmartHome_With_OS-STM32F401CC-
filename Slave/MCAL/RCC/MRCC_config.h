/*******************************************************************************************************/
/* Author            : Ibrahim Refaey                                                                  */
/* Date              :                                                                                 */
/* File              : MRCC_Config.h                                                                   */
/* Description       : This file contains all configuration parameters of RCC driver                   */
/* Version           : v 1.0                                                                           */
/* Module            : RCC Driver                                                                      */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                               File Gaurd                           		                           */       
/*******************************************************************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H


/*
	- CLKSRC option :
			         1) HSI
			         2) HSE
			         3) PLL
*/
       #define CLKSRC  HSI
/*
   - HSE option :
                 1)_HSE_CRYSTAL
                 2)_HSE_RC
*/

       #define HSE_SRC  _HSE_CRYSTAL
/*
   - PLL option :
	            1) _HSE_PLL
                2) _HSI_PLL
 */
      #define PLL_SRC   _HSI_PLL

#endif // RCC_CONFIG_H
