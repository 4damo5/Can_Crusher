//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"
#include "crusher.h"
#include "crusher_system.h"

//=====[Declaration of private defines]========================================

#define CRUSHER_DELAY_TIME 200

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void crusherSystemInit() {
    crusherInit();
    userInterfaceInit();
}

void crusherSystemUpdate() {
    static int crusherUpdateCounter = 0;

    if(crusherUpdateCounter == CRUSHER_DELAY_TIME) {
    crusherUpdateCounter = 0;
    
    crusherUpdate();
    userInterfaceUpdate();
    }
    else {
        crusherUpdateCounter += SYSTEM_TIME_INCREMENT_MS;
    }

}

//=====[Implementations of private functions]==================================
