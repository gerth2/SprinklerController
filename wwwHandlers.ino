#include "wwwHandlers.h"
#include "stateMachine.h"

void install_handlers(AsyncWebServer * server) {

  server->on("/setCmdState", HTTP_GET, [](AsyncWebServerRequest *request){
    String action = request->getParam("state")->value();
    
    if(action == "OFF"){
        setCmdState(STATE_OFF);
    } else if(action == "AUTO") {
        setCmdState(STATE_AUTO);
    } else if(action == "MANUAL") {
        setCmdState(STATE_MANUAL);
    } else {
        Serial.println("Got unknown state command!");
    }

    request->send(200, "text/plain", String(action));
  });


}
