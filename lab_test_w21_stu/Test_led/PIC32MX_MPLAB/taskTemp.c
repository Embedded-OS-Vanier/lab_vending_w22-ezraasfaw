/* ***************************************************************************
 * File: vTask1.c
 * Description: to complete
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  
 *****************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "include/public.h"
#include "include/console32.h"
#include "include/Tick_core.h"
#include "include/adc32.h"

int adc;
int temp;

static void taskTemperature( void *pvParameters){
    
    pvParameters = pvParameters ;    // This is to get rid of annoying warnings
    while(1){
        
        _LATA1 ^=1 ;
        vTaskDelay(500/ portTICK_RATE_MS);
        adc = readADC(2);
        temp = adc * 27 /1023;
        temp = temp - 7;
        setTemp(temp);
        
        
        
        
    
    
    
    
    }
   
}


/* Public function declarations */
void vStartTaskTemp(void){
      xTaskCreate( taskTemperature, ( char * ) "Task Temperature", 240, NULL, 2, NULL );
}
