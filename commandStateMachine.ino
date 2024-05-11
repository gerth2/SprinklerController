#include "commandStateMachine.h"
#include "outputStateMachine.h"

uint8_t curStateCmd;
uint8_t curState;

void csm_setCmdState(uint8_t cmd){
    Serial.printf("Got State Cmd %d\n", cmd); //todo actually something useful
    curStateCmd = cmd;
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
    curState = curStateCmd;
}

uint8_t csm_getCurState(){
    return curState;
}