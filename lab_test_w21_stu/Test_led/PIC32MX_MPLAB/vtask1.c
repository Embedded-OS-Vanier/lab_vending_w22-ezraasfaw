
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

#define MTNDEW 0
#define COKE 1
#define CRUSH 2
#define TEA 3

#define S3 PORTDbits.RD6 //S3
#define S4 PORTDbits.RD7 //S4
#define S6 PORTDbits.RD13 //S6

//#define IFSTATEMENT

#ifndef IFSTATEMENT
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
                    fprintf2(C_LCD, "Select items\n\r");
                    
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
                    fprintf2(C_LCD, "s4\n\r");
                    setCredit(totalCredit + 0.25);
                    //fprintf2(C_UART1, totalCredit);
                    state =  SM_DELAY;     
                    break;  
                    
                case  0x5:
                    fprintf2(C_LCD, "s6\n\r");
                    if(totalCredit >= product.price){
                        totalCredit = totalCredit - product.price;
                        //fprintf2(C_UART1, totalCredit);
                    }
                    else {
                        reqFund = product.price - totalCredit;
                        //fprintf2(C_UART1, reqFund);
                    }
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
                    if(statePB== 0x0003) state =  SM_POLL;
                    break;    
          
    }
    }
}


int getCredit(void){ 
    xSemaphoreTake( xCredit, portMAX_DELAY ); 
    int s; 
    s = totalCredit; // Critical Section 
    xSemaphoreGive( xCredit); 
    return s; 
} 
        
int setCredit(int s){ 
    xSemaphoreTake( xCredit, portMAX_DELAY ); 
    if(s >= 0)  totalCredit = s; // Critical Section 
    xSemaphoreGive( xCredit); 
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

#ifdef IFSTATEMENT
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

item_t product;


/* Private static function declarations */
static void vTask1( void *pvParameters ){
    pvParameters = pvParameters ; // This is to get rid of annoying warnings
	/* As per most tasks, this task is implemented in an infinite loop. */

    soda[0];
    int i = 0, temp_c;
   
	for( ;; )
	{    
        totalCredit = getCredit();
        static enum {SM_INIT,SM_BUTTON,SM_S3, SM_S4,SM_S6} state = SM_S3;  
        switch(state){
        
            
            
        case SM_INIT:
            soda[0];
            int i = 0, temp_c;
            fprintf2(C_UART1, "Menu\n");
            state = SM_BUTTON;
            break;
            
        case SM_BUTTON:
            if(!S3){
            state = SM_S3;
            }
            else if(!S4){
            state = SM_S4;
            }
            else if(!S6){
            state = SM_S6;
            }
            else state = SM_BUTTON;
            break;
        
        case SM_S3:
            if (i<=3){
                i++;
                //item[i];
                product.tag;
                vTaskDelay(10);
                if(!S3) state = SM_S3;
                else state = SM_BUTTON;
            }
            else{
                i = 0;
                state = SM_S3;
            }
            break;
        
        
        case SM_S4:
        
            setCredit(totalCredit + 0.25);
            state = SM_S4;
            vTaskDelay(10);
            if(!S4) state = SM_S4;
            else state = SM_S6;
            break;
        
        case SM_S6:
        
            if(totalCredit >= 5000){
                totalCredit = totalCredit - 5000;
            }
            else state = SM_S4;
            
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

THOSE SETTER-GETTER BELONG TO DATABASE
int getCredit(void){ 
    xSemaphoreTake( xCredit, portMAX_DELAY ); 
    int s; 
    s = totalCredit; // Critical Section 
    xSemaphoreGive( xCredit); 
    return s; 
} 
        
int setCredit(int s){ 
    xSemaphoreTake( xCredit, portMAX_DELAY ); 
    if(s >= 0)  totalCredit = s; // Critical Section 
    xSemaphoreGive( xCredit); 
}         

//int getItem(void){ 
//    xSemaphoreTake( xItem, portMAX_DELAY ); 
//    int itm; 
//    itm = itemInfo; // Critical Section 
//    xSemaphoreGive( xItem); 
//    return itm; 
//} 
//        
//int setItem(int itm){ 
//    xSemaphoreTake( xItem, portMAX_DELAY ); 
//    if(itm >= 0)  itemInfo = itm; // Critical Section 
//    xSemaphoreGive( xItem); 
//}

#endif 

