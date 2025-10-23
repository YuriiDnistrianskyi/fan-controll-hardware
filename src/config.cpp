#include "../include/config.hpp"

#include <Arduino.h>
#include "../my.cpp"

const uint8_t FAN_PIN = 5;

const uint8_t BME280_SDA_PIN = 21;
const uint8_t BME280_SCL_PIN = 22;

const uint8_t BUTTON_PIN = 1; //

const uint32_t DELAY_TIME_FOR_READ_SENSOR = 2000;
const uint32_t DEBOUNCE_TIME_CLICK_BUTTON = 2000;

const char* SSID = MY_SSID;
const char* PASSWORD = MY_PASSWORD;
