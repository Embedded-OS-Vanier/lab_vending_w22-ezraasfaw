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
char buffn[100];
static QueueHandle_t xQueue;
char rx;
char rec[10];
int acsii_value;
int num;

item_t product;



static void taskTechnician( void *pvParameters){
    
    pvParameters = pvParameters ;    // This is to get rid of annoying warnings
    static int lastTick, i,mode, digit;
    static enum {SM_MENU, SM_INIT,SM_INPUT_SEPERATION, SM_BUTTON, SM_REFRESH, SM_MTNDEW_LOAD, SM_COKE_LOAD, SM_CRUSH_LOAD, SM_TEA_LOAD,SM_TEMPERATURE, SM_RETRIEVE_MONEY, SM_LAST_TRANS,SM_READ_Q, SM_STOCK,SM_PRICE, SM_EXIT} state = SM_MENU;  
    

    
    while(1){

        switch(state){
            case SM_MENU:
                fprintf2(C_LCD, "?Out of order-Temperature issue?");
                fprintf2(C_UART1, "Explorer 16/32 Vending Machine\n");
                fprintf2(C_UART1, "Enter r to refresh display \n");
                fprintf2(C_UART1, "Enter o followed by a 2 digits value between 00 and 99 to load orange bottles\n");
                fprintf2(C_UART1, "Enter c followed by a 2 digits value between 00 and 99 to load cherry bottles\n");
                fprintf2(C_UART1, "Enter l followed by a 2 digits value between 00 and 99 to load lemon bottles\n");
                fprintf2(C_UART1, "Enter t to read fridge temperature\n");
                fprintf2(C_UART1, "Enter e when the machine's money is removed\n");
                fprintf2(C_UART1, "Enter h to find out the last transaction time (in seconds)\n");
                fprintf2(C_UART1, "Enter m to read the amount of quarters currently in the machine\n");
                fprintf2(C_UART1, "Enter s to read the soda stock\n");
                fprintf2(C_UART1, "Enter p to change soda prices\n");
                fprintf2(C_UART1, "Enter k to check out from servicing\n");
                vTaskDelay(20/ portTICK_RATE_MS);
                state = SM_INIT;
    ////////////////////////////Initialization vending machine ////////////////////////
            case SM_INIT:
                xQueueReceive(xQueue,&rx, portMAX_DELAY );  
                sprintf(buff, "%c",rx);
                fprintf2(C_UART1, buff);
                //_LATA0 ^= 1;// Toggles a LED
                state = SM_INPUT_SEPERATION;
                break;   
            case SM_INPUT_SEPERATION:  
                if (rx != '\n'){
                    rec[i] = rx;
                    i++;
                }
                else if (rx == '\n'){
                    i = 0;
                    state = SM_BUTTON;
            
                }
                break;   
/////////////////////////Button Selection with Debouncing//////////////////////////
            case SM_BUTTON:
            
                mode = rec[0];
                sprintf(buffn,"d%d%",rec[1],rec[2]);
                digit = atoi(buffn);
            
                if(mode == 'r') state = SM_REFRESH;
                else if (mode == 'm') state = SM_MTNDEW_LOAD;
                else if (mode == 'k') state = SM_COKE_LOAD;
                else if (mode == 'c') state = SM_CRUSH_LOAD;
                else if (mode == 'i') state = SM_TEA_LOAD;
                else if (mode == 't') state = SM_TEMPERATURE;
                else if (mode == 'e') state = SM_RETRIEVE_MONEY;
                else if (mode == 'h') state = SM_LAST_TRANS;
                else if (mode == 'q') state = SM_READ_Q;
                else if (mode == 's') state = SM_STOCK;
                else if (mode == 'p') state = SM_PRICE;
                else if (mode == 'x') state = SM_EXIT;
            
            
                break;
            
/////////////////////////////////refresh display///////////////////////////////////           
            case SM_REFRESH:
                state = SM_MENU;
                break;
          
/////////////////////////////////load MTNDEW drink/////////////////////////////////
            case SM_MTNDEW_LOAD:
                product= getItem(MTNDEW);
                product.qty = digit;
                sprintf(buff, "MTNDEW stock updated\nMTNDEW in stock is now:%d ", product.qty);
                fprintf2(C_UART1, buff);
                break;
            
//////////////////////////////////load COKE drink//////////////////////////////////
            case SM_COKE_LOAD:
                product= getItem(COKE);
                product.qty = digit;
                sprintf(buff, "COKE stock updated\nMTNDEW in stock is now:%d ", product.qty);
                fprintf2(C_UART1, buff);
                break;
            
/////////////////////////////////load CRUSH drink//////////////////////////////////
            case SM_CRUSH_LOAD:
                product= getItem(CRUSH);
                product.qty = digit;
                sprintf(buff, "CRUSH stock updated\nMTNDEW in stock is now:%d ", product.qty);
                fprintf2(C_UART1, buff);
                break;
            
//////////////////////////////////load TEA drink///////////////////////////////////
            case SM_TEA_LOAD:
                product= getItem(TEA);
                product.qty = digit;
                sprintf(buff, "TEA stock updated\nMTNDEW in stock is now:%d ", product.qty);
                fprintf2(C_UART1, buff);
                break;
            
///////////////////////////////////////////////////////////////////////////////////

    
        }
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