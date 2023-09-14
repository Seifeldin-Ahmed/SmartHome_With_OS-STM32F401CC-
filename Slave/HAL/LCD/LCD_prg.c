/*
 * LCD_prg.c
 *
 *  Created on: Aug 26, 2022
 *      Author: Dell
 */
#include"../../LIB/STD_TYPES.h"
#include "../../MCAL/GPIO/MGPIO_interface.h"
#include "../../MCAL/SysTick/SysTick_interface.h"
#include "LCD_int.h"



//------------PRIVATE------------//


static void LCD_vidSendEnable(void)
{
	MGPIO_voidWriteData(LCD_u8_E_PORT,LCD_u8_E_PIN,HIGH);
	Systic_vDelay_ms(1);
	MGPIO_voidWriteData(LCD_u8_E_PORT,LCD_u8_E_PIN,LOW);
}


//------------------------------//

/* Name:LCD_VidInit
 * Description: initialize the LCD in 8 bit mode
 * Argument: void
 * Return: void
 * */
void LCD_VidInit(void)
{
	
#if defined eight_bit_mode
	Systic_vDelay_ms(32);

	/* function set */
	LCD_enuSendInstruction(LCD_u8_FUNCTION_SET);

	Systic_vDelay_ms(1);
	/* display control */
	LCD_enuSendInstruction(LCD_u8_DISPLAY_ON_CURSOR_OFF);

	Systic_vDelay_ms(1);
	/* display control */
	LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);

	LCD_enuSendInstruction(LCD_u8_RETURN_HOME);

	Systic_vDelay_ms(2);
	/* entry mode */
	LCD_enuSendInstruction(LCD_u8_CURSOR_INC_SHIFT_OFF);
	Systic_vDelay_ms(7);
 
 #elif defined four_bit_mode 

	Systic_vDelay_ms(32);


   LCD_enuSendInstruction(0x02);

 	/* function set */
 	LCD_enuSendInstruction(LCD_u8_FUNCTION_SET);

 	Systic_vDelay_ms(1);
 	/* display control */
 	LCD_enuSendInstruction(LCD_u8_DISPLAY_ON_CURSOR_OFF);

 	Systic_vDelay_ms(1);
 	/* display control */
 	LCD_enuSendInstruction(LCD_u8_CLEAR_DISPLAY);

 //	LCD_enuSendInstruction(LCD_u8_RETURN_HOME);

 	Systic_vDelay_ms(2);
	 
 	/* entry mode */
 	LCD_enuSendInstruction(LCD_u8_CURSOR_INC_SHIFT_OFF);
 	Systic_vDelay_ms(7);

 #endif
}



/* name: LCD_enuSendCharacter
 * Description: send ASCII CODE Character to LCD Microcontroller
 * Argument: Copy_u8Character   (The Desired Character to be Displayed)
 * Return: void
 * */
