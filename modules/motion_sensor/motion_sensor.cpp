//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "motion_sensor.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

#define TRIGGER_UPDATE_TIME 10

//=====[Declaration and initialization of public global objects]===============

DigitalOut trig(D7);
InterruptIn echo(D6);
Ticker timer;

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

bool motionDetected;
int pulseLength;
int timerStop;

//=====[Declarations (prototypes) of private functions]========================

static void triggerPulse();
static void echoRise();
static void echoFall();
static void tickerCallback();

//=====[Implementations of public functions]===================================

void motionSensorInit() {
  echo.rise(&echoRise);
  echo.fall(&echoFall);
  timer.attach(&tickerCallback, .001);

  motionDetected = false;
}

void motionSensorDetect() { triggerPulse(); }

bool motionSensorRead() { return motionDetected; }

//=====[Implementations of private functions]==================================

static void triggerPulse() {
  static int triggerUpdateCounter = 0;
  triggerUpdateCounter++;

  trig = 1;

  if (triggerUpdateCounter > TRIGGER_UPDATE_TIME) {
    trig = 0;

    triggerUpdateCounter = 0;
  }
}

static void echoRise() { pulseLength = 0; }

static void echoFall() {
  timerStop = pulseLength;

  if (timerStop < 20) {
    motionDetected = true;
  } else {
    motionDetected = false;
  }
}

static void tickerCallback() { pulseLength++; }
