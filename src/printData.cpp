#include <Arduino.h>
#include <TM1637Display.h>

#include "../include/printData.hpp"

extern TM1637Display display;

void printData(float temperature) {
    int t = int(temperature * 100);
    display.showNumberDecEx(t, 0b01000000);
    // Serial.println("Temperature: " + String(temperature));
}
