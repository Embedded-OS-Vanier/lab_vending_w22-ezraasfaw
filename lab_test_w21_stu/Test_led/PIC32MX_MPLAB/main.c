  
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
#include "include/initBoard.h" 
/* Hardware specific includes. */
#include "include/ConfigPerformance.h"
#include "include/console32.h"
#include "include/public.h"
#include "include/adc32.h"
#include <sys/attribs.h>     

#define DELAY_LOOP_COUNT 100000

int rstcnt __attribute__((persistent)); //survives WDTO,BOR,POR and EXTR
int ul;
/* Prototypes for the standard FreeRTOS callback/hook functions implemented within this file. */
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName );

char buffn[100];

int main( void )
{
    /* Prepares the hardware */
	prvSetupHardware();
	//INTCONbits.MVEC=1; 
    initADC();
    initmutex();
    vInitQueue();
#ifndef SIMULATION
    initIO();
    LCDInit();
#endif   


    initUart2_wInt();
    //initUart1();


    //vTaskDelay(10);
    
    //fprintf2(C_LCD, "Hi Uart1\n");
    
    
    int count = 10000;
    while(count--);

//    if(RCONbits.EXTR){
//        rstcnt= 0;
//        fprintf2(C_LCD,"\nPWR Reset");
//        RCONbits.EXTR=0;  
//        LATAbits.LATA0 ^= 1;       //LED D3
//    }
//    
//    else if(RCONbits.WDTO){ 
//        sprintf(buffn,"\nWTD reset %d",rstcnt++);
//        fprintf2(C_LCD,buffn);
//        RCONbits.WDTO=0;
//        LATAbits.LATA1 ^= 1;       //LED D4
//        if (rstcnt> 6){
//            fprintf2(C_LCD,"\nBoard frozen");
//            while(1){
//                WDTCONbits.WDTCLR=1;
//                LATAbits.LATA2 ^= 1;       //LED D4
//            }
//        }
//    }
    /* create tasks here */
    
    vStartTaskUI();
    vStartTaskTech();
    vStartTaskTemp();
    vTaskStartScheduler();
	return 0;
}
/*-----------------------------------------------------------*/


void vApplicationIdleHook( void ){
    while(1){
        LATA^=1;
        for( ul= 0; ul< DELAY_LOOP_COUNT; ul++ );
//        WDTCONbits.WDTCLR=1;
    }
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
    pxTask= pxTask;
    pcTaskName = pcTaskName;

    for( ;; );
}

