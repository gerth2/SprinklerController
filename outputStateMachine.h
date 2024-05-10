
#ifndef OUTPUT_STATE_MACHINE_H_
#define OUTPUT_STATE_MACHINE_H_

typedef struct {
    bool zoneCommands[7];
    bool boostPumpCommand;
} osm_commands_t;


// Input commands
void osm_setActiveZone(uint8_t zone_number);
void osm_setAllOff(void);

// Output
osm_commands_t osm_getOutputCmds(void);


// Periodic calls
void osm_init();
void osm_update();

#endif