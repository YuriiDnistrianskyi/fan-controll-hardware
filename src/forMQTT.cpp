#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

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

void sendDataMQTT(float motorTemperature, bool fanState, PowerFanEnum powerFan) {
    StaticJsonDocument<200> docTemperature;
    docTemperature["motor/temperature"] = motorTemperature;
    String jsonTemperature;
    serializeJson(docTemperature, jsonTemperature);
    client.publish("motor/temperature", jsonTemperature.c_str());

    StaticJsonDocument<200> docFanState;
    docFanState["state"] = fanState ? 1 : 0;
    String jsonFanState;
    serializeJson(docFanState, jsonFanState);
    client.publish("fan/state/info", jsonFanState.c_str());

    uint8_t sendPowerFan;
    switch(powerFan) {
        case POWER_FAN_0:
            sendPowerFan = 0;
            break;
        case POWER_FAN_1:
            sendPowerFan = 1;
            break;
        case POWER_FAN_2:
            sendPowerFan = 2;
            break;  
        case POWER_FAN_3:
            sendPowerFan = 3;
            break;
        default:
            sendPowerFan = 0;
            break;
    }

    StaticJsonDocument<200> docFanPower;
    docFanPower["power"] = sendPowerFan;
    String jsonFanPower;
    serializeJson(docFanPower, jsonFanPower);
    client.publish("fan/power/info", jsonFanPower.c_str());
}

void callback(char* topic, byte* payload, unsigned int length) {
    String msg;
    for (int i = 0; i < length; i++) msg += (char)payload[i];

    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, msg);

    if (error) {
        Serial.print("Error: ");
        Serial.println(error.c_str());
        return;
    }

    if (String(topic) == "fan/state") {
        if (doc.containsKey("state")) {
            if (doc["state"] == 1 && fanState != true) {
                fanState = true;
            } 
            else if (doc["state"] == 0 && fanState != false) {
                fanState = false;
            }
        }
    } 
    else if(String(topic) == "fan/power") {
        if (doc.containsKey("power")) {
            String power = doc["power"];
            bool errorInSwitchCase = false;

            switch(power.toInt()) {
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
                    Serial.println("Unknow power fan value: " + power);
                    errorInSwitchCase = true;
                    break;
            }

            if (!errorInSwitchCase) {
                usingPowerFanMQTT = true;
            }
        }
    }
}

void initMQTT() {
    client.setServer(MQTT_BROKER_URI, atoi(MQTT_BROKER_PORT));
    client.setCallback(callback);
}