void LCD_enuSendCharacter(u8 Copy_u8Character)
{
	#if defined eight_bit_mode
	    		  /* Rs pin ----> high */
					MGPIO_voidWriteData(LCD_u8_RS_PORT,LCD_u8_RS_PIN,HIGH);

	         	  /* RW pin ----> low */
					MGPIO_voidWriteData(LCD_u8_RW_PORT, LCD_u8_RW_PIN, LOW);

	              // Send data //
					MGPIO_voidWriteData(LCD_u8_D0_PORT, LCD_u8_D0_PIN, (Copy_u8Character >> 0) & 1);
					MGPIO_voidWriteData(LCD_u8_D1_PORT, LCD_u8_D1_PIN, (Copy_u8Character >> 1) & 1);
					MGPIO_voidWriteData(LCD_u8_D2_PORT, LCD_u8_D2_PIN, (Copy_u8Character >> 2) & 1);
	         		MGPIO_voidWriteData(LCD_u8_D3_PORT, LCD_u8_D3_PIN, (Copy_u8Character >> 3) & 1);
	         		MGPIO_voidWriteData(LCD_u8_D4_PORT, LCD_u8_D4_PIN, (Copy_u8Character >> 4) & 1);
	         		MGPIO_voidWriteData(LCD_u8_D5_PORT, LCD_u8_D5_PIN, (Copy_u8Character >> 5) & 1);
	         		MGPIO_voidWriteData(LCD_u8_D6_PORT, LCD_u8_D6_PIN, (Copy_u8Character >> 6) & 1);
	         		MGPIO_voidWriteData(LCD_u8_D7_PORT, LCD_u8_D7_PIN, (Copy_u8Character >> 7) & 1);

	    //     	 DIO_enuSetPortValue(DIO_u8_PORTC, Copy_u8Character);
	         	   // Enable //
	         	 LCD_vidSendEnable();
               Systic_vDelay_ms(4);
#elif defined four_bit_mode


           // *************************** SENDING THE THE HIGH NIBBLE FIRST *******************************/////
       	    		  /* Rs pin ----> high */
               	       MGPIO_voidWriteData(LCD_u8_RS_PORT,LCD_u8_RS_PIN,HIGH);

       	    		  /* RW pin ----> low */
               	   	   MGPIO_voidWriteData(LCD_u8_RW_PORT, LCD_u8_RW_PIN,LOW);

                      // Send data //
       	    		  MGPIO_voidWriteData(LCD_u8_D4_PORT, LCD_u8_D4_PIN, (Copy_u8Character >> 4) & 1);
       	    		  MGPIO_voidWriteData(LCD_u8_D5_PORT, LCD_u8_D5_PIN, (Copy_u8Character >> 5) & 1);
       	    		  MGPIO_voidWriteData(LCD_u8_D6_PORT, LCD_u8_D6_PIN, (Copy_u8Character >> 6) & 1);
       	    		  MGPIO_voidWriteData(LCD_u8_D7_PORT, LCD_u8_D7_PIN, (Copy_u8Character >> 7) & 1);

       	    		  //     	 DIO_enuSetPortValue(DIO_u8_PORTC, Copy_u8Character);
       	    		  // Enable //
       	    		  LCD_vidSendEnable();
						 
		 // *************************** SENDING THE THE lOW NIBBLE FIRST ********************************//////	 
						  	  /* Rs pin ----> high */
       	    		  MGPIO_voidWriteData(LCD_u8_RS_PORT,LCD_u8_RS_PIN,HIGH);
				       
				       /* RW pin ----> low */
       	    		  MGPIO_voidWriteData(LCD_u8_RW_PORT, LCD_u8_RW_PIN,LOW);
				       
				       // Send data //
				       MGPIO_voidWriteData(LCD_u8_D4_PORT, LCD_u8_D4_PIN, (Copy_u8Character >> 0) & 1);
				       MGPIO_voidWriteData(LCD_u8_D5_PORT, LCD_u8_D5_PIN, (Copy_u8Character >> 1) & 1);
				       MGPIO_voidWriteData(LCD_u8_D6_PORT, LCD_u8_D6_PIN, (Copy_u8Character >> 2) & 1);
				       MGPIO_voidWriteData(LCD_u8_D7_PORT, LCD_u8_D7_PIN, (Copy_u8Character >> 3) & 1);
				       
				       
				       //     	 DIO_enuSetPortValue(DIO_u8_PORTC, Copy_u8Character);
				       // Enable //
				         LCD_vidSendEnable();	
						 Systic_vDelay_ms(12);
						
	#endif					  
						 
}


/* name: LCD_enuSendInstruction
 * Description: send instruction to LCD Microcontroller
 * Argument: Copy_u8Instruction   (The Desired Instruction to be Executed)
 * Return: Error Status >>>>> LCD_OK , LCD_NOK
 * */
