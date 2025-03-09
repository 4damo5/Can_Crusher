//=====[#include guards - begin]===============================================

#ifndef _CRUSHER_H_
#define _CRUSHER_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum { NOT_READY, READY, BUSY } crusherState_t;

//=====[Declarations (prototypes) of public functions]=========================

void crusherInit();
void crusherUpdate();
int crusherRead();
bool eStopState();
crusherState_t crusherStateRead();

//=====[#include guards - end]=================================================

#endif // _CRUSHER_H_