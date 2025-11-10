#include "../include/config.hpp"

#include <Arduino.h>
#include "../my.cpp"

// PINS
const uint8_t POTENTIOMETER_PIN = A0;

const uint8_t FAN_PWM_PIN = D8;

// const uint8_t BME280_SDA_PIN = D2;
// const uint8_t BME280_SCL_PIN = D1;

const uint8_t TM1637_CLK_PIN = D5;
const uint8_t TM1637_DIO_PIN = D6;

const uint8_t BUTTON_PIN = D7;

// TIME DELAYS
const uint32_t DELAY_TIME_FOR_READ_SENSOR = 1000;
const uint32_t DEBOUNCE_TIME_CLICK_BUTTON = 2000;
const uint32_t DELAY_TIME_FOR_RECONNECT_MQTT = 5000;

// WIFI CONNECTION
const char* SSID = MY_SSID;
const char* PASSWORD = MY_PASSWORD;

// MQTT
const char* MQTT_BROKER_URI = MY_MQTT_BROKER_URI;
const char* MQTT_BROKER_PORT = MY_MQTT_BROKER_PORT;

// 
const uint8_t MAX_ALLOWED_TEMPERATURE = 60;
const uint8_t MIN_ALLOWED_TEMPERATURE = 35;
