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

bool motorRunning;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motorInit() {
    motorM1Pin.mode(OpenDrain);
    motorM2Pin.mode(OpenDrain);
    
    motorM1Pin.input();
    motorM2Pin.input();

    motorRunning = false;
}

void motorStart() {
    motorRunning = true;
}

void motorStop() {
    motorRunning = false;
}

void motorUpdate()
{
    static int motorUpdateCounter = 0;
    
    motorUpdateCounter += SYSTEM_TIME_INCREMENT_MS;
    
    if ( motorUpdateCounter > MOTOR_UPDATE_TIME ) {
        
        motorUpdateCounter = 0;
        
        if ( motorRunning ) {
                    motorM1Pin.input();
                    motorM2Pin.input();
                    motorRunning = false;
        }
         else {
                    motorM2Pin.input();
                    motorM1Pin.output();
                    motorM1Pin = LOW;
                    motorRunning = true;
                           }        
}
}

//=====[Implementations of private functions]==================================

