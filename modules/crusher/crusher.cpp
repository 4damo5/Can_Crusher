//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "user_interface.h"

#include "crusher.h"
#include "motion_sensor.h"
#include "motor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn startButton(D14);
DigitalIn eStop(D13);
DigitalIn limSwitch(D12);

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
    startButton.mode(PullDown);
  eStop.mode(PullDown);
  limSwitch.mode(PullDown);

  motorInit();
  motionSensorInit();
  

  crusherState = NOT_READY;
  canCount = 0;
}

void crusherUpdate() {
  
  motionSensorUpdate();
  crusherStateUpdate();
  motorUpdate();
}

int crusherRead() { return canCount; }

crusherState_t crusherStateRead() { return crusherState; }

bool eStopState() { return eStopTriggered; }

//=====[Implementations of private functions]==================================

void crusherStateUpdate() {
  switch (crusherState) {
  case NOT_READY:
    motorStop();

    if (motionSensorRead()) {
      crusherState = READY;
    }
    break;
  case READY:
    motorStop();

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
        canCount++;
      if (motionSensorRead()) {
        crusherState = READY;
      } else {
        crusherState = NOT_READY;
      }
    }
    break;

  default:
    break;
  }
  if (eStop) {
      motorStop();
      eStopTriggered = true;
    }
}
