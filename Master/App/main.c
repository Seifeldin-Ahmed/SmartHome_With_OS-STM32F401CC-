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
#include "../MCAL/SysTick/SysTick_interface.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KEYPAD/KEYPAD_int.h"
#include "../MCAL/UART/UART_interface.h"


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
#define FAN      		'F'
#define DOOR      		'D'
#define LAMP      		'L'
#define TEMP      		'T'
#define HEATER    		'H'


// for Moods
#define ON        		'O'
#define OFF       		'F'

#define MANUAL     		 1
#define AUTOMATIC  		 2

// for Password
#define first_digit     '1'
#define second_digit    '2'
#define third_digit     '3'
#define fourth_digit    '4'


/*
 * ==================================================================================================================================
 *                                                         Main Function
 * ===================================================================================================================================
 */

int main()
{
    u8 password[4],i,value,flag=0,Local_u8Temp;
/************************************** RCC *************************************/
	MRCC_voidInitClock(HSI,_HSE_CRYSTAL,_HSE_PLL);
	MRCC_voidEnablePeripheralClock(AHB1_BUS,_PERIPHERAL_EN_GPIOA);
	MRCC_voidEnablePeripheralClock(AHB1_BUS,_PERIPHERAL_EN_GPIOB);
	MRCC_voidEnablePeripheralClock(APB2_BUS,PERIPHERAL_EN_USART6);

/****************************************** GPIO PINS **************************/
	// LCD Pins
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_0,_MODE_OUTPUT);
    MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_1,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_2,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_3,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_4,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_5,_MODE_OUTPUT);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_6,_MODE_OUTPUT);

    //Uart Pins
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_11,_MODE_ALTF);
	MGPIO_voidSetPinMode(_GPIOA_PORT,_PIN_12,_MODE_ALTF);
    MGPIO_voidSetPinAltFn(_GPIOA_PORT , _PIN_11, _ALTFN_8 );
    MGPIO_voidSetPinAltFn(_GPIOA_PORT , _PIN_12, _ALTFN_8 );

    //Leds
    LED_vLedInit(_GPIOB_PORT,_PIN_0); //red led
    LED_vLedInit(_GPIOB_PORT,_PIN_1); //red green

/********************************* Initilizations *******************************/
	SysTick_vInit();
 	LCD_VidInit();
 	KEYPAD_vidInit();

	UART_tstrConfiguration object;
	object.UART_BaudRate = UART_BAUDRATE_115200;
	object.UART_Interrupt_Enable = UART_INT_DISABLE;
	object.p_IRQ_CallBack = NULL;
	object.UART_ParityBit = UART_NONE_PARITY;
	object.UART_PStopBits =  UART_ONE_STOP_BIT;
	object.UART_WordLength =UART_EIGHT_DATA_BITS;
	object.UART_Mode = UART_FULL_DUPLEX;
    UART_vInit(UART_6, &object);


