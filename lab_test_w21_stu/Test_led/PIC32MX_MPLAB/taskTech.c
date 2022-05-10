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

/*Semaphores and mutexes declarations*/
//static QueueHandle_t xQueue = NULL;

char buff[100];
char buffn[100];
static QueueHandle_t xQueue;
char rx;
char rec[10];
int acsii_value;
int reset;
int lastTick;
int digit;
int i = 0;
int flag = 0;
char mode;
int credit;

item_t product;



static void taskTechnician( void *pvParameters){
    
    pvParameters = pvParameters ;    // This is to get rid of annoying warnings
   
    static enum { SM_MENU,SM_INIT,SM_INPUT_SEPERATION, SM_BUTTON, SM_REFRESH, SM_MTNDEW_LOAD, SM_COKE_LOAD, SM_CRUSH_LOAD, SM_TEA_LOAD,SM_TEMPERATURE, SM_RETRIEVE_MONEY, SM_LAST_TRANS,SM_READ_Q, SM_STOCK,SM_PRICE, SM_EXIT} state = SM_INIT;  
    

    //UItech();
    while(1){

        switch(state){
            case SM_MENU:
                UItech();
                state = SM_INIT;
    ////////////////////////////Initialization vending machine ////////////////////////
            case SM_INIT:
//                if (flag == 0){
                UItech();
                xQueueReceive(xQueue,&rx, portMAX_DELAY );  
                sprintf(buff, "%c",rx);
                fprintf2(C_UART2, buff);

                if (rx == '\n' || rx == '\r'){
                    i = 0;
                    state = SM_BUTTON;
            
                }
                else{
                    
                    rec[i] = rx;
                    i++;
                    }
                    
                
                break;   
/////////////////////////Button Selection with Debouncing//////////////////////////
            case SM_BUTTON:
            
                vTaskDelay(10);
                
                mode = rec[0];
                sprintf(buffn,"%c%c",rec[1],rec[2]);
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
                UItech();
                state = SM_INIT;
                break;
          
/////////////////////////////////load MTNDEW drink/////////////////////////////////
            case SM_MTNDEW_LOAD:
                product= getItem(MTNDEW);
                product.qty = digit;
                sprintf(buff, "MTNDEW stock updated\nMTNDEW in stock is now:%d ", product.qty);
                fprintf2(C_UART2, buff);
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                state = SM_INIT;
                break;
            
//////////////////////////////////load COKE drink//////////////////////////////////
            case SM_COKE_LOAD:
                product= getItem(COKE);
                product.qty = digit;
                sprintf(buff, "COKE stock updated\nCOKE in stock is now:%d ", product.qty);
                fprintf2(C_UART2, buff);
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                state = SM_INIT;
                break;
            
/////////////////////////////////load CRUSH drink//////////////////////////////////
            case SM_CRUSH_LOAD:
                product= getItem(CRUSH);
                product.qty = digit;
                sprintf(buff, "CRUSH stock updated\nCRUSH in stock is now:%d ", product.qty);
                fprintf2(C_UART2, buff);
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                state = SM_INIT;
                break;
            
//////////////////////////////////load TEA drink///////////////////////////////////
            case SM_TEA_LOAD:
                product= getItem(TEA);
                product.qty = digit;
                sprintf(buff, "TEA stock updated\nTEA in stock is now:%d ", product.qty);
                fprintf2(C_UART2, buff);
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                state = SM_INIT;
                break;
                
                
/////////////////////////////////Retrieve Money/////////////////////////////////////
            case SM_RETRIEVE_MONEY:
                credit = getCredit();
                setCredit(credit = 0);
                fprintf2(C_UART2, "Retrieve credit\n Credit total is now 0Q");
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                state = SM_INIT;
                break;
              
/////////////////////////////////Retrieve Money/////////////////////////////////////
            case SM_LAST_TRANS:                                                                       
                sprintf(buff, "Last transaction happened %d seconds ago\n\r", getTime());  
                fprintf2(C_UART2, buff);                                                                            
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                state = SM_INIT;
                break;
                
/////////////////////////////////////////////////////////////////////////////////
            case SM_TEMPERATURE:                                                               
                sprintf(buff, "Fridge temperature is  %d  degree\n\r", getTemp()); 
                fprintf2(C_UART2, buff);                                                                
                vTaskDelay(DELAY/ portTICK_RATE_MS); 
                state = SM_INIT;                                                                         
                break;
                
 /////////////////////////////////////////////////////////////////////////////////
            case SM_READ_Q:
                sprintf(buff, " %d Q in the Vending Machine\n\r", getCredit());   
                fprintf2(C_UART2, buff);                                                            
                vTaskDelay(DELAY/ portTICK_RATE_MS); 
                state = SM_INIT;                                                                   
                break;
                
  /////////////////////////////////////////////////////////////////////////////////
            case SM_STOCK:
                product= getItem(MTNDEW);
                sprintf(buff, "%d cans of MTNDEW in the Vending Machine\n\r\n\r", product.qty ); 
                fprintf2(C_UART2, buff);                                                         
                
                product= getItem(COKE);
                sprintf(buff, "%d cans of COKE in the Vending Machine\n\r\n\r", product.qty );  
                fprintf2(C_UART2, buff);      
                
                product= getItem(CRUSH);
                sprintf(buff, "%d cans of CRUSH in the Vending Machine\n\r\n\r", product.qty ); 
                fprintf2(C_UART2, buff);                                                   

                product= getItem(TEA);
                sprintf(buff, "%d cans of TEA in the Vending Machine\n\r\n\r", product.qty ); 
                fprintf2(C_UART2, buff);  
                
                vTaskDelay(DELAY/ portTICK_RATE_MS); 
                state = SM_INIT;                                                                   
                break;
                
  /////////////////////////////////////////////////////////////////////////////////
//            case SM_PRICE:
//                if(rx == 'd'){                                                           
//                    state = SM_INIT;                                                              
//                }
//                else{
//                    
//                    sprintf(buffn, "%c%c", rx[2], rx[3]);               
//                    DrinkPrice = atoi(temp_buffer);                                                         
//                    
//                    if(TaskTechnician_rx[0] == 'o' && TaskTechnician_rx[1] == 'p'){
//                        mutex_SetPriceVM(DrinkPrice, ORANGE);                                                                                                 
//                        sprintf(buff, "Orange price is now: %dQ.\n\r", mutex_GetPriceVM(ORANGE));      
//                        fprintf2(C_UART2, buff);                                                        
//                    }
//                    else if(TaskTechnician_rx[0] == 'r' && TaskTechnician_rx[1] == 'p'){
//                        mutex_SetPriceVM(DrinkPrice, RED);                                                                                                             
//                        sprintf(PrintBuff, "Red price is now: %dQ.\n\r", mutex_GetPriceVM(RED));            
//                        fprintf2(C_UART2, buff);                                                            
//                    }
//                    
//                    else if(TaskTechnician_rx[0] == 'y' && TaskTechnician_rx[1] == 'y'){
//                        mutex_SetPriceVM(DrinkPrice, YELLOW);                                                                
//                        sprintf(PrintBuff, "Yellow price is now: %dQ.\n\r", mutex_GetPriceVM(RED));         
//                        fprintf2(C_UART2, buff);                                                       
//                    }
//                
//                    vTaskDelay(DELAY/ portTICK_RATE_MS); 
//                    state = SM_INIT;                                                                   
//                    break;
//                }

    
        }
    }        
}

