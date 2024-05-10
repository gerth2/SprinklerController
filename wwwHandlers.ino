#include "wwwHandlers.h"
#include "commandStateMachine.h"

void install_handlers(AsyncWebServer * server) {

  server->on("/setCmdState", HTTP_GET, [](AsyncWebServerRequest *request){
    String action = request->getParam("state")->value();
    
    if(action == "OFF"){
        csm_setCmdState(STATE_OFF);
    } else if(action == "AUTO") {
        csm_setCmdState(STATE_AUTO);
    } else if(action == "MANUAL") {
        csm_setCmdState(STATE_MANUAL);
    } else {
        Serial.println("Got unknown state command!");
    }

    request->send(200, "text/plain", String(action));
  });


}
