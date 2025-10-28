#include <Arduino.h>
#include <PubSubClient.h>

#include "../include/config.hpp"
#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/forMQTT.hpp"
#include "../include/readData.hpp"
#include "../include/printData.hpp"
#include "../include/setPowerFan.hpp"

extern PubSubClient client;

uint32_t lastTimeForReadSensor = 0;
bool fanState = false;
bool lastFanState = false;
uint8_t currentPowerFan = 0;

void setup() {
  initPins();
  initWiFi();
  initMQTT();
}

void loop() {
  if (!client.connected())
    reconnect();

  client.loop();

  uint32_t nowTimeForReadSensor = millis();
  if ((nowTimeForReadSensor - lastTimeForReadSensor) > DELAY_TIME_FOR_READ_SENSOR) {
    lastTimeForReadSensor = nowTimeForReadSensor;
    float motorTemperature = readData();
    printData(motorTemperature);
    sendDataMQTT(motorTemperature);

    if (motorTemperature >= MAX_ALLOWED_TEMPERATURE) {
      if (fanState != true) {
        fanState = true;
      }
      // if (lastPowerFan == 0) {
      //   lastPowerFan = 85;
      // }
    } 
    else if (motorTemperature <= MIN_ALLOWED_TEMPERATURE) {
      if (fanState != false) {
        fanState = false;
      }
    }
    
    setPowerFan(fanState);
  }
}
