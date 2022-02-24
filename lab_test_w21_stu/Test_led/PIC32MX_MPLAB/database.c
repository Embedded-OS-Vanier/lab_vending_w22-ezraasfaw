  
/* ***************************************************************************
 * File: main.c
 * Description: 
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *        
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
#include <string.h>


#define MAX_ITEM 4


  
typedef struct item {
    char name[100];
    int qty;
    int price;
    int tag;
} item_t;


item_t item[MAX_ITEM]={
    {"Mountain Dew",2,5,MTNDEW},
    {"Coke",2,5,COKE},
    {"Crush",2,5,CRUSH},
    {"Nestea",2,5,TEA}
};


WHAT IS THE PURPOSE OF THIS FUNCTION?
void itemInfo(int selec){
struct item MtnDew;
struct item Coke;
struct item Crush;
struct item Nestea;

if (selec == 0){
/*MountainDew*/
strcpy( MtnDew.name, "Mountain Dew");
MtnDew.price = 5;
MtnDew.qty = 2;
}

if (selec == 1){
/*Cocacola*/
strcpy( MtnDew.name, "CocaCola");
Coke.price = 5;
Coke.qty = 2;
}

if (selec == 2){
/*Crush*/
strcpy( MtnDew.name, "Crush");
Crush.price = 5;
Crush.qty = 2;
}

if (selec == 3){
/*Nestea*/
strcpy( MtnDew.name, "Nestea");
Nestea.price = 5;
Nestea.qty = 2;
}
return;
}