LCD_enutErrorStatus LCD_enuSendInstruction(u8 Copy_u8Instruction)
{
	LCD_enutErrorStatus  Local_enuErrorStatus = LCD_OK;

	  if(0)
	  {
		  Local_enuErrorStatus=LCD_NOK;
	  }
	  else
	  {
		  #if defined eight_bit_mode
    		  /* Rs pin ----> low */
		      MGPIO_voidWriteData(LCD_u8_RS_PORT,LCD_u8_RS_PIN,LOW);

         	  /* RW pin ----> low */
		      MGPIO_voidWriteData(LCD_u8_RW_PORT, LCD_u8_RW_PIN, LOW);

              // Send instructions //
         		MGPIO_voidWriteData(LCD_u8_D0_PORT, LCD_u8_D0_PIN, (Copy_u8Instruction >> 0) & 1);
         		MGPIO_voidWriteData(LCD_u8_D1_PORT, LCD_u8_D1_PIN, (Copy_u8Instruction >> 1) & 1);
         		MGPIO_voidWriteData(LCD_u8_D2_PORT, LCD_u8_D2_PIN, (Copy_u8Instruction >> 2) & 1);
         		MGPIO_voidWriteData(LCD_u8_D3_PORT, LCD_u8_D3_PIN, (Copy_u8Instruction >> 3) & 1);
         		MGPIO_voidWriteData(LCD_u8_D4_PORT, LCD_u8_D4_PIN, (Copy_u8Instruction >> 4) & 1);
         		MGPIO_voidWriteData(LCD_u8_D5_PORT, LCD_u8_D5_PIN, (Copy_u8Instruction >> 5) & 1);
         		MGPIO_voidWriteData(LCD_u8_D6_PORT, LCD_u8_D6_PIN, (Copy_u8Instruction >> 6) & 1);
         		MGPIO_voidWriteData(LCD_u8_D7_PORT, LCD_u8_D7_PIN, (Copy_u8Instruction >> 7) & 1);

         	   // Enable //
         	 LCD_vidSendEnable();
			  Systic_vDelay_ms(4);
		#elif defined four_bit_mode	  
		
 // *************************** SENDING THE THE HIGH NIBBLE FIRST ********************************//////	 
			  /* Rs pin ----> low */
			  MGPIO_voidWriteData(LCD_u8_RS_PORT,LCD_u8_RS_PIN,LOW);

			  /* RW pin ----> low */
			  MGPIO_voidWriteData(LCD_u8_RW_PORT, LCD_u8_RW_PIN, LOW);

			  MGPIO_voidWriteData(LCD_u8_D4_PORT, LCD_u8_D4_PIN, (Copy_u8Instruction >> 4) & 1);
			  MGPIO_voidWriteData(LCD_u8_D5_PORT, LCD_u8_D5_PIN, (Copy_u8Instruction >> 5) & 1);
			  MGPIO_voidWriteData(LCD_u8_D6_PORT, LCD_u8_D6_PIN, (Copy_u8Instruction >> 6) & 1);
			  MGPIO_voidWriteData(LCD_u8_D7_PORT, LCD_u8_D7_PIN, (Copy_u8Instruction >> 7) & 1);

			  // Enable //
			  LCD_vidSendEnable();
			  
    // *************************** SENDING THE THE lOW NIBBLE FIRST ********************************//////	 
			  	  /* Rs pin ----> low */
			     MGPIO_voidWriteData(LCD_u8_RS_PORT,LCD_u8_RS_PIN,LOW);

			  	  /* RW pin ----> low */
			     MGPIO_voidWriteData(LCD_u8_RW_PORT, LCD_u8_RW_PIN,LOW);

			  	  // Send instructions //
			  	 MGPIO_voidWriteData(LCD_u8_D4_PORT, LCD_u8_D4_PIN, (Copy_u8Instruction >> 0) & 1);
			  	 MGPIO_voidWriteData(LCD_u8_D5_PORT, LCD_u8_D5_PIN, (Copy_u8Instruction >> 1) & 1);
			  	 MGPIO_voidWriteData(LCD_u8_D6_PORT, LCD_u8_D6_PIN, (Copy_u8Instruction >> 2) & 1);
			  	 MGPIO_voidWriteData(LCD_u8_D7_PORT, LCD_u8_D7_PIN, (Copy_u8Instruction >> 3) & 1);

			  	  // Enable //
			  	  LCD_vidSendEnable();
				 Systic_vDelay_ms(12);
	  }

#endif
     return Local_enuErrorStatus;
}



