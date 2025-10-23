#include <WiFi.h>

#include "../include/initWiFi.hpp"

#include "../include/config.h"

void initWiFi() {
    WiFi.begin(SSID, PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        Serial.println("Connecting to WiFi ...");
    }
    Serial.println("Connected to WiFi");
    Serial.println("IP Address: " + WiFi.localIP());
}
