/**
  
*/

#ifndef INITBOARD_H
#define INITBOARD_H
/**
    Section: Includes
*/
#include <stdint.h>
#include <xc.h>
#include "FreeRTOS.h"
/* Hardware specific includes. */
#include "ConfigPerformance.h"
/**
    Section: Macros
*/
//macros definitions
/**
    Section: Function Prototypes
*/
void initIO(void);
void prvSetupHardware( void );



#endif
