/*
 * ==================================================================================================================================
 *                                                         Include Section
 * ===================================================================================================================================
 */

#include "../LIB/BIT_MATHS.h"
#include "../LIB/STD_TYPES.h"
#include "../MCAL/RCC/MRCC_Interface.h"
#include "../MCAL/GPIO/MGPIO_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/UART/UART_interface.h"
#include "../HAL/LM35/LM35_interface.h"
#include "../HAL/LDR/LDR_interface.h"
#include "../RTOS/RTOS_interface.h"
#include "../HAL/Motors/DCMOTOR_inth.h"
#include "../HAL/BUZZER/BUZZER_interface.h"
#include "../HAL/HEATER/HEATER_interface.h"
#include "../MCAL/SysTick/SysTick_interface.h"
#include "../HAL/SEV_SEG/SevSegment_int.h"
/*
 * ==================================================================================================================================
 *                                                         Macros
 * ===================================================================================================================================
 */

// for rooms
#define ROOM1     		'1'
#define ROOM2     		'2'
#define KITCHEN     	'3'
#define GARAGE   		'4'

//for components
#define FAN      	 	'F'
#define DOOR        	'D'
#define LAMP     	 	'L'
#define TEMP     		'T'
#define HEATER    		'H'

// for Moods
#define ON      		'O'
#define OFF      		'F'

#define MANUAL     		 1
#define AUTOMATIC  		 2

/*
 * ==================================================================================================================================
 *                                                         Global Vairables
 * ===================================================================================================================================
 */

u8 Global_u8Temp_value;
u8 Global_u8LDR_value;
u8 Global_u8UartCounter;

u8 Global_u8Control; //Manuall or automatic
u8 Global_u8Room;
u8 Global_u8component;
u8 Global_u8mode;

//for flags
u8 Global_Fan_Flag1;   // for room1
u8 Global_Fan_Flag2;   // for room1

u8 Global_Heater_Flag1;// for room1
u8 Global_Heater_Flag2;// for room1

u8 Global_Room2_Door_Flag1;  // for room2
u8 Global_Room2_Door_Flag2;  // for room2

u8 Global_Lamp_Flag1;  // for room2
u8 Global_Lamp_Flag2;  // for room2


u8 Global_garage_Door_Flag1;  // for garage
u8 Global_garage_Door_Flag2;  // for garage


u8 counter;
u8 Global_u8Counter_Seconds=0;
u8 Global_u8Counter_Minutes=0;
u8 Global_u8Counter_Hours=0;

/*
 * ==================================================================================================================================
 *                                                         OS Tasks
 * ===================================================================================================================================
 */

