#include <ESP8266WiFi.h>

#include "../include/initWiFi.hpp"

#include "../include/config.hpp"

void initWiFi() {
    WiFi.begin(SSID, PASSWORD);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(2000);
    }
    Serial.println();
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
}