LCD_enutErrorStatus LCD_enuGoTo(u8 Copy_u8Row , u8 Copy_u8Col)
{
	LCD_enutErrorStatus  Local_enuErrorStatus = LCD_OK;

	 if(Copy_u8Row >LCD_u8_ROW1 ||  Copy_u8Col>LCD_u8_COL15)
	 {
		 Local_enuErrorStatus = LCD_NOK;
	 }
	 else
	 {
		 switch (Copy_u8Row)
		 {
		     case LCD_u8_ROW0:
		    	                  LCD_enuSendInstruction(LCD_u8_FIRST_DDRAM_ADDRESS + Copy_u8Col);
		    	                    break;
		     case LCD_u8_ROW1:
		    	                  LCD_enuSendInstruction(LCD_u8_FIRST_DDRAM_ADDRESS + (Copy_u8Col+0x40));
		    	                    break;
		 }

	 }
    return Local_enuErrorStatus;
}


LCD_enutErrorStatus	LCD_enuSendString(u8* Add_pu8String)
{
	LCD_enutErrorStatus Local_enuErrorStatus = LCD_OK;

		if(Add_pu8String == NULL)
		{
			Local_enuErrorStatus = LCD_NOK;
		}
		else
		{
                  while(*Add_pu8String!='\0')
                     {
                	  LCD_enuSendCharacter(*Add_pu8String);
                    	   Add_pu8String++;
                    }
		}
		return Local_enuErrorStatus;
}


LCD_enutErrorStatus LCD_enuSendCustomCharacter(u8 *Add_u8Pattern,u8 Copy_u8NumOfBlock , u8 Copy_u8Row , u8 Copy_u8Col)
{
	LCD_enutErrorStatus Local_enuErrorStatus = LCD_OK;
     u8 Local_u8Iterator=8;
	if(Add_u8Pattern == NULL || Copy_u8NumOfBlock > 7 || Copy_u8Row > LCD_u8_ROW1 || Copy_u8Col > LCD_u8_COL15)
	{
		Local_enuErrorStatus=LCD_NOK;
	}

	else
	{
	      LCD_enuSendInstruction(LCD_u8_FIRST_CGRAM_ADDRESS + (Copy_u8NumOfBlock*8)); // the block is 8 byte so we jumb a block not a byte
	    while(Local_u8Iterator--)
		  {
	    	LCD_enuSendCharacter (*Add_u8Pattern);
		    Add_u8Pattern++;
		    Systic_vDelay_ms(5);
	      }

	    LCD_enuGoTo(Copy_u8Row,Copy_u8Col);
	    LCD_enuSendCharacter(Copy_u8NumOfBlock);
	}

	return Local_enuErrorStatus;
}




void LCD_enuSendNumber(u32 Copy_u32Number)
{

    u8 Local_u8Reminder=0;
    u8 LCD_au8Reminder[15];
    u8 Local_u8Index=0;
	s8 Local_s8Iterator;
	if(Copy_u32Number == 0)
	{
		LCD_enuSendCharacter('0');
	}
	else
	{
          while(Copy_u32Number!=0)
          {
	          Local_u8Reminder=Copy_u32Number%10;   //    1
	          Copy_u32Number=Copy_u32Number/10;   //1
	          LCD_au8Reminder[Local_u8Index]=Local_u8Reminder;
	          Local_u8Index++;
          }
          
          for (Local_s8Iterator=Local_u8Index-1 ; Local_s8Iterator>=0; --Local_s8Iterator)
                 LCD_enuSendCharacter(LCD_au8Reminder[Local_s8Iterator]+48);
	}		  

}