void Task_Room1()
{
	Global_u8Temp_value = LM35_u16_Get_Temp(ADC_CHANNEL_4);
	if(Global_u8Temp_value > 25 ) // turn on fan
	{
		/* test case senario:
		 * // now : temp> 25 so  auto: on.
		 *  user : off .
		 *  then user : on.
		 *  then temp <20
		 *  Note: fan still on  (it should be off), (that is the importantance of automatic and manuall control options )
		 * */
		   if(Global_Fan_Flag1 == 0)
			{
			  MGPIO_voidWriteData(_GPIOA_PORT,_PIN_2,HIGH); // Turn Fan on            // off=1 , on=0
			}
            if(Global_Heater_Flag1 == 0)
			{
            	HEATER_vTurnOFF(_GPIOA_PORT,_PIN_6); // Turn Heater off        //on = 1 , off =0
			}
		    if(Global_u8Temp_value > 30) // turn buzzer on & red led;
			{
			  BUZZER_vTurnOn(_GPIOA_PORT,_PIN_7);
			}
		    else // turn buuzer off & red led
			{
			   BUZZER_vTurnOFF(_GPIOA_PORT,_PIN_7);
			}
	}
	else if(Global_u8Temp_value < 20)
	{
		if(Global_Fan_Flag2==0)
  	    {
			MGPIO_voidWriteData(_GPIOA_PORT,_PIN_2,LOW); // Turn Fan off           // on =1 , off = 0
 	    }
		if(Global_Heater_Flag2 == 0)
		{
			HEATER_vTurnOn(_GPIOA_PORT,_PIN_6); // Turn Heater on     // off=1 , on=0
		}

		if(Global_u8Temp_value < 10) // turn buzzer on  & red led
		{
				BUZZER_vTurnOn(_GPIOA_PORT,_PIN_7);
		}
		else // turn buuzer off & red led
		{
			     BUZZER_vTurnOFF(_GPIOA_PORT,_PIN_7);
		}

	}
	else
	{
		MGPIO_voidWriteData(_GPIOA_PORT,_PIN_2,LOW); // Turn Fan off
		HEATER_vTurnOFF(_GPIOA_PORT,_PIN_6); // Turn Heater off
	}
}
void Task_Room1_Control()
{
	if (Global_u8Room == ROOM1 )
	 {
		switch(Global_u8component)
		{
			case FAN :
				 if(Global_u8Control == MANUAL)
				  {
					 if(Global_u8mode == ON)
                       {
             			 MGPIO_voidWriteData(_GPIOA_PORT,_PIN_2,HIGH); // Turn Fan on
             			 Global_Fan_Flag1 = 0 ; // for case 1 temp > 25 , auto : on , and user want it on
             			 Global_Fan_Flag2 = 1; //  for case 2 temp <20  , auto : off , and user wait it on
                       }
                      else if(Global_u8mode == OFF)
                      {
              			 MGPIO_voidWriteData(_GPIOA_PORT,_PIN_2,LOW); // Turn Fan off
              			 Global_Fan_Flag1 = 1; // for case 3 temp > 25 , auto : on , and user want it off
              			 Global_Fan_Flag2 =0; //  for case 4 temp <20  , auto : off , and user wait it off
                      }
				  }
				 else
				 {
					 Global_Fan_Flag1 = 0; //back to normal
					 Global_Fan_Flag2 = 0;
				 }
             	 Global_u8Room = 0;
             	 Global_u8component = 0;
             	 Global_u8mode = 0;
                      break;
			case DOOR :
				       if(Global_u8mode == ON)
				        {
				        	 MGPIO_voidWriteData(_GPIOA_PORT,_PIN_0,HIGH); // Open Door
				        	 MGPIO_voidWriteData(_GPIOA_PORT,_PIN_1,LOW);
				         }
				         else if(Global_u8mode == OFF)
				         {
				        	 MGPIO_voidWriteData(_GPIOA_PORT,_PIN_0,LOW); //  Close Door
				        	 MGPIO_voidWriteData(_GPIOA_PORT,_PIN_1,HIGH);
				         }
			        	 Global_u8Room = 0;
			        	 Global_u8component = 0;
			        	 Global_u8mode = 0;
				         break;
			case TEMP :
				        	 // send temp;
					     Global_u8Temp_value = LM35_u16_Get_Temp(ADC_CHANNEL_4);
					     UART_vTransmite(UART_6,Global_u8Temp_value,enable);
				         Global_u8Room = 0;
				         Global_u8component = 0;
				         Global_u8mode = 0;
				         break;
			case HEATER:
				 	 	 if(Global_u8Control == MANUAL)
						  {
				 	 		 if(Global_u8mode == ON)
				 	 		 {
				 	 			 HEATER_vTurnOn(_GPIOA_PORT,_PIN_6);
				 	 			 Global_Heater_Flag1 = 1;   // for case 1 temp > 25 , auto : off , and user want it on
				 	 			 Global_Heater_Flag2 = 0;   // for case 2 temp <20  , auto : on , and user wait it on
				 	 		 }
				 	 		 else if(Global_u8mode == OFF)
				 	 		 {
				 	 			 HEATER_vTurnOFF(_GPIOA_PORT,_PIN_6);
				 	 			 Global_Heater_Flag1 = 0; // for case 3 temp > 25 , auto : off , and user want it off
				 	 			 Global_Heater_Flag2 = 1;  // for case 2 temp <20  , auto : on , and user wait it off
				 	 		 }
						  }
				 	 	 else
				 	 	 {
				 	 		Global_Heater_Flag1 = 0; //back to normal
				 	 		Global_Heater_Flag2 = 0;
				 	 	 }
		 	 			 Global_u8Room = 0;
		 	 			 Global_u8component = 0;
		 	 			 Global_u8mode = 0;
					     break;
			default: break;
		}
	}
}

