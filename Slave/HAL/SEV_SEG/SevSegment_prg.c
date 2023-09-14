 /*
 * SevSegment_prg.c

 *
 *  Created on: Aug 25, 2022
 *      Author: Seif
 */

#include "../../LIB/STD_TYPES.h"
#include "SevSegment_int.h"
#include "SevSegment_cfg.h"
#include "SevSegment_prv.h"

/// Needed Functions///

void SevSegment_enuDisplayNumber(u8 Copy_u8PIN0, u8 Copy_u8PIN1, u8 Copy_u8PIN2, u8 Copy_u8PIN3 , u8 Copy_u8PIN4, u8 Copy_u8PIN5, u8 Copy_u8PIN6,u8 Copy_u8Number)
{
		switch  (Copy_u8Number)
      	    {
                  case 0 :
                	     MGPIO_voidWriteData (_GPIOA_PORT,Copy_u8PIN0,(SevSegment_u8_ZERO>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT,Copy_u8PIN1,(SevSegment_u8_ZERO>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT,Copy_u8PIN2,(SevSegment_u8_ZERO>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT,Copy_u8PIN3,(SevSegment_u8_ZERO>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT,Copy_u8PIN4,(SevSegment_u8_ZERO>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT,Copy_u8PIN5,(SevSegment_u8_ZERO>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT,Copy_u8PIN6,(SevSegment_u8_ZERO>>6) & 0x01);
                 	                        break;
                  case 1 :
             	     MGPIO_voidWriteData (_GPIOA_PORT, Copy_u8PIN0,(SevSegment_u8_ONE>>0) & 0x01);
             	     MGPIO_voidWriteData (_GPIOA_PORT, Copy_u8PIN1,(SevSegment_u8_ONE>>1) & 0x01);
             	     MGPIO_voidWriteData (_GPIOB_PORT, Copy_u8PIN2,(SevSegment_u8_ONE>>2) & 0x01);
             	     MGPIO_voidWriteData (_GPIOB_PORT, Copy_u8PIN3,(SevSegment_u8_ONE>>3) & 0x01);
             	     MGPIO_voidWriteData (_GPIOB_PORT, Copy_u8PIN4,(SevSegment_u8_ONE>>4) & 0x01);
             	     MGPIO_voidWriteData (_GPIOB_PORT, Copy_u8PIN5,(SevSegment_u8_ONE>>5) & 0x01);
             	     MGPIO_voidWriteData (_GPIOB_PORT, Copy_u8PIN6,(SevSegment_u8_ONE>>6) & 0x01);
                 	       		            break;
                  case 2 :
              	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_TWO>>0) & 0x01);
              	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_TWO>>1) & 0x01);
              	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_TWO>>2) & 0x01);
              	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_TWO>>3) & 0x01);
              	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_TWO>>4) & 0x01);
              	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_TWO>>5) & 0x01);
              	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_TWO>>6) & 0x01);
                      		       		   break;
                  case 3 :
               	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_THREE>>0) & 0x01);
               	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_THREE>>1) & 0x01);
               	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_THREE>>2) & 0x01);
               	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_THREE>>3) & 0x01);
               	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_THREE>>4) & 0x01);
               	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_THREE>>5) & 0x01);
               	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_THREE>>6) & 0x01);
                      		       		   break;
                  case 4 :
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_FOUR>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_FOUR>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_FOUR>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_FOUR>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_FOUR>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_FOUR>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_FOUR>>6) & 0x01);
                      		       		   break;
                  case 5 :
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_FIVE>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_FIVE>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_FIVE>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_FIVE>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_FIVE>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_FIVE>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_FIVE>>6) & 0x01);
                      		       		   break;
                  case 6 :
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_SIX>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_SIX>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_SIX>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_SIX>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_SIX>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_SIX>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_SIX>>6) & 0x01);
                      		       		   break;
                  case 7 :
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_SEVEN>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_SEVEN>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_SEVEN>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_SEVEN>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_SEVEN>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_SEVEN>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_SEVEN>>6) & 0x01);
                      		       		   break;
                  case 8 :
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_EIGHT>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_EIGHT>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_EIGHT>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_EIGHT>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_EIGHT>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_EIGHT>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_EIGHT>>6) & 0x01);
                      		       		   break;
                  case 9 :
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN0,(SevSegment_u8_NINE>>0) & 0x01);
                	     MGPIO_voidWriteData (_GPIOA_PORT , Copy_u8PIN1,(SevSegment_u8_NINE>>1) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN2,(SevSegment_u8_NINE>>2) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN3,(SevSegment_u8_NINE>>3) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN4,(SevSegment_u8_NINE>>4) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN5,(SevSegment_u8_NINE>>5) & 0x01);
                	     MGPIO_voidWriteData (_GPIOB_PORT , Copy_u8PIN6,(SevSegment_u8_NINE>>6) & 0x01);
                      		       		   break;

               }


}

