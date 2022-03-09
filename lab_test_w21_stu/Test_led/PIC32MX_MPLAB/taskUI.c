
/* ***************************************************************************
 * File: vTask1.c
 * Description: to complete
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  
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


#define TICK_100MS 10000


#define S3 PORTDbits.RD6 //S3
#define S4 PORTDbits.RD7 //S4
#define S6 PORTDbits.RD13 //S6

#define IFSTATEMENTCODE

#ifndef IFSTATEMENTCODE
static int totalCredit; 
SemaphoreHandle_t xCredit; 
//xCredit = xSemaphoreCreateMutex(); 

item_t product;


/* Private static function declarations */
static void vTask1( void *pvParameters ){
    pvParameters = pvParameters ; // This is to get rid of annoying warnings
	/* As per most tasks, this task is implemented in an infinite loop. */
    static enum {SM_POLL,SM_ACTION,SM_DELAY, SM_DEB} state = SM_POLL;  
    static int statePB, lastTick, i, reqFund;
    static char* proName, proPrice;

	for( ;; )
	{    
        //totalCredit = getCredit();

        switch(state){
          
        case SM_POLL:
            
            fprintf2(C_LCD, "Menu\n\r");
            statePB= (S6 << 2 | S4 << 1 | S3 )& 0x0007; 
            if(statePB != 0x0007){
                state = SM_ACTION;
            }
            break;
            
        case  SM_ACTION:
            
            switch(statePB){
                lastTick = TickGet();
                case  0x4:
                     //some actions due to BTN0
                    fprintf2(C_UART1, "Select items\n\r");
                    
                    if (i<=3){
                        i++;
                        getItem(i);
                        proName = product.name;
                        //fprintf2(C_UART1, proName);
                        
                    }
                    else{
                        i = 0;
                        getItem(i);
                        proName = product.name;
                        //fprintf2(C_UART1, proName);
                    }
                    state =  SM_DELAY;
                    break;    
                    
                case  0x3:
                    fprintf2(C_UART1, "s4\n\r");
                    setCredit(totalCredit + 0.25);
                    //fprintf2(C_UART1, totalCredit);
                    state =  SM_DELAY;     
                    break;  
                    
                case  0x5:
                    fprintf2(C_UART1, "s6\n\r");
//                    if(totalCredit >= product.price){
//                        totalCredit = totalCredit - product.price;
//                        //fprintf2(C_UART1, totalCredit);
//                    }
//                    else {
//                        reqFund = product.price - totalCredit;
//                        //fprintf2(C_UART1, reqFund);
//                    }
                    state =  SM_DELAY;     
                    break;
            }// switch statePB
            
        case SM_DELAY:
            if(TickGet() - lastTick>= (TICK_100MS)) {
                        state =  SM_DEB;
                        lastTick= TickGet();
            }
                    break;
            
        case SM_DEB:// Debounce delay
                    statePB= (S6 << 2 | S4 << 1 | S3 )& 0x0007; // PBs release wait
                    if(statePB== 0x0007) state =  SM_POLL;
                    break;    
          
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

#endif

#ifdef IFSTATEMENTCODE
/* ***************************************************************************
 * File: vTask1.c
 * Description: to complete
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  
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


static int totalCredit; 
SemaphoreHandle_t xCredit; 
//xCredit = xSemaphoreCreateMutex(); 

item_t product;


/* Private static function declarations */
static void vTask1( void *pvParameters ){
    pvParameters = pvParameters ; // This is to get rid of annoying warnings
	/* As per most tasks, this task is implemented in an infinite loop. */

    char buff[100];
    int i;
    static enum {SM_INIT,SM_BUTTON,SM_S3, SM_S4,SM_S6,SM_MTN,SM_COKE, SM_CRUSH, SM_TEA} state = SM_INIT;  
    static char* proName, proPrice;
	for( ;; )
	{    
        //totalCredit = getCredit();
        
        switch(state){
        
            
            
        case SM_INIT:
            
            i = 0;
                #ifndef SIMULATION
                    fprintf2(C_LCD, "            Select items\n");
                #endif   

    
                #ifdef SIMULATION
                    fprintf2(C_UART1, "            Select items\n");
                #endif
            
                vTaskDelay(1000/ portTICK_RATE_MS);
                
            state = SM_BUTTON;
            break;
            
            
            
        case SM_BUTTON:
            
            if(!S3) state = SM_S3;
            else if(!S4) state = SM_S4;
            else if(!S6) state = SM_S6;
            else state = SM_BUTTON;
            break;
        
        case SM_S3:
            vTaskDelay(500/ portTICK_RATE_MS);
                #ifndef SIMULATION
                    
                    fprintf2(C_LCD, "S3                  \n");
                    
                #endif   

                #ifdef SIMULATION
                    fprintf2(C_UART1, "S3                  \n");
                #endif
            if (i<=4){
                
                vTaskDelay(1000/ portTICK_RATE_MS);
                i++;
                if(i == MTNDEW)state = SM_MTN;
                else if(i == COKE)state = SM_COKE;
                else if(i == CRUSH)state = SM_CRUSH;
                else if(i == TEA)state = SM_TEA;
                else state = SM_BUTTON;
                
                #ifndef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_LCD, buff);
                #endif   

    
                #ifdef SIMULATION
//                    sprintf(buff, "%s",product.name);
//                    fprintf2(C_UART1, buff);
                #endif
                
            }
            else{
                i = 0;
                state = SM_BUTTON;
            }
            break;
        
        
        case SM_S4:
            vTaskDelay(500/ portTICK_RATE_MS);
                #ifndef SIMULATION
                    fprintf2(C_LCD, "S4                  \n");
                #endif   

    
                #ifdef SIMULATION
                    fprintf2(C_UART1, "S4                  \n");
                #endif
            

            
            //setCredit(totalCredit + 0.25);
            vTaskDelay(10);
            state = SM_BUTTON;
            break;
        
        case SM_S6:

            vTaskDelay(500/ portTICK_RATE_MS);
            
                #ifndef SIMULATION
                    fprintf2(C_LCD, "S6                  \n");
                #endif   

    
                #ifdef SIMULATION
                    fprintf2(C_UART1, "S6                  \n");
                #endif
            
            
            if(totalCredit >= 5000){
                totalCredit = totalCredit - 5000;
            }
            else state = SM_BUTTON;
            
            break;
            
            
            case SM_MTN:
                    product= getItem(MTNDEW);
                    
                #ifndef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_LCD, buff);
                #endif   

    
                #ifdef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_UART1, buff);
                #endif
            
                    
                    vTaskDelay(500/ portTICK_RATE_MS);
                    state = SM_BUTTON;
   
                    
            case SM_COKE:
                    product= getItem(COKE);
                    
                #ifndef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_LCD, buff);
                #endif   

    
                #ifdef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_UART1, buff);
                #endif
                    
                    vTaskDelay(500/ portTICK_RATE_MS);
                    state = SM_BUTTON;
   
                    
            case SM_CRUSH:
                    product= getItem(CRUSH);
                    
                #ifndef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_LCD, buff);
                #endif   

    
                #ifdef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_UART1, buff);
                #endif
                    
                    vTaskDelay(500/ portTICK_RATE_MS);
                    state = SM_BUTTON;
       
                    
            case SM_TEA:
                    product= getItem(TEA);
                    
                #ifndef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_LCD, buff);
                #endif   

    
                #ifdef SIMULATION
                    sprintf(buff, "%s",product.name);
                    fprintf2(C_UART1, buff);
                #endif
                    
                    vTaskDelay(500/ portTICK_RATE_MS);
                    state = SM_BUTTON;
        
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


#endif 