void Task_Room2()
{
	Global_u8LDR_value = (u8)LDR_u32_Get_value(ADC_CHANNEL_8);
	if(Global_u8LDR_value > 50) // turn on Lamp
	{
		if(Global_Lamp_Flag1==0)
		{
		  MGPIO_voidWriteData(_GPIOA_PORT,_PIN_15,HIGH); // Turn Lamp on
		}
		if(Global_Room2_Door_Flag1 == 0)
		{ // open door
		  MGPIO_voidWriteData(_GPIOA_PORT,_PIN_9,HIGH); // IN1 on
		  MGPIO_voidWriteData(_GPIOA_PORT,_PIN_10,LOW); // IN2 off
		}
	}
	else
	{
	    if(Global_Lamp_Flag2 ==0)
		{
	    	MGPIO_voidWriteData(_GPIOA_PORT,_PIN_15,LOW); // Turn Lamp Off
		}
		//close door
		if(Global_Room2_Door_Flag2 == 0)
		{
			MGPIO_voidWriteData(_GPIOA_PORT,_PIN_9,LOW);   // IN1 off
			MGPIO_voidWriteData(_GPIOA_PORT,_PIN_10,LOW); // IN2 on
		}
	}
}
void Task_Room2_Control()
{
	if( Global_u8Room == ROOM2)
		{
			switch(Global_u8component)
			{
			  case FAN:
			           if(Global_u8mode == ON)
			           {
			        	  MGPIO_voidWriteData(_GPIOA_PORT,_PIN_14,HIGH); //  turn fan on
			           }
			           else if(Global_u8mode == OFF)
			           {
			        	  MGPIO_voidWriteData(_GPIOA_PORT,_PIN_14,LOW); //  turn fan off
			           }
		        	   Global_u8Room = 0;
		        	   Global_u8component = 0;
		        	   Global_u8mode = 0;
				       break;
			  case DOOR:
					 if(Global_u8Control == MANUAL)
					  {
						   if(Global_u8mode == ON)
						   {
								MGPIO_voidWriteData(_GPIOA_PORT,_PIN_9,HIGH); // IN1 on
								MGPIO_voidWriteData(_GPIOA_PORT,_PIN_10,LOW); // IN2 off

								Global_Room2_Door_Flag1 = 0 ;
								Global_Room2_Door_Flag2 = 1;
	                       }
						   else if(Global_u8mode == OFF)
	                   	   {
								MGPIO_voidWriteData(_GPIOA_PORT,_PIN_9,LOW); // IN1 off
								MGPIO_voidWriteData(_GPIOA_PORT,_PIN_10,HIGH); // IN2 on
								Global_Room2_Door_Flag1 = 1;
								Global_Room2_Door_Flag2 = 0;
	                   	   }
					   }
					   else
					   {
						   Global_Room2_Door_Flag1 = 0;
						   Global_Room2_Door_Flag2 = 0;
					   }
					   Global_u8Room = 0;
					   Global_u8component = 0;
					   Global_u8mode = 0;
	                   break;
			  case LAMP:
					 if(Global_u8Control == MANUAL)
					  {
						   if(Global_u8mode == ON)
						   {
								MGPIO_voidWriteData(_GPIOA_PORT,_PIN_15,HIGH); // Turn Lamp on
								Global_Lamp_Flag1 = 0 ;
								Global_Lamp_Flag2 = 1;
	                       }
						   else if(Global_u8mode == OFF)
	                	   {
								MGPIO_voidWriteData(_GPIOA_PORT,_PIN_15,LOW); // Turn Lamp Off
								Global_Lamp_Flag1 = 1;
								Global_Lamp_Flag2 = 0;
	                	   }
					   }
					   else
					   {
						   Global_Lamp_Flag1 = 0;
						   Global_Lamp_Flag2 = 0;
					   }
					   Global_u8Room = 0;
					   Global_u8component = 0;
					   Global_u8mode = 0;
	                   break;
			  default:
				       break;
			}
		}
}

