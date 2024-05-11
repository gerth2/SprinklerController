
#ifndef COMMAND_STATE_MACHINE_H_
#define COMMAND_STATE_MACHINE_H_

#define STATE_MANUAL 0
#define STATE_AUTO 1


void csm_setCmdState(uint8_t cmd);
void csm_requestManualZone(uint8_t zone);
void csm_requestAllOff(void);

uint8_t csm_getCurState();

// Periodic calls
void csm_init();
void csm_update();

#endif