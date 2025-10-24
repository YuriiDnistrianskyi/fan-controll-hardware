#include "../include/config.hpp"

#include <Arduino.h>
#include "../my.cpp"

const uint8_t FAN_PIN = D7;

// const uint8_t BME280_SDA_PIN = D5;
// const uint8_t BME280_SCL_PIN = D6;

const uint8_t TM1637_CLK_PIN = D5;
const uint8_t TM1637_DIO_PIN = D6;

const uint8_t BUTTON_PIN = 2; //

const uint32_t DELAY_TIME_FOR_READ_SENSOR = 2000;
const uint32_t DEBOUNCE_TIME_CLICK_BUTTON = 2000;

const char* SSID = MY_SSID;
const char* PASSWORD = MY_PASSWORD;
