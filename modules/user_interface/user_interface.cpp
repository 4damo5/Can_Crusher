//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"
#include "display.h"
#include "crusher.h"
#include "crusher_system.h"

//=====[Declaration of private defines]========================================

#define DISPLAY_REFRESH_TIME_MS 100

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

static void userInterfaceInit()
{
    displayInit();

    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "CRUSHER:" );

    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "CANS CRUSHED:" );
}

static void userInterfaceUpdate()
{
    static int accumulatedDisplayTime = 0;
    char cansCrushed[3] = "";
    
    if( accumulatedDisplayTime >=
        DISPLAY_REFRESH_TIME_MS ) {

        accumulatedDisplayTime = 0;

        switch(crusherStateRead()) {
            case (NOT_READY):
            displayCharPositionWrite(9,0);
            displayStringWrite("NOT READY");
            break;
            
            case (READY):
            displayCharPositionWrite(9,0);
            displayStringWrite("READY      ");
            break;

            case (BUSY):
            displayCharPositionWrite(9,0);
            displayStringWrite("BUSY       ");
            break;

            default:
            break;
        }

        if (eStopState()) {
            displayCharPositionWrite(0,0);
            displayStringWrite("EMERGENCY STOP   ");
            
        }

        sprintf(cansCrushed, "%d", crusherRead());
        displayCharPositionWrite ( 14,1 );
        displayStringWrite( cansCrushed );
        

    } else {
        accumulatedDisplayTime =
            accumulatedDisplayTime + SYSTEM_TIME_INCREMENT_MS;        
    } 
}