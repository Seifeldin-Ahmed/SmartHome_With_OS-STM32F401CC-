/*
 * SysTick_config.h
 *
 *  Created on: Aug 20, 2023
 *      Author: Dell
 */

#ifndef MCAL_SYSTICK_SYSTICK_CONFIG_H_
#define MCAL_SYSTICK_SYSTICK_CONFIG_H_



#define Freq_cpu          16000000UL

/*****************************************************************************************************************************************************************************************/

/*
 *  OPTIONS: 1- SYSTICK_INTURRPT_DISABLE
 *			 2-	SYSTICK_INTURRPT_ENABLE
 */
#define SYSTIC_INTURRPT_OPTION           SYSTICK_INTURRPT_ENABLE


/*
 *  OPTIONS: 1- SYSTICK_CLKSOURCE_AHB_DIV_8
 *			 2-	SYSTICK_CLKSOURCE_PROCESSOR_CLK_AHB
 */
#define SYSTIC_CLKSOURCE_OPTION               SYSTICK_CLKSOURCE_PROCESSOR_CLK_AHB

/*****************************************************************************************************************************************************************************************/




#endif /* MCAL_SYSTICK_SYSTICK_CONFIG_H_ */
