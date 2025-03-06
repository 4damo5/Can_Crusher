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
bool eStopTriggered = false;

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

bool eStopState() {
    return eStopTriggered;
}

//=====[Implementations of private functions]==================================

void crusherStateUpdate() {
    if (eStopTriggered) {
        while(true) {}
    }

    switch(crusherState) {
        case NOT_READY:
        stopMotor();

        if (motionSensorRead()) {
            crusherState = READY;
        } 
        break;
        case READY:
        stopMotor();

        if (!motionSensorRead()) {
            crusherState = NOT_READY;
        }

        if (startButton) {
            crusherState = BUSY;
        }
        break;

        case BUSY:
        motorStart();

        if (limSwitch) {
            if (motionSensorRead()) {
                crusherState = READY;
            }
            else {
                crusherState = NOT_READY;
            }
        }

        if (eStop) {
            stopMotor();
            eStopTriggered = true;
        }
        break;

        default:
        break;
    }
}