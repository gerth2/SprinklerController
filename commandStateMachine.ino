#include "commandStateMachine.h"

void csm_setCmdState(uint8_t cmd){
    Serial.printf("Got State %d\n", cmd); //todo actually something useful
}

void csm_requestManualZone(uint8_t zone){
 //TODO
}

void csm_requestAllOff(void){
 //TODO
}


// Periodic calls
void csm_init(){
    //TODO
}

void csm_update(){
    //TODO
}
