  
/* ISR receiver
 *		
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      			Comments on this revision		
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould      20 Jan. 2020		v1.0.0
 *
 **********************************************************************/

#include "FreeRTOS.h"
#include "queue.h"
#include "semphr.h"
#include "include/console32.h"
#include "include/public.h"
#include <sys/attribs.h>     

/*Semaphores and mutexes declarations*/


/* */
void __ISR( _UART_2_VECTOR, IPL1SOFT) U2RXInterrupt( void){
    char cChar;
    
	IFS1bits.U2RXIF=0;
    
	while( U2STAbits.URXDA )
	{
		cChar = U2RXREG;
        vSendQueueFromISR(cChar);
	}
}
 

//static void ISRHandler(){
//    while(1){
//        char rx;
//        // Blocks on the semaphore
//        xQueueReceive(xQueue,&rx, portMAX_DELAY ); 
//        _LATA0 ^= 1;// Toggles a LED
//        return rx;
//    }
//}


//void _ISR_T2Interrupt(void){
//    IFS0bits.T2IF = 0; // Clear Timer2 Interrupt
//        
//} 

