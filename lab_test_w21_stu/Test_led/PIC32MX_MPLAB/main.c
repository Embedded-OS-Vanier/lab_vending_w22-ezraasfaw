  
/* ***************************************************************************
 * File: main.c
 * Description: 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author               Date           Version      Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Ezra-Fikru Asfaw     2/17/2022         1.0       Worked on vTask1 by adding case statement for each button. Was trying to figure out the logic behind each button.
 *                                                  Worked on database by adding structures for each item in the vending machine. I was also trying to figure out how 
 *                                                  to select specific item from the structure.
 *                            
 * Ezra-Fikru Asfaw     2/24/2022         2.0       Worked on database.c and public.h by modifing it so that there is no error displaying.
 *                                                  Worked on vtask1.c to figure out the logic for the case statement for the button inputs.
 * 
 * Ezra-Fikru Asfaw     3/3/2022          3.0 
 *
 * Ezra-Fikru Asfaw     3/10/2022         4.0 
 *  
 * Ezra-Fikru Asfaw     3/24/2022         5.0      Worked on taskTech.c. I was able to send an input from the consol to a 
 *                                                 queue which was able to print on UART1
 * 
 * Ezra-Fikru Asfaw     3/31/2022         6.0      Worked on taskTech.c. I was able to send an input from the consol to a 
 *                                                 queue which was able to print on UART1
 * Ezra-Fikru Asfaw     3/24/2022         7.0      Worked on taskTech.c. I was able to split the input into a character and 2 digit input. Then, use it to 
 *                                                 perform some functionality such as loading drink mad retrieving credit.
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



/* Prototypes for the standard FreeRTOS callback/hook functions implemented within this file. */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );

int main( void )
{
    /* Prepares the hardware */
	prvSetupHardware();
	//INTCONbits.MVEC=1; 
    initmutex();
    vInitQueue();
#ifndef SIMULATION
    initIO();
    LCDInit();
#endif   

    
#ifdef SIMULATION
    initUart2_wInt();
    initUart1();
    //initUart2_wInt();
#endif
    
//    fprintf2(C_LCD, "?Out of order-Temperature issue?");
//    fprintf2(C_UART1, "Explorer 16/32 Vending Machine\n");
//    fprintf2(C_UART1, "Enter r to refresh display \n");
//    fprintf2(C_UART1, "Enter o followed by a 2 digits value between 00 and 99 to load orange bottles\n");
//    fprintf2(C_UART1, "Enter c followed by a 2 digits value between 00 and 99 to load cherry bottles\n");
//    fprintf2(C_UART1, "Enter l followed by a 2 digits value between 00 and 99 to load lemon bottles\n");
//    fprintf2(C_UART1, "Enter t to read fridge temperature\n");
//    fprintf2(C_UART1, "Enter e when the machine's money is removed\n");
//    fprintf2(C_UART1, "Enter h to find out the last transaction time (in seconds)\n");
//    fprintf2(C_UART1, "Enter m to read the amount of quarters currently in the machine\n");
//    fprintf2(C_UART1, "Enter s to read the soda stock\n");
//    fprintf2(C_UART1, "Enter p to change soda prices\n");
//    fprintf2(C_UART1, "Enter k to check out from servicing\n");
    //vTaskDelay(10);
    
    //fprintf2(C_LCD, "Hi Uart1\n");
    
    /* create tasks here */
    
    //vStartTaskUI();
    vStartTaskTech();
    vTaskStartScheduler();
	return 0;
}
/*-----------------------------------------------------------*/


void vApplicationIdleHook( void ){
    while(1){
        LATA^=1;
    }
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    pxTask= pxTask;
    pcTaskName = pcTaskName;

    for( ;; );
}

