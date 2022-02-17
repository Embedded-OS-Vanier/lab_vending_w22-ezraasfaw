  
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

/* */
void __ISR( _UART_2_VECTOR, IPL1SOFT) U2RXInterrupt( void){
    char cChar;
    
	IFS1bits.U2RXIF=0;
	while( U2STAbits.URXDA )
	{
		cChar = U2RXREG;

	}
}
 