/*********************************************************************************/
 while(flag==0)
 {
       LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
	   LCD_enuSendString("Enter Password: ");
	   LCD_enuGoTo(1,0);
	   for(i=0 ; i<4; i++)
	   {
		   do{
			   KEYPAD_enuGetPressedKey(&password[i]) ;
	       }while(password[i] == KEYPAD_u8_NOTPRESSED);
		   LCD_enuSendCharacter('*');
		   Systic_vDelay_ms(250);
	   }
	   if(password[0]==first_digit && password[1]==second_digit && password[2]==third_digit && password[3]==fourth_digit) //CORRECT
	   {   	LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
  	   		LCD_enuSendString("Password correct");
  	   		LED_vLedTurnOn(_GPIOB_PORT,_PIN_1);
  	   		Systic_vDelay_ms(500);
		    flag=1;
  	   		LED_vLedTurnOFF(_GPIOB_PORT,_PIN_1);
	   }
       else
	   {
		    LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY); //WRONG
		    LCD_enuSendString("Wrong Password");
  	   		LED_vLedTurnOn(_GPIOB_PORT,_PIN_0);
  	   		Systic_vDelay_ms(500);
  	   		LED_vLedTurnOFF(_GPIOB_PORT,_PIN_0);
	   }
 }
 while (1)
 {
	     	LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
	     	LCD_enuSendString("1-ROOM1");
			LCD_enuGoTo(1,0);
	     	LCD_enuSendString("2-ROOM2");
			LCD_enuGoTo(0,9);
	     	LCD_enuSendString("3-Kitchen");
			LCD_enuGoTo(1,9);
	     	LCD_enuSendString("4-Garage");
	     	do{
	     		KEYPAD_enuGetPressedKey(&value) ;
	     	}while(value == KEYPAD_u8_NOTPRESSED);
	     	Systic_vDelay_ms(250);
             switch(value)
             {
             	case '1' : // ROOM1
          /*********************************************************************** ROOM1 ***********************************************************************************/
                		         LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                	             LCD_enuSendString("1-Fan");
                	             LCD_enuGoTo(1,0);
                	             LCD_enuSendString("2-Door");
                	             LCD_enuGoTo(0,10);
                	             LCD_enuSendString("3-Temp");
                	             LCD_enuGoTo(1,10);
                	             LCD_enuSendString("4-Heater");
                		         do{
                		        		KEYPAD_enuGetPressedKey(&value) ;
                		         }while(value == KEYPAD_u8_NOTPRESSED);
                		         Systic_vDelay_ms(250);
                		         switch(value)
                		          {
                		         	 	 case '1' : // FAN
                		         	 		 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                		         	 		 	 	 LCD_enuSendString("1-Manual");
                		         	 		 	 	 LCD_enuGoTo(1,0);
                		         	 		 	 	 LCD_enuSendString("2-Automatic");
                		         	 		 	 	 do{
                	                		        		KEYPAD_enuGetPressedKey(&value) ;
                	                		         }while(value == KEYPAD_u8_NOTPRESSED);
                	                		         Systic_vDelay_ms(250);
                	                		         if(value=='1')
                	                		         {
                	                		        	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
                    		         	 		 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                	                		        	 LCD_enuSendString("1-Fan-ON");
                    		         	 		 	 	 LCD_enuGoTo(1,0);
                    		         	 		 	 	 LCD_enuSendString("2-Fan-Off");
                    		         	 		 	 	 do{
                    	                		        		KEYPAD_enuGetPressedKey(&value) ;
                    	                		         }while(value == KEYPAD_u8_NOTPRESSED);
                    	                		         Systic_vDelay_ms(200);
                    	                		         if(value=='1')
                	                		        	  {
                    	                		        	 UART_vTransmite(UART_6,ROOM1,enable); // room1
                	                		                 UART_vTransmite(UART_6,FAN,enable);   // Fan
                	                		                 UART_vTransmite(UART_6,ON,enable);    // ON
                	                		        	  }
                    	                  		         else
                    	                                  {
                    	                               	     UART_vTransmite(UART_6,ROOM1,enable); // room1
                    	                            	 	 UART_vTransmite(UART_6,FAN,enable);   // Fan
                    	                            	 	 UART_vTransmite(UART_6,OFF,enable);   // OFF
                    	                                  }
                	                		         }
                	                		         else
                	                		         {
                	                		        	 UART_vTransmite(UART_6,AUTOMATIC,enable); // AUTOMATIC control
                  	                               	     UART_vTransmite(UART_6,ROOM1,enable);     // room1
                        	                             UART_vTransmite(UART_6,FAN,enable);       // Fan
                        	                             UART_vTransmite(UART_6,OFF,enable);  	   // don't care
                	                		         }

                		         	 		 	 	 break;

                		         	 	 case '2' : // DOOR
        		         	 		 	 	 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                		         	 		 	 	 LCD_enuSendString("1-Door-Open");
                		         	 		 	 	 LCD_enuGoTo(1,0);
                		         	 		 	 	 LCD_enuSendString("2-Door-Close");

                	                		         do{
                	                		        		KEYPAD_enuGetPressedKey(&value) ;
                	                		         }while(value == KEYPAD_u8_NOTPRESSED);
                	                		         Systic_vDelay_ms(250);
                	                		         if(value=='1')
                	                    	          {
                	                		        	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
                	                		        	 UART_vTransmite(UART_6,ROOM1,enable);  // room1
                	                		        	 UART_vTransmite(UART_6,DOOR,enable);   // Door
                	                		        	 UART_vTransmite(UART_6,ON,enable);     // Open
                	                    	          }
                	                    	          else
                	                    	          {
                 	                		        	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
                	                    	        	 UART_vTransmite(UART_6,ROOM1,enable);  // room1
                	                    	        	 UART_vTransmite(UART_6,DOOR,enable);   // Door
                	                    	        	 UART_vTransmite(UART_6,OFF,enable);    // close
                	                    	          }

                		         	 		 	 	 break;

                		         	 	 case '3' : // TEMP
                		         	 		 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                		         	 		 	 	 LCD_enuSendString("Temperature: ");
            	                		        	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
           	                    	        	     UART_vTransmite(UART_6,ROOM1,enable); // send trigger to mc2 to send back the temp
           	                    	        	     UART_vTransmite(UART_6,TEMP,enable);
           	                    	        	     UART_vTransmite(UART_6,ON,enable);
           	                    	        	     Local_u8Temp =UART_u8Recive(UART_6,enable);
                 		         	 		 	 	 LCD_enuSendNumber(Local_u8Temp);
                		         	 		 	 	 Systic_vDelay_ms(250);

                		         	 		 	 	 break;

                		         	 	 case '4' : // HEATER
                		         	 		         LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                		         	 		         LCD_enuSendString("1-Manual");
                		         	 		         LCD_enuGoTo(1,0);
                		         	 		         LCD_enuSendString("2-Automatic");
                		         	 		         do{
                		         	 		         		KEYPAD_enuGetPressedKey(&value) ;
                		         	 		         }while(value == KEYPAD_u8_NOTPRESSED);
                		         	 		         Systic_vDelay_ms(250);
                		         	 		         if(value=='1')
                		         	 		         {
                		         	 		        	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
                		         	 		        	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                		         	 		        	 LCD_enuSendString("1-Heater-ON");
                		         	 		        	 LCD_enuGoTo(1,0);
                		         	 		        	 LCD_enuSendString("2-Heater-Off");
                		         	 		        	 do{
                		         	 		        		 KEYPAD_enuGetPressedKey(&value) ;
                		         	 		        	 }while(value == KEYPAD_u8_NOTPRESSED);
                		         	 		        	 Systic_vDelay_ms(250);
                		         	 		        	 if(value=='1')
                		         	 		        	 {
                		         	 		        		 UART_vTransmite(UART_6,ROOM1,enable);  // room1
                		         	 		        		 UART_vTransmite(UART_6,HEATER,enable); // Heater
                		         	 		        		 UART_vTransmite(UART_6,ON,enable);     // ON
                		         	 		        	 }
                		         	 		        	 else
                		         	 		        	 {
                		         	 		        		 UART_vTransmite(UART_6,ROOM1,enable);  // room1
                		         	 		        		 UART_vTransmite(UART_6,HEATER,enable); // Heater
                		         	 		        		 UART_vTransmite(UART_6,OFF,enable);    // Off
                		         	 		        	 }
                		         	 		         }
                		         	 		         else
                		         	 		         {
                	                		        	 UART_vTransmite(UART_6,AUTOMATIC,enable); // AUTOMATIC control
                	                		        	 UART_vTransmite(UART_6,ROOM1,enable); 	   // room1
                	                		        	 UART_vTransmite(UART_6,HEATER,enable);    // Heater
            		         	 		        		 UART_vTransmite(UART_6,OFF,enable);       // don't care

                		         	 		         }
                		         	 		 	 	 break;
                		          }
                                 break;
            /**********************************************************************************************************************************************************************/




                	case '2' : // Room2
            /********************************************************************* ROOM2 *****************************************************************************************/
                				 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                	             LCD_enuSendString("1-Fan");
                	             LCD_enuGoTo(1,0);
                	             LCD_enuSendString("2-Door");
                	             LCD_enuGoTo(0,10);
                	             LCD_enuSendString("3-Lamp");
                	             do{
                	             		KEYPAD_enuGetPressedKey(&value) ;
                	             }while(value == KEYPAD_u8_NOTPRESSED);
                	             Systic_vDelay_ms(250);
                	             switch(value)
                	              {
                	                 case '1' : //Fan
                	                	 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                	                	 	 	 LCD_enuSendString("1-Fan-ON");
                	                	 	 	 LCD_enuGoTo(1,0);
                	                	 	 	 LCD_enuSendString("2-Fan-Off");
             		         	 		 	 	 do{
             	                		        		KEYPAD_enuGetPressedKey(&value) ;
             	                		         }while(value == KEYPAD_u8_NOTPRESSED);
             	                		         Systic_vDelay_ms(200);
             	                		         if(value == '1')
             	                		         {
             	                		        	UART_vTransmite(UART_6,MANUAL,enable); // manuall control
        	                		        	 	UART_vTransmite(UART_6,ROOM2,enable);  // room2
        	                		        	 	UART_vTransmite(UART_6,FAN,enable);    // Fan
        	                		        	 	UART_vTransmite(UART_6,ON,enable);     // On
             	                		         }
             	                		         else
             	                		         {
             	                		        	UART_vTransmite(UART_6,MANUAL,enable); // manuall control
             	                		         	UART_vTransmite(UART_6,ROOM2,enable);  // room2
             	                		         	UART_vTransmite(UART_6,FAN,enable);    // Fan
             	                		         	UART_vTransmite(UART_6,OFF,enable);    // Off
             	                		         }

                	                	 	 	 break;

                	                 case '2' : //Door
      		         	 		 	 	 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
      		         	 		 	 	 	 	 LCD_enuSendString("1-Manual");
      		         	 		 	 	 	 	 LCD_enuGoTo(1,0);
        		         	 		 	 	 	 LCD_enuSendString("2-Automatic");
        		         	 		 	 	 	 do{
        		         	 		 	 	 		 KEYPAD_enuGetPressedKey(&value) ;
        		         	 		 	 	 	 }while(value == KEYPAD_u8_NOTPRESSED);
        	                		             Systic_vDelay_ms(250);
        	                		             if(value=='1')
        	                		             {
        	                		            	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
        	                		            	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
        	                		            	 LCD_enuSendString("1-Door-Open");
        	                		            	 LCD_enuGoTo(1,0);
        	                		            	 LCD_enuSendString("2-Door-Close");

            	                		             do{
            	                		           	 	KEYPAD_enuGetPressedKey(&value) ;
            	                		             }while(value == KEYPAD_u8_NOTPRESSED);
            	                		             Systic_vDelay_ms(200);
            	                		             if(value=='1')
            	                    	              {
            	                		            	 UART_vTransmite(UART_6,ROOM2,enable); // room1
            	                		            	 UART_vTransmite(UART_6,DOOR,enable);  // Door
            	                		            	 UART_vTransmite(UART_6,ON,enable);    // Open
            	                    	              }
            	                    	              else
            	                    	              {
            	                    	            	 UART_vTransmite(UART_6,ROOM2,enable); // room1
            	                    	            	 UART_vTransmite(UART_6,DOOR,enable);  // Door
            	                    	            	 UART_vTransmite(UART_6,OFF,enable);   // close
            	                    	              }
        	                		             }
        	                		             else
        	                		             {
            	                		        	 UART_vTransmite(UART_6,AUTOMATIC,enable); // AUTOMATIC control
            	                		        	 UART_vTransmite(UART_6,ROOM2,enable); 	   // room2
            	                		        	 UART_vTransmite(UART_6,DOOR,enable);      // Door
        		         	 		        		 UART_vTransmite(UART_6,OFF,enable);       // don't care
        	                		             }
                	                	 	 	 break;

                	                 case '3' :
		         	 		 	 	 	 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
		         	 		 	 	 	 	 	 LCD_enuSendString("1-Manual");
		         	 		 	 	 	 	 	 LCD_enuGoTo(1,0);
		         	 		 	 	 	 	 	 LCD_enuSendString("2-Automatic");
		         	 		 	 	 	 	 	 do{
		         	 		 	 	 	 	 		 KEYPAD_enuGetPressedKey(&value) ;
		         	 		 	 	 	 	      }while(value == KEYPAD_u8_NOTPRESSED);
		         	 		 	 	 	 	 	 Systic_vDelay_ms(250);
		         	 		 	 	 	 	     if(value=='1')
		         	 		 	 	 	 	 	 {
		         	 		 	 	 	 	    	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
		         	 		 	 	 	 	    	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
		         	 		 	 	 	 	    	 LCD_enuSendString("1-Lamp-ON");
		         	 		 	 	 	 	    	 LCD_enuGoTo(1,0);
		         	 		 	 	 	 	    	 LCD_enuSendString("2-Lamp-Off");
		         	 		 	 	 	 	    	 do{
		         	 		 	 	 	 	    		 KEYPAD_enuGetPressedKey(&value) ;
		         	 		 	 	 	 	    	 }while(value == KEYPAD_u8_NOTPRESSED);
		         	 		 	 	 	 	    	 Systic_vDelay_ms(200);
            	                		         	 if(value=='1')
            	                		         	 {
            	                		         		 UART_vTransmite(UART_6,ROOM2,enable); // room2
        	                		            	 	 UART_vTransmite(UART_6,LAMP,enable);  // Lamp
        	                		            	 	 UART_vTransmite(UART_6,ON,enable);    // Open
            	                		         	 }
            	                		         	 else
            	                		         	 {	 UART_vTransmite(UART_6,ROOM2,enable); // room2
            	                		         	 	 UART_vTransmite(UART_6,LAMP,enable);  // Lamp
            	                		         	 	 UART_vTransmite(UART_6,OFF,enable);   // Close
            	                		         	 }
		         	 		 	 	 	 	 	 }
		         	 		 	 	 	 	     else
		         	 		 	 	 	 	     {
            	                		        	 UART_vTransmite(UART_6,AUTOMATIC,enable); // AUTOMATIC control
            	                		        	 UART_vTransmite(UART_6,ROOM2,enable); 	   // room2
            	                		        	 UART_vTransmite(UART_6,LAMP,enable);      // LAMP
        		         	 		        		 UART_vTransmite(UART_6,OFF,enable);       // don't care
		         	 		 	 	 	 	     }
                	                	 	 	 break;
                	             }
                				  break;
           /***********************************************************************************************************************************************************/



                	case '3' : //kitchen
           /********************************************************************* Kitchen *****************************************************************************************/
                            	  LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                            	  LCD_enuSendString("1-Door");
                            	  do{
                            	  		KEYPAD_enuGetPressedKey(&value) ;
                            	  }while(value == KEYPAD_u8_NOTPRESSED);
                            	  Systic_vDelay_ms(250);
                            	  switch(value)
                            	   {
                            	       case '1' :
                            	      	 	 	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
                            	      	 	 	 LCD_enuSendString("1-Door-Open");
                            	      	 	 	 LCD_enuGoTo(1,0);
                            	      	 	 	 LCD_enuSendString("2-Door-Close");
            	                		         do{
            	                		        		KEYPAD_enuGetPressedKey(&value) ;
            	                		         }while(value == KEYPAD_u8_NOTPRESSED);
            	                		         Systic_vDelay_ms(250);
            	                		         if(value=='1')
            	                    	          {
            	                		        	 UART_vTransmite(UART_6,MANUAL,enable);   // manuall control
            	                		        	 UART_vTransmite(UART_6,KITCHEN,enable);  // KITCHEN
            	                		        	 UART_vTransmite(UART_6,DOOR,enable);     // Door
            	                		        	 UART_vTransmite(UART_6,ON,enable);       // Open
            	                    	          }
            	                    	          else
            	                    	          {
             	                		        	 UART_vTransmite(UART_6,MANUAL,enable);   // manuall control
            	                    	        	 UART_vTransmite(UART_6,KITCHEN,enable);  // KITCHEN
            	                    	        	 UART_vTransmite(UART_6,DOOR,enable);     // Door
            	                    	        	 UART_vTransmite(UART_6,OFF,enable);      // close
            	                    	          }
                            	      	 	 	 break;
                            	    }
                            		break;
            /***********************************************************************************************************************************************************/



                  case '4' : //Garage
            /********************************************************************* ROOM2 *****************************************************************************************/
                                    LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
 		         	 		 	 	LCD_enuSendString("1-Manual");
 		         	 		 	 	LCD_enuGoTo(1,0);
   		         	 		 	    LCD_enuSendString("2-Automatic");
   		         	 		 	 	do{
   		         	 		 	 		 KEYPAD_enuGetPressedKey(&value) ;
   		         	 		 	 	}while(value == KEYPAD_u8_NOTPRESSED);
   	                		        Systic_vDelay_ms(250);
   	                		        if(value=='1')
   	                		        {
   	                		        	 UART_vTransmite(UART_6,MANUAL,enable); // manuall control
   	                		        	 LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);
   	                		        	 LCD_enuSendString("1-Door-Open");
   	                		        	 LCD_enuGoTo(1,0);
   	                		        	 LCD_enuSendString("2-Door-Close");

       	                		        do{
       	                		      	 	KEYPAD_enuGetPressedKey(&value) ;
       	                		        }while(value == KEYPAD_u8_NOTPRESSED);
       	                		        Systic_vDelay_ms(200);
       	                		        if(value=='1')
       	                    	         {
       	                		       	 UART_vTransmite(UART_6,GARAGE,enable); // GARAGE
       	                		       	 UART_vTransmite(UART_6,DOOR,enable);  // Door
       	                		       	 UART_vTransmite(UART_6,ON,enable);    // Open
       	                    	         }
       	                    	         else
       	                    	         {
       	                    	       	 UART_vTransmite(UART_6,GARAGE,enable); // GARAGE
       	                    	       	 UART_vTransmite(UART_6,DOOR,enable);  // Door
       	                    	       	 UART_vTransmite(UART_6,OFF,enable);   // close
       	                    	         }
   	                		        }
               		                else
               		                {
	                		        	 UART_vTransmite(UART_6,AUTOMATIC,enable); // AUTOMATIC control
	                		        	 UART_vTransmite(UART_6,GARAGE,enable); 	   // room2
	                		        	 UART_vTransmite(UART_6,DOOR,enable);      // Door
	         	 		        		 UART_vTransmite(UART_6,OFF,enable);       // don't care
               		                }
   	                	 	 	    break;

                	default:
                		            break;
                }


   }
return 0;
}

