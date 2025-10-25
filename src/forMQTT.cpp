#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "../include/forMQTT.hpp"

#include "../include/config.hpp"

extern bool fanState;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
uint32_t lastTimeForReconncetMQTT = 0;

void reconnect() {
    while (!client.connected()) {
        uint32_t nowTimeForReconnectMQTT = millis();
        if ((nowTimeForReconnectMQTT - lastTimeForReconncetMQTT) > DELAY_TIME_FOR_RECONNECT_MQTT) {
            lastTimeForReconncetMQTT = nowTimeForReconnectMQTT;
            Serial.println("Connecting to MQTT...");
            if (client.connect("ESPClient")) {
                Serial.println("Connected to MQTT");
            } else {
                Serial.print("Failed to connect to MQTT, rc=");
                Serial.print(client.state());
                Serial.println(" try again in 5 seconds");
            }
        }
    };
}

void sendDataMQTT(float motorTemperature) {
    char temperature[10];
    dtostrf(motorTemperature, 6, 2, temperature);
    client.publish("motor/temperature", temperature);
}

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) msg += (char)payload[i];

    if (String(topic) == "home/fan") {
        if (msg == "ON" && fanState != true) {
            fanState = true;
        } else if (msg == "OFF" && fanState != false) {
            fanState = false;
        }
    }
}

void initMQTT() {
    client.setServer(MQTT_BROKER_URI, atoi(MQTT_BROKER_PORT));
    client.setCallback(callback);
}
