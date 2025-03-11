//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "motion_sensor.h"
#include "crusher_system.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

#define TRIGGER_UPDATE_TIME 20

//=====[Declaration and initialization of public global objects]===============

AnalogIn lightReader(A1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool motionDetected;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motionSensorInit() {
  motionDetected = false;
}

void motionSensorUpdate() { 
    float lightReading = lightReader.read();
    if (lightReading < .8) {
        motionDetected = false;
    }
    else {
        motionDetected = true;
    }
  }

bool  motionSensorRead() {
    return motionDetected;
}

//=====[Implementations of private functions]==================================