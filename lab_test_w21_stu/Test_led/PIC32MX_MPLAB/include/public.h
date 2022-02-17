/* ***************************************************************************
 * File: public.h
 * Description: contains public prototypes and shared macros
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  - v1
 *****************************************************************************/

#ifndef PUBLIC_H
#define PUBLIC_H


//#define     CONSOLE     C_LCD
#define     CONSOLE     C_UART1
#define     MTNDEW      0
#define     COKE        1
#define     CRUSH       2
#define     TEA         3 
#define     MAX_ITEM    4


void vStartTask1(void);
void vStartTask2(void);
void itemInfo(int selec);
#endif /* PUBLIC_H */