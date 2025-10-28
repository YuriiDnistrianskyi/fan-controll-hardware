#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "../include/forMQTT.hpp"

#include "../include/powerFanEnum.hpp"
#include "../include/config.hpp"

extern bool fanState;
bool usingPowerFanMQTT = false;

WiFiClient wifiClient;
PubSubClient client(wifiClient);
uint32_t lastTimeForReconncetMQTT = 0;

PowerFanEnum powerFanMQTT = POWER_FAN_0;

void reconnect() {
    uint32_t nowTimeForReconnectMQTT = millis();
    if ((nowTimeForReconnectMQTT - lastTimeForReconncetMQTT) > DELAY_TIME_FOR_RECONNECT_MQTT) {
        lastTimeForReconncetMQTT = nowTimeForReconnectMQTT;
        Serial.println("Connecting to MQTT...");

        String clientId = "fanControllClient-";
        clientId += String(ESP.getChipId(), HEX);
    
        if (client.connect(clientId.c_str())) {
            Serial.println("Connected to MQTT");
            Serial.println("ID: " + clientId);
            
            if (client.subscribe("fan/state"))
                Serial.println("Subscribed to fan/state");
            else
                Serial.println("Failed to subscribe to fan/state");
            
            if (client.subscribe("fan/power"))
                Serial.println("Subscribed to fan/power");
            else
                Serial.println("Failed to subscribe to fan/power");
        } 
        else {
            Serial.print("Failed to connect to MQTT, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
        }
    }
}

void sendDataMQTT(float motorTemperature) {
    char temperature[10];
    dtostrf(motorTemperature, 6, 2, temperature);
    client.publish("motor/temperature", temperature);
}

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) msg += (char)payload[i];

    if (String(topic) == "fan/state") {
        if (msg == "ON" && fanState != true) {
            fanState = true;
        } 
        else if (msg == "OFF" && fanState != false) {
            fanState = false;
        }
    } 
    else if(String(topic) == "fan/power") {
        switch(msg.toInt()) {
            case 0:
                powerFanMQTT = POWER_FAN_0;
                break;
            case 1:
                powerFanMQTT = POWER_FAN_1;
                break;
            case 2:
                powerFanMQTT = POWER_FAN_2;
                break;  
            case 3:
                powerFanMQTT = POWER_FAN_3;
                break;
            default:
                break;
        }
        //
        usingPowerFanMQTT = true;
    }
}

void initMQTT() {
    client.setServer(MQTT_BROKER_URI, atoi(MQTT_BROKER_PORT));
    client.setCallback(callback);
}
