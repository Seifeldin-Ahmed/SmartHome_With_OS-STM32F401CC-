/*******************************************************************************************************/
/* Author            : Ibrahim Refaey                                                                  */
/* Date              :                                                                                 */
/* File              : MRCC_prog.c                                                                     */
/* Description       : This file contains all registers ,structs and macros of RCC Driver              */
/* Version           : v 1.0                                                                           */
/* Module            : RCC Driver                                                                      */
/*******************************************************************************************************/

/*******************************************************************************************************/
/*                                      Standard Types LIB                                             */
/*******************************************************************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATHS.h"


/*******************************************************************************************************/
/*                                      MCAL Components                                                */
/*******************************************************************************************************/
#include "MRCC_interface.h"
#include "MRCC_private.h"
#include "MRCC_config.h"

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      Functions Implementations                                      */
/*******************************************************************************************************/

/*#####################################################################################################*/
/*#####################################################################################################*/

/*******************************************************************************************************/
/*                                      01- MRCC_voidEnableClock                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MRCC_voidEnablePeripheralClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	
	switch(BusName)
	{
		case AHB1_BUS:  SET_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  SET_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  SET_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  SET_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /*   ERROR   */          break ;
		
	}
}
/*******************************************************************************************************/
/*                                      02- MRCC_voidDisableClock                                       */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Disable Peripheral Clock                                                  */
/* 2- Function Input       -> Copy_uBusName ,   Copy_u8PerNum                                          */
/*   - BusName_t      : The Bus Of The Prepheral ( AHB1 , AHB2 , APB1 , APB2 ) Every One               */
/*                      Detect Which REG To Choice Pripheral From It                                   */ 
/*   - Copy_u8PerName :  The Order Of Prepheral On The Selected Reg                                    */                      
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MRCC_voidDisablePeripheralClock(BusName_t BusName , u8 Copy_u8PerNum )
{
	switch(BusName)
	{
		case AHB1_BUS:  CLEAR_BIT(RCC_AHB1ENR,Copy_u8PerNum );         break ;
		case AHB2_BUS:  CLEAR_BIT(RCC_AHB2ENR,Copy_u8PerNum );         break ;
		case APB1_BUS:  CLEAR_BIT(RCC_APB1ENR,Copy_u8PerNum );         break ;
		case APB2_BUS:  CLEAR_BIT(RCC_APB2ENR,Copy_u8PerNum );         break ;
		default :     /* ERROR */          break ;
		
	}
}

/*******************************************************************************************************/
/*                                      03- MRCC_voidEnableSecuritySystem                              */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Enable Security System                                                   */
/* 2- Function Input       -> No Thing                                                                 */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/

void MRCC_voidEnableSecuritySystem(void)
{
	SET_BIT( RCC_CR  , CSSON);
	
}
/*******************************************************************************************************/
/*                                      04- MRCC_voidDisableSecuritySystem                              */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> Disable Security System                                                   */
/* 2- Function Input       -> No Thing                                                                 */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/


