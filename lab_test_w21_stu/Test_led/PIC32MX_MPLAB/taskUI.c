/* ***************************************************************************
 * File: taskUI.c
 * Description: to complete
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ezra-Fikru Asfaw                                 
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
#include "include/adc32.h"





static int totalCredit;
static char buff[100];
SemaphoreHandle_t xCredit; 
//xCredit = xSemaphoreCreateMutex(); 

item_t product;


/* Private static function declarations */
static void vTaskUI( void *pvParameters ){
    pvParameters = pvParameters ; // This is to get rid of annoying warnings
	/* As per most tasks, this task is implemented in an infinite loop. */

    
    static int lastTick, missCredit,qty,drink_no;
    static enum {SM_INIT,SM_BUTTON,SM_S3, SM_S4,SM_S6,SM_MTN,SM_COKE, SM_CRUSH, SM_TEA, SM_STATUS, SM_TEMP} state = SM_INIT;  
	for( ;; )
	{    
        
        totalCredit = getCredit();  
        switch(state){
          
////////////////////////////Initialization vending machine ////////////////////////
        case SM_INIT:
            

            #ifndef SIMULATION
                fprintf2(C_LCD, "                    \n                      ");
                fprintf2(C_LCD, "Select items\nPress S3++                      ");
            #endif   

    
            #ifdef SIMULATION
                fprintf2(C_UART1, "Select items\nPress S3++   ");
            #endif
            
            vTaskDelay(DELAY/ portTICK_RATE_MS);
            state = SM_BUTTON;
            break;

/////////////////////////Button Selection with Debouncing//////////////////////////
        case SM_BUTTON:
            

                drink_no = 0;
                if(!S3) state = SM_S3;
                else if(!S4) state = SM_S4;
                else state = SM_BUTTON;

            
            break;
               
///////////////////////////////Drink Selection/////////////////////////////////////
        case SM_S3:

            vTaskDelay(20/ portTICK_RATE_MS);
            if (drink_no<=3){
                
                
                
                if(drink_no == MTNDEW){
                    
                    state = SM_MTN;
                    lastTick= TickGet();
                    vTaskDelay(20/ portTICK_RATE_MS);
                    break;
                }
                
                
                if(drink_no == COKE){
                    
                    state = SM_COKE;
                    lastTick= TickGet();
                    vTaskDelay(DELAY/ portTICK_RATE_MS);
                    break;
                }
                else if(drink_no == CRUSH){
                    
                    state = SM_CRUSH;
                    lastTick= TickGet();
                    vTaskDelay(DELAY/ portTICK_RATE_MS);
                    break;
                }
                
                else if(drink_no == TEA){
                    
                    state = SM_TEA;
                    lastTick= TickGet();
                    vTaskDelay(DELAY/ portTICK_RATE_MS);
                    break;
                }
                else state = SM_INIT;
                
            }
            else{
                drink_no = 0;
                state = SM_INIT;
            }
            break;
 
///////////////////////////////////Adding Credit///////////////////////////////////
        case SM_S4:

            
            if (TickGet() - lastTick>= (SEC_6)){
                lastTick= TickGet();
                state = SM_INIT;
                break;
                    }        

            else{
            if((totalCredit < 10)&&(!S4)){
                vTaskDelay((DELAY)/ portTICK_RATE_MS);
                totalCredit++;
                setCredit(totalCredit);
                lastTick= TickGet();
                DisplayUI();
                vTaskDelay(DELAY/ portTICK_RATE_MS);
                
            }
            else if (totalCredit >= 10){
                
                #ifdef SIMULATION
                    fprintf2(C_UART1, "Max Credit\n");
                #endif

                #ifndef SIMULATION
                    fprintf2(C_LCD, "Max Credit                  \n             ");
                #endif
            
            }
            }

            if(!S3) state = SM_S3;
            else if (!S6) state = SM_S6;

            break;
            

///////////////////////////////////Vending/////////////////////////////////////////
        case SM_S6:
            vTaskDelay(20/ portTICK_RATE_MS);

      
            if(product.qty <= 0){
    
                #ifdef SIMULATION
                    fprintf2(C_UART1, "Sorry\nSold out\n");
                #endif

                #ifndef SIMULATION
                    fprintf2(C_LCD, "Sorry           \nSold out                     ");
                #endif
                    if (TickGet() - lastTick>= (SEC_6)){
                    lastTick= TickGet();
                    state = SM_INIT;
                    break;
                    }
            }
            
            
            else if(totalCredit >= product.price){
                totalCredit = totalCredit - product.price;
                setCredit(totalCredit);
                #ifdef SIMULATION
                    fprintf2(C_UART1, "Vending...\n");
                #endif

                #ifndef SIMULATION
                    fprintf2(C_LCD, "Vending...                  \n                  ");
                #endif
                
                vTaskDelay(2000/ portTICK_RATE_MS);
                vTaskDelay(20/ portTICK_RATE_MS);
                setItem( drink_no, --product.qty);
                SetTime(TickGet());
                vTaskDelay(DELAY/ portTICK_RATE_MS);

               // i = 0;
                state = SM_INIT;
            
                break;
            }
            
            else if(totalCredit < product.price){
                
                missCredit = product.price - totalCredit;
                vTaskDelay(20/ portTICK_RATE_MS);
                #ifdef SIMULATION
                    sprintf(buff, "Insuffi credits\nMissing %dQ",missCredit);
                    fprintf2(C_UART1, buff);
                #endif 
                
                #ifndef SIMULATION
                    sprintf(buff, "Insuffi credits            \nMissing %dQ      ",missCredit);
                    fprintf2(C_LCD, buff);
                #endif 
                
                
               
                
            }
            vTaskDelay(DELAY/ portTICK_RATE_MS);
            if(!S3) state = SM_S3;
            else if (!S4) state = SM_S4;
            
            break;
            

/////////////////////////////Drink Information/////////////////////////////////////
            case SM_MTN:
                    product= getItem(MTNDEW);
                    vTaskDelay(20/ portTICK_RATE_MS);
                    DisplayUI();
                    vTaskDelay(100/ portTICK_RATE_MS);
                    if (TickGet() - lastTick>= (SEC_3)){
                        
                        state = SM_INIT;
                        break;
                    }
                    
                    if (!S3){
                        drink_no++;
                        state = SM_COKE;
                        lastTick= TickGet();
                    }
                    else if(!S4) state = SM_S4;
                    else if (!S6) state = SM_S6;
                    else SM_MTN;
                    break;
   
                    
            case SM_COKE:
                    product= getItem(COKE);
                    vTaskDelay(20/ portTICK_RATE_MS);
                    DisplayUI();
                    vTaskDelay(100/ portTICK_RATE_MS);
                    if (TickGet() - lastTick>= (SEC_3)){
                       
                        state = SM_INIT;
                        break;
                    }
                    
                    if (!S3){
                        drink_no++;
                        state = SM_CRUSH;
                        lastTick= TickGet();
                    }
                    else if(!S4) state = SM_S4;
                    else if (!S6) state = SM_S6;
                    else state = SM_COKE;
                    break;
   
                    
            case SM_CRUSH:
                    product= getItem(CRUSH);
                    vTaskDelay(20/ portTICK_RATE_MS);
                    DisplayUI();
                    vTaskDelay(100/ portTICK_RATE_MS);
                    if (TickGet() - lastTick>= (SEC_3)){
                        
                        state = SM_INIT;
                        break;
                    }
                    if (!S3){
                        drink_no++;
                        state = SM_TEA;
                        lastTick= TickGet();
                    } 
                    else if(!S4) state = SM_S4;
                    else if (!S6) state = SM_S6;
                    else SM_CRUSH;
                    break;
       
                    
            case SM_TEA:
                    product= getItem(TEA);
                    vTaskDelay(20/ portTICK_RATE_MS);
                    DisplayUI();
                    vTaskDelay(100/ portTICK_RATE_MS);
                    if (TickGet() - lastTick>= (SEC_3)){
                        
                        state = SM_INIT;
                        break;
                    }
                    if (!S3){
                        drink_no=0;
                        state = SM_MTN;
                        lastTick= TickGet();
                    } 
                    else if(!S4) state = SM_S4;
                    else if (!S6) state = SM_S6;
                    else SM_TEA;
                    break;
///////////////////////////////////////////////////////////////////////////////////
            case SM_STATUS:
                if (getStatus()== 1){
                    fprintf2(C_LCD, "?Out of order\nTechnician in use?");
                }
                else{
                    state = SM_INIT;
                }
                break;
                
            case SM_TEMP:
                
                if (getTemp() <= 5 || getTemp() >=15){
                    fprintf2(C_LCD, "?Out of order\nTemperature Issue?");
                }
                else{
                    state = SM_INIT;
                }
        
                break;
        
    }
        if (getStatus() == 1 )state = SM_STATUS;
        else if (getTemp() <= 5 || getTemp() >=15) state = SM_TEMP;
    }
}

void DisplayUI(void){
                //vTaskDelay(DELAY/ portTICK_RATE_MS);
                #ifndef SIMULATION
                    sprintf(buff, "%s price:%dQ              \nCdt:%dQ Qty:%d ",product.name, product.price, totalCredit, product.qty);
                    fprintf2(C_LCD, buff);
                #endif   

    
                #ifdef SIMULATION
                    sprintf(buff, "%s price:%dQ              \nCdt:%dQ Qty:%d ",product.name, product.price, totalCredit, product.qty);
                    fprintf2(C_UART1, buff);
                #endif

}
/* Public function declarations */
void vStartTaskUI(void){
     xTaskCreate(	vTaskUI,						/* Pointer to the function that implements the task. */
					( char * ) "Task 1",	/* Text name for the task.  This is to facilitate debugging only. */
					240,						/* Stack depth in words. */
					NULL,						/* We are not using the task parameter. */
					1,							/* This task will run at priority 1. */
					NULL );						/* We are not using the task handle. */
}


