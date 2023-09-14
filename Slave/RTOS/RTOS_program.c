/*
 * RTOS_program.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Dell
 */


#include "../LIB/STD_TYPES.h"
#include "../MCAL/SysTick/SysTick_interface.h"
#include "RTOS_interface.h"
#include "RTOS_config.h"
#include "RTOS_private.h"


Task SystemTasks[MAX_NUMBER_TASKS] ={0};
u8 Timing[MAX_NUMBER_TASKS];
Task Empty= {0}; // zero will be assigned to all elements

u8 RTOS_u8CreateTask(void(*handler)(void),u8 Copy_u8Periodicity,u8 Copy_u8Priority, u8 Copy_u8FirstDelay)
{
   u8 Local_u8ErrorState = 0;
   if(Copy_u8Priority < MAX_NUMBER_TASKS)  // verify priority within limit
   {

	   if(SystemTasks[Copy_u8Priority].TaskHandler == 0) // no task
	   {
		   SystemTasks[Copy_u8Priority].TaskHandler = handler ;
		   SystemTasks[Copy_u8Priority].periodicity = Copy_u8Periodicity;
	       Timing     [Copy_u8Priority] = Copy_u8FirstDelay; // example : if Copy_u8FirstDelay = 3 ----> first time to execute the task will be after 3 Tasks
	       SystemTasks[Copy_u8Priority].Tstate = Ready; // by default when we create a task we make it Ready unless we want to make it in the suspend state
	   }
	   else
	   {
		   Local_u8ErrorState = 2; // error_state
	   }
   }
   else
   {
	   Local_u8ErrorState = 1;
   }
}


void RTOS_vScheduler(void) //callback function to systick
{
   u8 Local_u8Counter = 0;
   for (Local_u8Counter = 0 ; Local_u8Counter < MAX_NUMBER_TASKS ; Local_u8Counter ++) // loop over all the container (array of tasks)
   {
          if(SystemTasks[Local_u8Counter].TaskHandler !=0) // before we mask schudling, we need to ask if there's a task or not
          {
              if(SystemTasks[Local_u8Counter].Tstate == Ready) // if it's in the suspend state, we will not make a schdule for it
              {
            	   if( Timing[Local_u8Counter] > 0)
          	    	   Timing[Local_u8Counter]--; // every Tick we need to decrease the timing for this task by 1 until it reaches zero to execute it, and reload the periodcity again , to make this task run every 10 ticks for example , where periodcity is 10 in this example

            	   if(Timing[Local_u8Counter] == 0) // is it suppose to run at this moment ?
          	       {
          	    	   SystemTasks[Local_u8Counter].TaskHandler();  //execute the task
          	    	   Timing[Local_u8Counter] = SystemTasks[Local_u8Counter].periodicity; // to make execution after 10 ticks for example (after desired period)
          	       }

              }
          }
   }
}


u8 RTOS_DeleteTask(u8 Priority) //we pass periority not handler : in order to access the array of structure easliy by periority, i can't access the location in the array of tasks by handler.                             // if i passed the handler i would make a loop to iterate over the array of structutre to search where the location which contain this handler, then delete it
{
	u8 Local_u8ErrorState = 0 ;
   if(SystemTasks[Priority].TaskHandler != 0) // if there's a task
   {
	   SystemTasks[Priority] = Empty; // make this location in the container empty; [ container means (array of structures --> array of tasks) ]
     // this means zero will be assigned to the handler pointer (which means this pointer holds no address)
	   // periodicity = 0 , and first delay = 0
   }
   else // there's no task to delete it
   {
	   Local_u8ErrorState = 1;
   }
   return Local_u8ErrorState;
}


u8 RTOS_vSuspend(u8 Priority)
{
	u8 Local_u8ErrorState = 0 ;
   if(SystemTasks[Priority].TaskHandler != 0) // if there's a task
   {
	   SystemTasks[Priority].Tstate = Suspend;
   }
   else // there's no task to put it into suspend state
   {
	   Local_u8ErrorState = 1;
   }
   return Local_u8ErrorState;
}


u8 RTOS_vResume(u8 Priority)
{
	u8 Local_u8ErrorState = 0 ;
   if(SystemTasks[Priority].TaskHandler != 0) // if there's a task
   {
	   SystemTasks[Priority].Tstate = Ready;
   }
   else // there's no task to put it into Ready state
   {
	   Local_u8ErrorState = 1;
   }
   return Local_u8ErrorState;
}


void RTOS_vStart_OS(void)
{                             /*
     number of ticks = time * freq = 0.005*16000000 = 160 000
  */
	u32 ticktime = 80000;
	Systickk_vPerodic(ticktime,RTOS_vScheduler);
}