void Task_Kitchen_Control()
{
    if(Global_u8Room == KITCHEN)
	{
		switch(Global_u8component)
		 {
			 case DOOR:
			       if(Global_u8mode == ON)
			        {
			        	 MGPIO_voidWriteData(_GPIOB_PORT,_PIN_9,HIGH); // Open Door
			        	 MGPIO_voidWriteData(_GPIOB_PORT,_PIN_10,LOW);

			         }
			         else if(Global_u8mode == OFF)
			         {
			        	 MGPIO_voidWriteData(_GPIOB_PORT,_PIN_9,LOW); //  Close Door
			        	 MGPIO_voidWriteData(_GPIOB_PORT,_PIN_10,HIGH);

			         }
		        	 Global_u8Room = 0;
		        	 Global_u8component = 0;
		        	 Global_u8mode = 0;
			         break;
		}
    }
}

void Task_Garage()
{
	Global_u8LDR_value = (u8)LDR_u32_Get_value(ADC_CHANNEL_5);
	if(Global_u8LDR_value > 50) // open door
		{
			if(Global_garage_Door_Flag1 == 0)
			{ // open door
			  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_5,HIGH); // IN1 on
			  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_6,LOW); // IN2 off
			}
		}
		else
		{
			//close door
			if(Global_garage_Door_Flag2 == 0)
			{
				MGPIO_voidWriteData(_GPIOB_PORT,_PIN_5,LOW);   // IN1 off
				MGPIO_voidWriteData(_GPIOB_PORT,_PIN_6,HIGH); // IN2 on
			}
		}
}
void Task_Garage_Control()
{
	if( Global_u8Room == GARAGE)
			{
				switch(Global_u8component)
				{
				  case DOOR:
						 if(Global_u8Control == MANUAL)
						  {
							   if(Global_u8mode == ON)
							   {
									MGPIO_voidWriteData(_GPIOB_PORT,_PIN_5,HIGH); // IN1 on
									MGPIO_voidWriteData(_GPIOB_PORT,_PIN_6,LOW); // IN2 off
									Global_garage_Door_Flag1 = 0 ;
									Global_garage_Door_Flag2 = 1;
		                       }
							   else if(Global_u8mode == OFF)
		                   	   {
									MGPIO_voidWriteData(_GPIOB_PORT,_PIN_5,LOW); // IN1 off
									MGPIO_voidWriteData(_GPIOB_PORT,_PIN_6,HIGH); // IN2 on
									Global_garage_Door_Flag1 = 1;
									Global_garage_Door_Flag2 = 0;
		                   	   }
						   }
						   else
						   {
							   Global_garage_Door_Flag1 = 0;
							   Global_garage_Door_Flag2 = 0;
						   }
						   Global_u8Room = 0;
						   Global_u8component = 0;
						   Global_u8mode = 0;
		                   break;
				  default:
					       break;
				}
			}
}

