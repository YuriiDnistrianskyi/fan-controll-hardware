#include <Arduino.h>
#include "../include/config.hpp"
#include "../include/initPins.hpp"
#include "../include/initWiFi.hpp"
#include "../include/readData.hpp"
#include "../include/printData.hpp"
#include "../include/setPowerFan.hpp"

uint32_t lastTimeForReadSensor = 0;
bool fanState = false;

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
    // mqtt
    setPowerFan(fanState);
  }
}
