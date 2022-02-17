
/* ***************************************************************************
 * File: vTask1.c
 * Description: to complete
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  Worked on thebutton
 *****************************************************************************/

#include <string.h>
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "include/public.h"
#include "include/console32.h"




#define BTN1WAIT 10
#define BTN2WAIT 2000


#define MTNDEW 0
#define COKE 1
#define CRUSH 2
#define TEA 3


#define S3 PORTDbits.RD6 //S3
#define S4 PORTDbits.RD7 //S4
#define S6 PORTDbits.RD13 //S6

int soda[4] = {MTNDEW, COKE, CRUSH, TEA};
static int totalCredit; 
SemaphoreHandle_t xCredit; 
//xCredit = xSemaphoreCreateMutex(); 

/* Private static function declarations */
static void vTask1( void *pvParameters ){
    pvParameters = pvParameters ; // This is to get rid of annoying warnings
	/* As per most tasks, this task is implemented in an infinite loop. */

    soda[0];
    int i = 0;
 
	for( ;; )
	{   
        static enum {SM_S3, SM_S4,SM_S6} state = SM_S3;  
    
        switch(state){
        
        case SM_S3:
        if(!S3){
            if (i<=3){
                i++;
                //item[i];
                vTaskDelay(10);
               if(!S3) state = SM_S3;
               else state = SM_S4;
            }
            else{
                i = 0;
                state = SM_S3;
            }
            break;
        }
        
        case SM_S4:
        if(!S4){
            totalCredit =+0.25;
            //setCredit(totalCredit);
            state = SM_S4;
            break;
        }
        case SM_S6:
        if(!S6){
            if(totalCredit >= 5000){
                
            }
            else state = SM_S4;
            
            break;
        }
    }
    }
}
/* Public function declarations */
void vStartTask1(void){
     xTaskCreate(	vTask1,						/* Pointer to the function that implements the task. */
					( char * ) "Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,						/* Stack depth in words. */
					NULL,						/* We are not using the task parameter. */
					1,							/* This task will run at priority 1. */
					NULL );						/* We are not using the task handle. */
}

int getCredit(void){ 
    xSemaphoreTake( xCredit, portMAX_DELAY ); 
    int s; 
    s = totalCredit; // Critical Section 
    xSemaphoreGive( xCredit); 
    return s; 
} 
        
void setCredit(int s){ 
    xSemaphoreTake( xCredit, portMAX_DELAY ); 
    if(s >= 0)  totalCredit =s; // Critical Section 
    xSemaphoreGive( xCredit); 
}         