void Task_Timer()
{
	Global_u8Counter_Seconds++;
	 		  if(Global_u8Counter_Seconds >= 60)
	 		  {
		 		  Global_u8Counter_Seconds=0;
		 		  Global_u8Counter_Minutes ++;
	 		  }
	 		  if(Global_u8Counter_Minutes >= 60)
	 		  {
		 		  Global_u8Counter_Minutes=0;
		 		  Global_u8Counter_Hours ++;
	 		  }
	 		  if(Global_u8Counter_Hours >= 24)
	 		  {
		 		  Global_u8Counter_Hours=0;
	 		  }
}
void Task_Real_Time_clock()
{
  if(counter == 0)
  {
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_13,HIGH);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_15,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_15,LOW);
	  SevSegment_enuDisplayNumber(_PIN_3,_PIN_8, _PIN_1, _PIN_2 , _PIN_7,_PIN_8, _PIN_12, Global_u8Counter_Seconds % 10);
	  counter ++;
  }
  else if (counter == 1)
  {
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_14,HIGH);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_15,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_15,LOW);
	  SevSegment_enuDisplayNumber(_PIN_3,_PIN_8, _PIN_1, _PIN_2 , _PIN_7,_PIN_8, _PIN_12, Global_u8Counter_Seconds / 10);
	  counter ++;
  }

  else if (counter == 2)
  {
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_15,HIGH);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_15,LOW);
	  SevSegment_enuDisplayNumber(_PIN_3,_PIN_8, _PIN_1, _PIN_2 , _PIN_7,_PIN_8, _PIN_12, Global_u8Counter_Minutes % 10);
	  counter ++;
  }

  else if (counter == 3)
  {
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_15,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_13,HIGH);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_15,LOW);
	  SevSegment_enuDisplayNumber(_PIN_3,_PIN_8, _PIN_1, _PIN_2 , _PIN_7,_PIN_8, _PIN_12, Global_u8Counter_Minutes / 10);
	  counter ++;
  }
  else if (counter == 4)
  {
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_15,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_14,HIGH);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_15,LOW);
	  SevSegment_enuDisplayNumber(_PIN_3,_PIN_8, _PIN_1, _PIN_2 , _PIN_7,_PIN_8, _PIN_12, Global_u8Counter_Hours % 10);
	  counter ++;
  }
  else if (counter == 5)
  {
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOB_PORT,_PIN_15,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_13,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_14,LOW);
	  MGPIO_voidWriteData(_GPIOC_PORT,_PIN_15,HIGH);
	  SevSegment_enuDisplayNumber(_PIN_3,_PIN_8, _PIN_1, _PIN_2 , _PIN_7,_PIN_8, _PIN_12, Global_u8Counter_Hours / 10);
	  counter =0;
  }
}




/*
 * ==================================================================================================================================
 *                                                         Main Function
 * ===================================================================================================================================
 */

void UART_Call_back()
{
	u8 value;
	value = UART_u8Recive(UART_6,disable);
	if(Global_u8UartCounter == 0)
	  {
		Global_u8Control = value;
		Global_u8UartCounter++;
	  }
	else if(Global_u8UartCounter == 1)
	  {
		Global_u8Room = value;
		Global_u8UartCounter++;
	  }
	else if(Global_u8UartCounter==2)
	  {
		Global_u8component = value;
		Global_u8UartCounter++;
	  }
	else if(Global_u8UartCounter==3)
	  {
		  Global_u8mode = value;
		  Global_u8UartCounter = 0;
	  }

}

