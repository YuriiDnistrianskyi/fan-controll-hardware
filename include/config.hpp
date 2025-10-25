#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <Arduino.h>

extern const uint8_t POTENTIOMETER_PIN;

extern const uint8_t FAN_PWM_PIN;

extern const uint8_t TM1637_CLK_PIN;
extern const uint8_t TM1637_DIO_PIN;

extern const uint8_t BUTTON_PIN;

extern const uint32_t DELAY_TIME_FOR_READ_SENSOR;
extern const uint32_t DEBOUNCE_TIME_CLICK_BUTTON;

extern const char* SSID;
extern const char* PASSWORD;

#endif
