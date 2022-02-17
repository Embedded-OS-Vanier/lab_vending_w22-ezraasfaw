/***********************************************************************************************
*
*
* FileName:  initBoard.c      
*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Author        	Date      			Comments on this revision
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Serge Hould      20 Jan. 2020		v1.0.0
* Serge Hould      5 May 2020		v1.0.1 replaces T2 by T4
* 
*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include "include/initBoard.h"
#include "include/public.h"

 // Configuration Bit settings
// SYSCLK = 80 MHz 
//(8MHz Crystal/ FPLLIDIV * FPLLMUL / FPLLODIV)
// PBCLK = 80 MHz
// Primary Osc w/PLL (HS+PLL)
// WDT OFF, Peripheral Bus is CPU clock÷8
// Other options are default as per datasheet
// see file:///C:/Program%20Files/Microchip/xc32/v2.41/docs/config_docs/32mx795f512l.html
 
#pragma config FPLLMUL = MUL_20
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLODIV = DIV_1 
#pragma config POSCMOD = HS, FNOSC = PRIPLL
#pragma config FPBDIV = DIV_1  // PBCLK = SYSCLK/DIV_1
#pragma config FWDTEN =  OFF    // disable

void initIO(void)
{
    DDPCONbits.JTAGEN = 0; // JTAG shared with RA5, RA4, RA1 and RA0
    /* LEDs */
    TRISAbits.TRISA7 = 0;       //LED D10
    TRISAbits.TRISA5 = 0;       //LED D8
    TRISAbits.TRISA4 = 0;       //LED D7
    TRISAbits.TRISA3 = 0;       //LED D6
    TRISAbits.TRISA2 = 0;       //LED D5
    TRISAbits.TRISA1 = 0;       //LED D4
    TRISAbits.TRISA0 = 0;       //LED D3
    
   
    TRISDbits.TRISD6 =1; //S3
    TRISDbits.TRISD7 =1;//S6
    TRISDbits.TRISD13 =1;//S4
    TRISAbits.TRISA6 =1; //S5 - shared with LED D9
	
    /* Turns off all LEDs*/
     LATA = LATA & 0xffff0000;
  
}

void prvSetupHardware( void )
{
	/* Configure the hardware for maximum performance. */
	vHardwareConfigurePerformance();

	/* Setup to use the external interrupt controller. */
	vHardwareUseMultiVectoredInterrupts();

	portDISABLE_INTERRUPTS();

}