void UItech(void){
    
    //fprintf2(C_LCD, "?Out of order-Temperature issue?");
    fprintf2(C_UART2, "Explorer 16/32 Vending Machine\n\r");
    fprintf2(C_UART2, "Enter r to refresh display \n\r");
    fprintf2(C_UART2, "Enter m followed by a 2 digits value between 00 and 99 to load MTNDEW bottles\n\r");
    fprintf2(C_UART2, "Enter k followed by a 2 digits value between 00 and 99 to load COKE bottles\n\r");
    fprintf2(C_UART2, "Enter c followed by a 2 digits value between 00 and 99 to load CRUSH bottles\n\r");
    fprintf2(C_UART2, "Enter i followed by a 2 digits value between 00 and 99 to load TEA bottles\n\r");
    fprintf2(C_UART2, "Enter t to read fridge temperature\n\r");
    fprintf2(C_UART2, "Enter e when the machine's money is removed\n\r");
    fprintf2(C_UART2, "Enter h to find out the last transaction time (in seconds)\n\r");
    fprintf2(C_UART2, "Enter m to read the amount of quarters currently in the machine\n\r");
    fprintf2(C_UART2, "Enter s to read the soda stock\n\r");
    fprintf2(C_UART2, "Enter p to change soda prices\n\r");
    fprintf2(C_UART2, "Enter k to check out from servicing\n\r");
    vTaskDelay(DELAY/ portTICK_RATE_MS);

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