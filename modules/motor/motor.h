//=====[#include guards - begin]===============================================

#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum {
    RUN,
    STOPPED
} motorDirection_t;

//=====[Declarations (prototypes) of public functions]=========================

void motorInit();
void motorStart();
void motorStop();
void motorUpdate();

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_