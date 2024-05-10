#include <WiFi.h>
#include <WiFiClient.h>
#include "AsyncTCP.h"
#include <ESPAsyncWebServer.h>
#include <ESPmDNS.h>
#include <Preferences.h>

#include "currentTime.h"
#include "www.h"
#include "wwwHandlers.h"

const char *ssid = "SprinklerControlSetup";
const uint8_t nvmVersion = 2;

Preferences preferences;

AsyncWebServer server(80);

// Create an Event Source on /events
AsyncEventSource events("/events");

const char *captivePortalRedirect = "http://sprinkler.local/setup.html";

void handleConnect(AsyncWebServerRequest *request)
{
    String ssid = request->arg("ssid");
    String password = request->arg("password");

    if (ssid.length() > 0 && password.length() > 0)
    {
        // Save SSID and password to preferences
        preferences.begin("network", false); // Open preferences with namespace "network", read-only
        preferences.putString("ssid", ssid);
        preferences.putString("password", password);
        preferences.putUShort("nvmVersion", nvmVersion);
        preferences.end(); // Close preferences
        // Connect to the provided network
        Serial.println("Connecting to provided wifi network..");

        WiFi.begin(ssid.c_str(), password.c_str());
        request->send(200, "text/plain", "Connecting to network...");
    }
    else
    {
        request->send(400, "text/plain", "SSID and password cannot be empty");
    }
}

void setupMDNS()
{
    if (!MDNS.begin("sprinkler"))
    { // Replace "esp32" with your desired hostname
        Serial.println("Error setting up MDNS responder!");
        while (1)
        {
            delay(1000);
        }
    }
    Serial.println("mDNS responder started");
}

void setup()
{
    Serial.begin(115200);

    // Initialize Preferences library
    preferences.begin("network", false); // Open preferences with namespace "network", read-only

    // Read SSID and password from preferences
    String storedSSID = preferences.getString("ssid", "");
    String storedPassword = preferences.getString("password", "");
    uint8_t storedNvmVersion = preferences.getUShort("nvmVersion", 0);

    Serial.println(storedSSID);
    Serial.println(storedPassword);
    Serial.println(storedNvmVersion);

    if (storedSSID.length() > 0 && storedPassword.length() > 0 && storedNvmVersion == nvmVersion)
    {

        Serial.println("Attempting to connect to stored wifi network...");
        WiFi.begin(storedSSID, storedPassword);
        for (uint8_t retries = 0; retries < 10; retries++)
        {
            delay(1000);
            if (WiFi.status() != WL_CONNECTED)
            {
                Serial.println("Connection failed, retrying...");
            }
            else
            {
                // success, break early
                break;
            }
        }
        Serial.println("Connected to WiFi");

        syncTime();
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        // Fallback - Initialize WiFi as access point with no password
        // Allows for local configuration.
        WiFi.softAP(ssid);
        Serial.println("Access Point mode enabled.");

        // Print IP address
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    }

    init_web_pages(&server);
    install_handlers(&server);

    server.on("/connect", handleConnect);

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->redirect(captivePortalRedirect); });

    // Handle Web Server Events
    events.onConnect([](AsyncEventSourceClient *client)
                     {
        if(client->lastId()){
            Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
        }

        // send event with message "hello!", id current millis
        // and set reconnect delay to 1 second
        client->send("hello!", NULL, millis(), 10000); });

    server.addHandler(&events);

    setupMDNS(); // Call mDNS setup function

    server.begin();
    Serial.println("HTTP server started");
}

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

void loop()
{
    if ((millis() - lastTime) > timerDelay)
    {
        auto curTime = getCurTime();
        String currentTimeStr = String(curTime.hour) + ":" + String(curTime.minute) + ":" + String(curTime.second);
        // Serial.printf("Time = %s \n", currentTimeStr);

        // Send Events to the Web Client with the Sensor Readings
        events.send("ping", NULL, millis());
        events.send(String(currentTimeStr).c_str(), "time", millis());

        lastTime = millis();
    }
}