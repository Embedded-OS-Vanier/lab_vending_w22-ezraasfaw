
/* ***************************************************************************
 * File: vTask2.c
 * Description: to complete
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date      		Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                                  print
 *****************************************************************************/
#include <string.h>
#include <stdio.h>
/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "include/public.h"
#include "include/console32.h"

//void printItem( struct item *ver );
/* Private static function declarations */
static void vTask2( void *pvParameters )
{

   pvParameters = pvParameters ;    // This is to get rid of annoying warnings
   //while(1);
   	for( ;; )
	{   
        

}

    }


/* Public function declarations */
void vStartTask2(void){
      xTaskCreate( vTask2, ( char * ) "Task 2", 240, NULL, 1, NULL );
}

//void printItem( struct item *ver ) {
//            printf( "Book title : %s\n", item->name);
//            printf( "Book author : %s\n", item->price);




