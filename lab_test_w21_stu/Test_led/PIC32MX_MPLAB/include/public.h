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

#define S3 PORTDbits.RD6 //S3
#define S4 PORTDbits.RD13 //S4
#define S6 PORTDbits.RD7 //S6



#define SEC_3 30000000
#define SEC_6 60000000
#define SEC_10 100000000
#define DELAY 110
//#define SIMULATION

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
int setItem(int itm, int qty);
void DisplayUI(void);
void initmutex(void);

//void itemInfo(int selec);
#endif /* PUBLIC_H */
