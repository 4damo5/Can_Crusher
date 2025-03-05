//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "user_interface.h"

#include "crusher_system.h"
#include "crusher.h"
#include "motion_sensor.h"
#include "motor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

typedef enum {
    NOT_READY,
    READY,
    BUSY
} crusherState_t;

//=====[Declaration and initialization of public global objects]===============

// define start / estop here
//define lim switch here

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

int canCount;
crusherState_t crusherState;

//=====[Declarations (prototypes) of private functions]========================

void crusherStateUpdate();

//=====[Implementations of public functions]===================================

void crusherInit() {
    motorInit();
    motionSensorInit();

    crusherState = NOT_READY;
    canCount = 0;
}

void crusherUpdate() {
    motorUpdate();
    motionSensorDetect();
    crusherStateUpdate();
}

int crusherRead() {
    return canCount;
}

//=====[Implementations of private functions]==================================

void crusherStateUpdate() {
    switch(crusherState) {
        case NOT_READY:
        //stop motor 
        //if can detected
        //go to ready
        break;
        case READY:
        //stop motor
        //if can is not detected 
        //go to not ready

        //if start button is pressed && can is still detected
        //go to busy

        break;

        case BUSY:
        //if lim switch is pressed
        //go to ready or not ready depending on if can is detected

        //if estop is pressed
        //stop the the motor and go into an infinite loop interrupt

        //else 
        //keep turning motor

        break;

        default:
        break;
    }
}