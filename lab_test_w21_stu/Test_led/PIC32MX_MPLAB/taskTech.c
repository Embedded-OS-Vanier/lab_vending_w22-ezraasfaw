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
   
    static enum { SM_MENU,SM_INIT,SM_INPUT_SEPERATION, SM_BUTTON, SM_REFRESH, SM_MTNDEW_LOAD, SM_COKE_LOAD, SM_CRUSH_LOAD, SM_TEA_LOAD,SM_TEMPERATURE, SM_RETRIEVE_MONEY, SM_LAST_TRANS,SM_READ_Q, SM_STOCK,SM_PRICE, SM_EXIT} state = SM_MENU;  
    

    //UItech();
    while(1){
        vTaskDelay(10);
        switch(state){
            case SM_MENU:
                UItech();
                state = SM_INIT;
                break;
    ////////////////////////////Initialization vending machine ////////////////////////
            case SM_INIT:
//                if (flag == 0){
                xQueueReceive(xQueue,&rx, portMAX_DELAY );  
                sprintf(buff, "%c",rx);
                fprintf2(C_UART2, buff);

                setStatus(1); //on
                
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
            
                
                
                mode = rec[0];
                sprintf(buffn,"%c%c",rec[1],rec[2]);
                digit = atoi(buffn);
                if (flag == 0){
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
                }
                else {
                    state = SM_PRICE;
                }
            
            
                break;
            
/////////////////////////////////refresh display///////////////////////////////////           
            case SM_REFRESH:
                state = SM_MENU;
                break;
          
/////////////////////////////////load MTNDEW drink/////////////////////////////////
            case SM_MTNDEW_LOAD:
                setItem(MTNDEW,digit);
                product= getItem(MTNDEW);
                sprintf(buff, "MTNDEW stock updated\n\rMTNDEW in stock is now:%d \n\r\n\r", product.qty);
                fprintf2(C_UART2, buff);
                state = SM_MENU;
                break;
            
//////////////////////////////////load COKE drink//////////////////////////////////
            case SM_COKE_LOAD:
                setItem(COKE,digit);
                product= getItem(COKE);
                sprintf(buff, "COKE stock updated\n\rCOKE in stock is now:%d \n\r\n\r", product.qty);
                fprintf2(C_UART2, buff);
                state = SM_MENU;
                break;
            
/////////////////////////////////load CRUSH drink//////////////////////////////////
            case SM_CRUSH_LOAD:
                setItem(CRUSH,digit);
                product= getItem(CRUSH);
                sprintf(buff, "CRUSH stock updated\n\rCRUSH in stock is now:%d \n\r\n\r", product.qty);
                fprintf2(C_UART2, buff);
                state = SM_MENU;
                break;
            
//////////////////////////////////load TEA drink///////////////////////////////////
            case SM_TEA_LOAD:
                setItem(TEA,digit);
                product= getItem(TEA);
                sprintf(buff, "TEA stock updated\n\rTEA in stock is now:%d \n\r\n\r", product.qty);
                fprintf2(C_UART2, buff);
                state = SM_MENU;
                break;
                
                
/////////////////////////////////Retrieve Money/////////////////////////////////////
            case SM_RETRIEVE_MONEY:
                //credit = getCredit();
                setCredit(0);
                fprintf2(C_UART2, "Retrieve credit\n\rCredit total is now 0Q\n\r\n\r");
                state = SM_MENU;
                break;
              
/////////////////////////////////Retrieve Money/////////////////////////////////////
            case SM_LAST_TRANS:                                                                       
                sprintf(buff, "Last transaction happened %d seconds ago\n\r\n\r", getTime());  
                fprintf2(C_UART2, buff);
                state = SM_MENU;
                break;
                
/////////////////////////////////////////////////////////////////////////////////
            case SM_TEMPERATURE:
                sprintf(buff, "Fridge temperature is  %d  degree\n\r\n\r", getTemp()); 
                fprintf2(C_UART2, buff);
                state = SM_MENU;                                                                         
                break;
                
 /////////////////////////////////////////////////////////////////////////////////
            case SM_READ_Q:
                sprintf(buff, "%d Q in the Vending Machine\n\r\n\r", getCredit());   
                fprintf2(C_UART2, buff);
                state = SM_MENU;                                                                   
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
                
                state = SM_MENU;                                                                   
                break;
                
  /////////////////////////////////////////////////////////////////////////////////
            case SM_PRICE:
                if(flag == 0){   
                    subUItech();
                    flag = 1;
                    state = SM_INIT;
                    break;
                }
                else{
                    
                    //sprintf(buffn, "%c%c", rx[2], rx[3]);               
                    //DrinkPrice = atoi(temp_buffer);                                                         
                    
                    if(mode == 'v'){
                        setPrice(MTNDEW, digit);                                                                                               
                        sprintf(buff, "MTNDEW price is now: %dQ.\n\r\n\r", getPrice(MTNDEW));      
                        fprintf2(C_UART2, buff);                                                        
                    }
                    else if(mode == 'z'){
                        setPrice(COKE, digit);                                                                                                             
                        sprintf(buff, "COKE price is now: %dQ.\n\r\n\r", getPrice(COKE));            
                        fprintf2(C_UART2, buff);                                                            
                    }
                    
                    else if(mode == 'l' ){
                        setPrice(CRUSH, digit);                                                                 
                        sprintf(buff, "CRUSH price is now: %dQ.\n\r\n\r", getPrice(CRUSH));         
                        fprintf2(C_UART2, buff);                                                       
                    }
                    else if(mode == 'y' ){
                        setPrice(TEA, digit);                                                              
                        sprintf(buff, "TEA price is now: %dQ.\n\r\n\r", getPrice(TEA));         
                        fprintf2(C_UART2, buff);                                                       
                    }
                    
                
                    flag=0;
                    state = SM_MENU;                                                                   
                    break;
                }
                
                case SM_EXIT:
                    setStatus(0);
                    state = SM_MENU;
                    break;
                

    
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
    fprintf2(C_UART2, "Enter q to read the amount of quarters currently in the machine\n\r");
    fprintf2(C_UART2, "Enter s to read the soda stock\n\r");
    fprintf2(C_UART2, "Enter p to change soda prices\n\r");
    fprintf2(C_UART2, "Enter x to check out from servicing\n\r\n\r");
    vTaskDelay(DELAY/ portTICK_RATE_MS);

}

void subUItech(void){
    
    //fprintf2(C_LCD, "?Out of order-Temperature issue?");
    fprintf2(C_UART2, "Explorer 16/32 Vending Machine\n\r");
    fprintf2(C_UART2, "Enter r to refresh display \n\r");
    fprintf2(C_UART2, "Enter v followed by a 2 digits value between 00 and 99 to change MTNDEW price\n\r");
    fprintf2(C_UART2, "Enter z followed by a 2 digits value between 00 and 99 to change COKE price\n\r");
    fprintf2(C_UART2, "Enter l followed by a 2 digits value between 00 and 99 to change CRUSH price\n\r");
    fprintf2(C_UART2, "Enter y followed by a 2 digits value between 00 and 99 to change TEA price\n\r");
    fprintf2(C_UART2, "Enter x to check out from servicing\n\r\n\r");
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