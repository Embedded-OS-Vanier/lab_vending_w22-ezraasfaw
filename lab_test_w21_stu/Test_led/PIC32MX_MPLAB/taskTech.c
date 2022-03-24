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
#include "include/Tick_core.h"

/*Semaphores and mutexes declarations*/
//static QueueHandle_t xQueue = NULL;

char buff[100];
static QueueHandle_t xQueue;


static void taskTechnician( void *pvParameters){
    
    pvParameters = pvParameters ;    // This is to get rid of annoying warnings
    char rx;
    while(1){
        
        xQueueReceive(xQueue,&rx, portMAX_DELAY ); 
        sprintf(buff, "%c",rx);
        fprintf2(C_UART1, buff);
        //_LATA0 ^= 1;// Toggles a LED
        
    }
}


/* Public function declarations */
void vStartTaskTech(void){
      xTaskCreate( taskTechnician, ( char * ) "Task Technician", 240, NULL, 1, NULL );
}

void vInitQueue(void){
    xQueue = xQueueCreate( 5, sizeof( char ) );
}

void vSendQueueFromISR(char data){
    xQueueSendFromISR(xQueue,&data,0);
}