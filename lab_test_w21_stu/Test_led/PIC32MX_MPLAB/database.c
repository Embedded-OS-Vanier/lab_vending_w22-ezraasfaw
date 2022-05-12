  
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
#include "include/Tick_core.h"
#include "include/public.h"
#include <string.h>
#include "include/adc32.h"

static int totalCredit; 
static int itm; 
static int64_t time;
static int temp;
static int status;



SemaphoreHandle_t xItem;
SemaphoreHandle_t xCredit;   
SemaphoreHandle_t xTime;  
SemaphoreHandle_t xTemp;
SemaphoreHandle_t xStatus;
SemaphoreHandle_t xPrice;


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
    xTime = xSemaphoreCreateMutex();
    xTemp = xSemaphoreCreateMutex();
    xStatus = xSemaphoreCreateMutex();
    xPrice = xSemaphoreCreateMutex();
}
void SetTime(int64_t tempTime){
    xSemaphoreTake(xTime, portMAX_DELAY);  
    time = tempTime;                             
    xSemaphoreGive(xTime);                 
}

int getTime(void){
    int64_t TickDiff,lastTick;
    int finalTime;
    xSemaphoreTake(xTime, portMAX_DELAY);
    lastTick = TickGet();
    TickDiff = lastTick - time;
    finalTime = TickDiff / TICKS_PER_SECOND;
    xSemaphoreGive(xTime);
    return finalTime;

}


void setTemp(int tempTemp){
    xSemaphoreTake(xTemp, portMAX_DELAY);
    temp = tempTemp;
    xSemaphoreGive(xTemp);
}


int getTemp(void){
    int finalTemp;                      
    xSemaphoreTake(xTemp, portMAX_DELAY);    
    finalTemp = temp;                            
    xSemaphoreGive(xTemp);   
    return finalTemp;
}


void setStatus(int tempStatus){
    xSemaphoreTake(xStatus, portMAX_DELAY);   
    status = tempStatus;                                
    xSemaphoreGive(xStatus);                
}


int getStatus(void){
    int finalStatus;                                               
    xSemaphoreTake(xStatus, portMAX_DELAY);    
    finalStatus = status;                                
    xSemaphoreGive(xStatus);                    
    return finalStatus;                                           
}

int getPrice(int itm){ 
    xSemaphoreTake( xPrice, portMAX_DELAY ); 
    int pcTemp;
    if (itm == MTNDEW) pcTemp = item[itm].price;
    else if (itm == COKE) pcTemp = item[itm].price;
    else if (itm == CRUSH) pcTemp = item[itm].price;
    else if (itm == TEA) pcTemp = item[itm].price;
    
    //pcTemp = item[i]; // Critical Section 
    xSemaphoreGive( xPrice); 
    return pcTemp; 
} 
        
void setPrice(int itm, int price){ 
    xSemaphoreTake( xPrice, portMAX_DELAY ); 
    item[itm].price = price;
    
//    if(itm >= 0)  itemInfo = itm; // Critical Section 
    xSemaphoreGive( xPrice); 
}

