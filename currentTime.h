

typedef struct {
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t dayOfWeek;
} schedulerTime_t;


void syncTime();
schedulerTime_t getCurTime();
String getCurTimeStr();