void MRCC_voidDisableSecuritySystem(void)
{
	CLR_BIT( RCC_CR  , CSSON);
	
}
/*******************************************************************************************************/
/*                                      05- MRCC_voidInitSystemClk                                     */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> intialize system clock                                                   */
/*    - CLK		: HSE | HSI |PLL	                                                                   */
/*    - PLLSrc	:PLL_HSE | PLL_HSI                                                                     */
/*    - HSESrc  :HSE_Crystal ,HSE_RC                                                                   */
/* 2- Function Input       -> No Thing                                                                 */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MRCC_voidInitSystemClk(void)
{
	/********** HSI **********/
#if CLKSRC == HSI 
    MRCC->CR = 0;
	/* 1- EN HSI */
	SET_BIT(MRCC->CR , 0U);
	while(GET_BIT(MRCC->CR,1U)==0);
	/* 2- CLK SYS --> HSI */
	CLEAR_BIT(MRCC->CFGR, 0U);
	CLEAR_BIT(MRCC->CFGR, 1U);
	/********** HSE **********/
#elif CLKSRC == HSE
	
	#if HSE_SRC == CRYSTAL 
	/* 1- EN HSE */
		SET_BIT(MRCC->CR , 16U);
		/* 2- Disable BYP */
		CLEAR_BIT(MRCC->CR,18U);
		/* 3- CLK SYS --> HSE */
		SET_BIT(MRCC->CFGR, 0U);
		CLEAR_BIT(MRCC->CFGR, 1U);

	#elif HSE_SRC == RC 
		/* 1- EN HSE */
		SET_BIT(MRCC->CR , 16U);
		/* 2- Enable BYP */
		SET_BIT(MRCC->CR,18U);
		/* 3- CLK SYS --> HSE */
		SET_BIT(MRCC->CFGR, 0U);
		CLEAR_BIT(MRCC->CFGR, 1U);
	#else 
    /* Error*/
	#endif
	
	/********** PLL **********/
#elif CLKSRC == PLL	

    #if PLL_SRC == _HSE_PLL 
     /*1-Enable HSE */
			SET_BIT(MRCC->CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*2- EN PLL*/
			SET_BIT(MRCC->,24U);
			/* while ( GET_BIT(RCC_CR, 25)==0);*/
			/* 3- PLL From HSE */
			SET_BIT(MRCC->PLLCFGR, 22U);
			/* 4- System Clk  PLL */
			CLEAR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
 
    #elif PLL_SRC == _HSI_PLL  
            /*Enable HSI */
		     SET_BIT(MRCC->CR,0U);
			/*2- EN PLL*/
			SET_BIT(MRCC->CR,24U);
			/* 3- PLL From HSI */
			CLEAR_BIT(MRCC->PLLCFGR, 22U);
			/* 4- System Clk  PLL */
			CLEAR_BIT(MRCC->CFGR,0U);
			SET_BIT(MRCC->CFGR,1U);
    #else 
            /* Error*/
	#endif
/****************************************************/

#else 
/* Error*/
#endif // The End Of Big IF	
}

/*******************************************************************************************************/
/*                                      06- MRCC_voidInitClock                                         */
/*-----------------------------------------------------------------------------------------------------*/
/* 1- Function Description -> intialize system clock                                                   */
/*    - CLK		: HSE | HSI |PLL	                                                                   */
/*    - PLLSrc	:PLL_HSE | PLL_HSI                                                                     */
/*    - HSESrc  :HSE_Crystal ,HSE_RC                                                                   */
/* 2- Function Input       -> Copy_uClkSrc   , Copy_uHSESrc    ,Copy_uPLLSrc                           */
/* 3- Function Return      -> No Thing                                                                 */
/*******************************************************************************************************/
void MRCC_voidInitClock(CLKSrcName_t Copy_tClkSrc , HSESrc_t Copy_tHSESrc ,PLLSrc_t Copy_tPLLSrc )
{
	switch(Copy_tClkSrc)
	{
		case HSE :
		switch(Copy_tHSESrc)
		{
		  case _HSE_CRYSTAL : 
			/*1-Enable HSE */
			SET_BIT(RCC_CR,16U);
			/* while ( GET_BIT(RCC_CR, 17)==0);*/
			/*Disable BYP*/
			CLEAR_BIT(RCC_CR,18U);
			/* Input system Clk*/
			SET_BIT(RCC_CFGR,0U);
			CLEAR_BIT(RCC_CFGR,1U);
		  break ;
		  /************************************************/
          case _HSE_RC :   
			/*Enable HSE */
			SET_BIT(RCC_CR,16U);
            /*2-enable BYP*/
			SET_BIT(RCC_CR,18U);
				/* Input system Clk*/
			SET_BIT(RCC_CFGR,0U);
			CLEAR_BIT(RCC_CFGR,1U);

		  break ;

		  /*********************************************/
		  default :  break ;
		}
	    break ;
		/*******************/
		case HSI :
		/*Enable HSI */
			MRCC->CR = 0;
		SET_BIT(RCC_CR,0U);
		while(GET_BIT(MRCC->CR,1U)==0);
		/* Input system Clk*/
		CLEAR_BIT(RCC_CFGR,0U);
		CLEAR_BIT(RCC_CFGR,1U);
	    break ;
		/********************/
		case PLL :
			RCC_CR = 0;
			RCC_PLLCFGR =0;
		switch(Copy_tPLLSrc)
		{
		case _HSE_PLL:

/**************************************************************** RCC PLL configuration register (RCC_PLLCFGR *******************************************************************/
		 /* Bits 17:16 PLLP: Main PLL (PLL) division factor for main system clock,                       PLL output clock frequency = VCO frequency / PLLP with PLLP = 2, 4, 6, or 8*/
		 /*PLLP= 4*/
		 SET_BIT(RCC_PLLCFGR, 16U);
		 CLEAR_BIT(RCC_PLLCFGR, 17U);

		 /* Bits 14:6 PLLN: Main PLL (PLL) multiplication factor for VCO,                                VCO output frequency = VCO input frequency × PLLN with 192 ≤ PLLN ≤ 432*/
		 /*PLLN = 192*/
		 RCC_PLLCFGR |= (192<<6);

		 /* Bits 5:0 PLLM: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock     VCO input frequency = PLL input clock frequency / PLLM with 2 ≤ PLLM ≤ 63 */
		 /*PLLN = 16*/
		 RCC_PLLCFGR |= (16<<0);
/************************************************************************************************************************************************************************************/

/***************************************************************************** AHP , ABP1 , APB2 Prescalers *************************************************************************/
		 /*Bits 15:13 PPRE2: APB high-speed prescaler (APB2) */
		 /*APB2 Prescaler = 1*/
		 RCC_CFGR |= (0<<13);

		 /*Bits 12:10 PPRE1: APB Low speed prescaler (APB1)*/
		 /*APB1 Prescaler = 2*/
		 RCC_CFGR |= (4<<10);

		 /*Bits 7:4 HPRE: AHB prescaler*/
		 /*AHP Prescaler = 1*/
		 RCC_CFGR |= (0<<4);
/************************************************************************************************************************************************************************************/

		 /*1-Enable HSE */
		 SET_BIT(RCC_CR,16U);
		 while ( GET_BIT(RCC_CR, 17)==0); /* wait for hse rdy*/

		 /*2- EN PLL*/
		 SET_BIT(RCC_CR,24U);
		 while ( GET_BIT(RCC_CR, 25)==0); /*wait for pll rdy*/

		 SET_BIT(RCC_PLLCFGR, 22U);/*pllsrc ----> 1- select hse , 0- select hsi*/

		 CLEAR_BIT(RCC_CFGR,0U); /*select sw0,sw1 for pll*/
		 SET_BIT(RCC_CFGR,1U);

/*********************************************************************************************************************/
		 RCC_CFGR |= (0<<30);
/*********************************************************************************************************************/

			break ;
			
			/**************************/
			
			case _HSI_PLL : 
			/*Enable HSI */
		     SET_BIT(RCC_CR,0U);
			/*2- EN PLL*/
			SET_BIT(RCC_CR,24U);
			
			CLEAR_BIT(RCC_PLLCFGR, 22U);
			
			CLEAR_BIT(RCC_CFGR,0U);
			SET_BIT(RCC_CFGR,1U);
			
			break ;
		}

	    break ;
		
	}
	
}


/*******************************************************************************************************/
/*                                      End of file : MRCC_prog.c                                      */
/*-----------------------------------------------------------------------------------------------------*/
