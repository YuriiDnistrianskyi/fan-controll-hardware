#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Arduino.h>

extern const uint8_t FAN_PIN;

extern const uint8_t BME280_SDA_PIN;
extern const uint8_t BME280_SCL_PIN;

extern const uint8_t BUTTON_PIN;

extern const uint32_t DELAY_TIME_FOR_READ_SENSOR;
extern const uint32_t DEBOUNCE_TIME_CLICK_BUTTON;

extern const char* SSID;
extern const char* PASSWORD;

#endif
