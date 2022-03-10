  
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


static int itm; 
SemaphoreHandle_t xItem;
static int totalCredit; 
SemaphoreHandle_t xCredit;   



item_t item[MAX_ITEM]={
    {"MtnDew",2,5,MTNDEW},
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
        
int setItem(int itm, int qty){ 
    xSemaphoreTake( xItem, portMAX_DELAY ); 
    item[itm].qty = qty;
    
//    if(itm >= 0)  itemInfo = itm; // Critical Section 
    xSemaphoreGive( xItem); 
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

void initmutex(void){
    xCredit = xSemaphoreCreateMutex();
    xItem = xSemaphoreCreateMutex();
}
