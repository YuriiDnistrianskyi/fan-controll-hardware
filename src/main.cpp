#include <Arduino.h>
#include "../include/config.hpp"
#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/readData.hpp"
#include "../include/printData.hpp"
#include "../include/setPowerFan.hpp"

uint32_t lastTimeForReadSensor = 0;
bool fanState = false;
bool lastFanState = false;
uint8_t lastPowerFan = 0;

void setup() {
  initPins();
  initWiFi();
}

void loop() {
  uint32_t nowTimeForReadSensor = millis();
  if ((nowTimeForReadSensor - lastTimeForReadSensor) > DELAY_TIME_FOR_READ_SENSOR) {
    lastTimeForReadSensor = nowTimeForReadSensor;
    float motorTemperature = readData();
    printData(motorTemperature);

    if (motorTemperature >= MAX_ALLOWED_TEMPERATURE) {
      if (fanState != true) {
        fanState = true;
      }
      // if (lastPowerFan == 0) {
      //   lastPowerFan = 85;
      // }
    } else if (motorTemperature <= MIN_ALLOWED_TEMPERATURE) {
      if (fanState != false) {
        fanState = false;
      }
    }

    // mqtt
    setPowerFan(fanState);
  }
}