int main()
{

/************************************** RCC *************************************/
	MRCC_voidInitClock(HSI,_HSE_CRYSTAL,_HSE_PLL);
	MRCC_voidEnablePeripheralClock(AHB1_BUS,_PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(AHB1_BUS,_PERIPHERAL_EN_GPIOB);
	MRCC_voidEnablePeripheralClock(AHB1_BUS,_PERIPHERAL_EN_GPIOC);

	MRCC_voidEnablePeripheralClock(APB2_BUS,PERIPHERAL_EN_ADC1);
	MRCC_voidEnablePeripheralClock(APB2_BUS,PERIPHERAL_EN_USART6);

/****************************************** GPIO PINS **************************/
    //For Room1
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_0,_MODE_OUTPUT);
    MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_1,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_2,_MODE_OUTPUT);
	HEATER_vInit(_GPIOA_PORT,_PIN_6);
	BUZZER_vInit(_GPIOA_PORT,_PIN_7);

	//For Room2
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_9,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_10,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_14,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_15,_MODE_OUTPUT);

	//For Kitchen
	MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_9,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_10,_MODE_OUTPUT);

	//For Garage
	MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_5,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_6,_MODE_OUTPUT);

	// ADC Pins
    MGPIO_voidSetPinMode(_GPIOA_PORT , _PIN_4 , _MODE_ANALOG );
    MGPIO_voidSetPinMode(_GPIOB_PORT , _PIN_0 , _MODE_ANALOG );
    MGPIO_voidSetPinMode(_GPIOA_PORT , _PIN_5 , _MODE_ANALOG );

    //Uart Pins
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_11,_MODE_ALTF);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_12,_MODE_ALTF);
    MGPIO_voidSetPinAltFn(_GPIOA_PORT , _PIN_11, _ALTFN_8 );
    MGPIO_voidSetPinAltFn(_GPIOA_PORT , _PIN_12, _ALTFN_8 );

    //7-seg
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_13,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_14,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_15,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOC_PORT,_PIN_13,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOC_PORT,_PIN_14,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOC_PORT,_PIN_15,_MODE_OUTPUT);

	  MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_3,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_8,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_1,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_2,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_7,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_8,_MODE_OUTPUT);
	  MGPIO_voidSetPinMode(_GPIOB_PORT,_PIN_12,_MODE_OUTPUT);

/********************************* Initilizations *******************************/
	SysTick_vInit();
	LM35_vidInit();


	UART_tstrConfiguration object;
	object.UART_BaudRate = UART_BAUDRATE_115200;
	object.UART_Interrupt_Enable = UART_INT_ENABLE_RXNEIE;
	object.p_IRQ_CallBack = UART_Call_back;
	object.UART_ParityBit = UART_NONE_PARITY;
	object.UART_PStopBits =  UART_ONE_STOP_BIT;
	object.UART_WordLength =UART_EIGHT_DATA_BITS;
	object.UART_Mode = UART_FULL_DUPLEX;
    UART_vInit(UART_6, &object);


/*********************************** Create Tasks **********************************/
    /*
     *              Periodicity
     *
     *  T1- Task_Real_Time_clock:       5ms  = 1   tick
     *  T2- Task_Room1:        	        10ms = 2   tick
     *  T3- Task_Room2:        	        15ms = 3   tick
     *  T4- Task_Garage                 20ms = 4   tick
     *  T5- Task_Room1_Control          25ms = 5   tick
     *  T6- Task_Room2_Control          30ms = 6   tick
     *  T7- Task_Kitchen_Control        35ms = 7   tick
     *  T8- Task_Garage_Control         40ms = 8   tick
     *  T9- Task_Timer                1000ms = 200 tick
     *  Tick time = 5ms
     * */

	//Handler,       Periodicity , Priority , FirstDelay

    RTOS_u8CreateTask(Task_Real_Time_clock	, 1   , 0 , 0);
    RTOS_u8CreateTask(Task_Room1  		    , 2   , 1 , 0);
    RTOS_u8CreateTask(Task_Room2  		    , 3   , 2 , 0);
    RTOS_u8CreateTask(Task_Garage           , 4   , 3 , 0);
    RTOS_u8CreateTask(Task_Room1_Control    , 5   , 4 , 0);
    RTOS_u8CreateTask(Task_Room2_Control    , 6   , 5 , 0);
    RTOS_u8CreateTask(Task_Kitchen_Control  , 7   , 6 , 0);
    RTOS_u8CreateTask(Task_Garage_Control   , 8   , 7 , 0);
    RTOS_u8CreateTask(Task_Timer            , 200 , 8 , 200);




    RTOS_vStart_OS();

 while (1)
 {

  }
return 0;
}

