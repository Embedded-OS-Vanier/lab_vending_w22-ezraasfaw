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
#define     MTNDEW      1
#define     COKE        2
#define     CRUSH       3
#define     TEA         4 
#define     MAX_ITEM    4

#define S3 PORTDbits.RD6 //S3
#define S4 PORTDbits.RD7 //S4
#define S6 PORTDbits.RD13 //S6


#define BTN1WAIT 10
#define BTN2WAIT 2000

#define SIMULATION

typedef struct product {
    char name[100];
    int qty;
    int price;
    int tag;
} item_t;

void vStartTask1(void);
void vStartTask2(void);
int getCredit(void);
int setCredit(int s);
item_t getItem(int i);
int setItem(int _itm);
void initmutex(void);

//void itemInfo(int selec);
#endif /* PUBLIC_H */