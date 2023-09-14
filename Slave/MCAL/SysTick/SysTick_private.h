
/****************************************************
 *********************************************************************************************************
AUTHOR  : Seifeldin Ahmed
MICRO   : STM32F401CCU6
LAYER   : MCAL
DRIVER  : SysTick_Driver
File    : private File
Version :1.0
********************************************************************************************************
*********************************************************þ
*/


#ifndef MCAL_SysTick_SysTick_PRIVATE_H_
#define MCAL_SysTick_SysTick_PRIVATE_H_




typedef struct {

	u32 STK_CTRL  ;  //control
	u32 STK_LOAD  ;  //load
	u32 STK_VAL   ;  //value
	u32 STK_CALIB ;  //calibration

}MSYSTICK_T;


#define SYSTICK_BASE_ADDRESS	     0xE000E010
#define SYSTIC		( (volatile MSYSTICK_T *) SYSTICK_BASE_ADDRESS)


//************************************************************************** for Bits Definitions ****************************************************************************************

#define SYSTICK_EN_BIT	    	       0  /* Counter enable*/
#define SYSTICK_INTURRPT_BIT	  	   1  /*SysTick exception request enable*/
#define SYSTICK_CLKSOURCE_BIT          2

//****************************************************************************** Options For the Previous 2 bits *************************************************************************
#define SYSTICK_INTURRPT_DISABLE  	    		   0
#define SYSTICK_INTURRPT_ENABLE 	    		   1

#define SYSTICK_CLKSOURCE_AHB/8	  				   0
#define	SYSTICK_CLKSOURCE_PROCESSOR_CLK_AHB		   1

#endif
