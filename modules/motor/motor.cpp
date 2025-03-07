//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "motor.h"
#include "crusher_system.h"

//=====[Declaration of private defines]========================================

#define MOTOR_UPDATE_TIME 900

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalInOut motorM1Pin(PF_2);
DigitalInOut motorM2Pin(PE_3);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

motorDirection_t motorDirection;
motorDirection_t motorState;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motorInit() {
    motorM1Pin.mode(OpenDrain);
    motorM2Pin.mode(OpenDrain);
    
    motorM1Pin.input();
    motorM2Pin.input();

    motorDirection = STOPPED;
    motorState = STOPPED;
}

void motorStart() {
    motorState = RUN;
}

void motorStop() {
    motorState = STOPPED;
}

void motorUpdate()
{
    static int motorUpdateCounter = 0;
    
    motorUpdateCounter += SYSTEM_TIME_INCREMENT_MS;
    
    if ( motorUpdateCounter > MOTOR_UPDATE_TIME ) {
        
        motorUpdateCounter = 0;
        
        switch ( motorState ) {
            case RUN:
                if (motorDirection == STOPPED ) {
                    motorM1Pin.input();
                    motorM2Pin.input();
                    motorState = STOPPED;
                }
            break;
            case STOPPED:
            default:
                if ( motorDirection == RUN ) {
                    motorM2Pin.input();
                    motorM1Pin.output();
                    motorM1Pin = LOW;
                    motorState = RUN;
                }
            break;
        }
    }        
}

//=====[Implementations of private functions]==================================

