//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "crusher_system.h"
#include "motor.h"
#include "crusher.h"

//=====[Declaration of private defines]========================================

#define MOTOR_UPDATE_TIME 200

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut motorRelayPin(PF_2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

bool motorRunning;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void motorInit() {
  motorRelayPin = OFF;
  motorRunning = false;
}

void motorStart() { motorRunning = true; }

void motorStop() { motorRunning = false; }

void motorUpdate() {

    
  static int motorUpdateCounter = 0;

  motorUpdateCounter += SYSTEM_TIME_INCREMENT_MS;

  if (motorUpdateCounter >= MOTOR_UPDATE_TIME) {

    motorUpdateCounter = 0;

    if (motorRunning) {
      motorRelayPin = ON;
    } else {
      motorRelayPin = OFF;
    }
  }

  if (eStopState()) {
        motorRelayPin = OFF;
    }
}

//=====[Implementations of private functions]==================================
