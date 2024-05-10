#include <HTTPClient.h>
#include "currentTime.h"

String location = "America/Chicago"; 

int syncHour = -1;
int syncMinute = -1;
int syncSecond = -1;
int syncDayOfWeek = -1;
unsigned long syncMillis = 0;


void syncTime(){

  // Fetch current local time for the location from worldtimeapi.org
  String url = "http://worldtimeapi.org/api/timezone/" + location;

  HTTPClient http;
  http.begin(url);

  int httpCode = http.GET();
  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      syncMillis = millis();
      String payload = http.getString();

      // Extract local time from JSON response (assumes response is in JSON format)
      int startIndex = payload.indexOf("datetime\":\"") + 11;
      int endIndex = payload.indexOf("\"", startIndex);
      String localTime = payload.substring(startIndex, endIndex);
      Serial.print("[TIME SYNC] Current local time for ");
      Serial.print(location);
      Serial.print(": ");
      Serial.println(localTime);

      // Extract hour
      int indexT = localTime.indexOf('T');
      String timePart = localTime.substring(indexT + 1); // Extracting time part after 'T'
      syncHour = timePart.substring(0, 2).toInt();

      // Extract minute
      syncMinute = timePart.substring(3, 5).toInt();

      // Extract second
      syncSecond = timePart.substring(6, 8).toInt();

      // Extract day-of-week
      int index = payload.indexOf("day_of_week\":");
      String dayOfWeekStr = payload.substring(index + 13, index + 14);

      // Convert the substring to an integer
      syncDayOfWeek = dayOfWeekStr.toInt();

    } else {
      Serial.printf("HTTP request failed with error code %d\n", httpCode);
    }
  } else {
    Serial.println("Failed to connect to server");
  }

  http.end();

}

schedulerTime_t getCurTime(){

  schedulerTime_t retVal;

  // Calculate elapsed time since the sync request
  unsigned long currentMillis = millis();
  unsigned long elapsedMillis = currentMillis - syncMillis;
  unsigned long elapsedSeconds = elapsedMillis / 1000;

  // Add elapsed time to sync time
  unsigned long totalSeconds = syncSecond + elapsedSeconds;
  retVal.second    = totalSeconds % 60;
  int totalMinutes = (syncMinute + (totalSeconds / 60));
  retVal.minute    = totalMinutes % 60;
  int totalHours   = (syncHour + (totalMinutes / 60));
  retVal.hour      = totalHours % 24;
  retVal.dayOfWeek = (syncDayOfWeek + (totalHours / 24)) % 7;

  return retVal;

}

String getCurTimeStr(){
  schedulerTime_t curTime = getCurTime();

    std::string period = "AM";
    if (curTime.hour >= 12) {
        period = "PM";
        if (curTime.hour > 12) {
            curTime.hour -= 12;
        }
    }
    if (curTime.hour == 0) {
        curTime.hour = 12; // 0 hour is equivalent to 12 AM
    }

    char buffer[30]; // Buffer to hold formatted time string (HH:MM:SS PP)
    std::sprintf(buffer, "%d:%02d:%02d %s", curTime.hour, curTime.minute, curTime.second, period.c_str());
    return String(buffer);
}