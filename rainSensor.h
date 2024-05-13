#ifndef RAIN_SENSOR_H_
#define RAIN_SENSOR_H_

void rs_init(void);
void rs_update(void);

boolean rs_isInhibited(void);

boolean rs_isSensorWet(void);

#endif