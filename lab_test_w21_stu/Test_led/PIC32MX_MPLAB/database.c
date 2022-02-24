  
/* ***************************************************************************
 * File: main.c
 * Description: 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *        
 *                            
 *****************************************************************************/

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h" 
#include "semphr.h"
#include "croutine.h"
/* Hardware specific includes. */
#include "include/ConfigPerformance.h"
#include "include/console32.h"

#include "include/public.h"
#include <string.h>


#define MAX_ITEM 4

static int itm; 
SemaphoreHandle_t xItem;
  



item_t item[MAX_ITEM]={
    {"Mountain Dew",2,5,MTNDEW},
    {"Coke",2,5,COKE},
    {"Crush",2,5,CRUSH},
    {"Nestea",2,5,TEA}
};


item_t getItem(int i){ 
    xSemaphoreTake( xItem, portMAX_DELAY ); 
    item_t itmTemp;
    itmTemp = item[i]; // Critical Section 
    xSemaphoreGive( xItem); 
    return itmTemp; 
} 
        
//int setItem(int _itm){ 
//    xSemaphoreTake( xItem, portMAX_DELAY ); 
//    itm = _itm;
////    if(itm >= 0)  itemInfo = itm; // Critical Section 
//    xSemaphoreGive( xItem); 
//}




