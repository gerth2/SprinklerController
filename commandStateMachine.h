
#ifndef COMMAND_STATE_MACHINE_H_
#define COMMAND_STATE_MACHINE_H_

#define STATE_OFF 0
#define STATE_MANUAL 1
#define STATE_AUTO 2


void csm_setCmdState(uint8_t cmd);
void csm_requestManualZone(uint8_t zone);
void csm_requestAllOff(void);

// Periodic calls
void csm_init();
void csm_update();

#endif