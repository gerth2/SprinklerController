#ifndef RAIN_SENSOR_H_
#define RAIN_SENSOR_H_

void rs_init();
void rs_update();

boolean rs_isInhibited();

boolean rs_isSensorWet();

#endif