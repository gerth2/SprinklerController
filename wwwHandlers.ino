#include "wwwHandlers.h"
#include "commandStateMachine.h"

void install_handlers(AsyncWebServer * server) {

  server->on("/setCmdState", HTTP_GET, [](AsyncWebServerRequest *request){
    String action = request->getParam("state")->value();
    
    if(action == "AUTO") {
        csm_setCmdState(STATE_AUTO);
    } else if(action == "MANUAL") {
        csm_setCmdState(STATE_MANUAL);
    } else {
        Serial.println("Got unknown state command!");
    }

    request->send(200, "text/plain", String(action));
  });


  server->on("/requestZoneActive", HTTP_GET, [](AsyncWebServerRequest *request){
    uint8_t zoneIdx = request->getParam("zone")->value().toInt();
    
    if(zoneIdx>= 1 and zoneIdx<=7){
        csm_requestManualZone(zoneIdx);
        Serial.printf("Got zone %d activate command.\n", zoneIdx);

    } else {
        Serial.printf("Got unknown zone %d activate command!\n", zoneIdx);
    }

    request->send(200, "text/plain", String(zoneIdx));
  });

  server->on("/requestAllOff", HTTP_GET, [](AsyncWebServerRequest *request){
    
    csm_requestAllOff();
    Serial.printf("Got all-off command.\n");
    request->send(200, "text/plain", String(""));
  });

}
