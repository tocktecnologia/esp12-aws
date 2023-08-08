#ifndef WIFIMANAGER_H
#define WIFIMANAGER_H


#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include "utils.h"

WiFiManager wm;
int maxTries = 10;

void setupWM() {
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID);
    Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));
    int aux = 0;
    while (WiFi.status() != WL_CONNECTED && aux<maxTries)
    {
        Serial.println("trying ["+ String(aux) + "] connect to SSID: " + String(WIFI_SSID));
        delay(1000);
        aux++;
    }


    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
    //reset settings - wipe credentials for testing
    //wm.resetSettings();
    wm.setConfigPortalBlocking(true);
    // wm.setConfigPortalTimeout(60);
  
    // reset
    // wm.resetSettings();
    // wm.erase(true);
  
    //automatically connect using saved credentials if they exist
    //If connection fails it starts an access point with the specified name
    if(wm.autoConnect(getClientID().c_str(),"tock1234")){
        Serial.println("connected...yeey :)");
    }
    else {
        Serial.println("Configportal running");
    }
}

void loopWM() {
    wm.process();
    // put your main code here, to run repeatedly:
}

#endif // WIFIMANAGER_H