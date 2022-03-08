  
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
    
    
#ifndef SIMULATION
    initIO();
    LCDInit();
#endif   

    
#ifdef SIMULATION
    initUart1();
    initUart2_wInt();
#endif
    
    
    //fprintf2(C_LCD, "Hi Uart1\n");
    
    /* create tasks here */
    
    vStartTask1();
    
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

