#include <Adafruit_BME280.h>
#include <TM1637Display.h>

#include "../include/initPins.hpp"

#include "../include/config.hpp"

extern bool fanState;

Adafruit_BME280 bme;
TM1637Display display(TM1637_CLK_PIN, TM1637_DIO_PIN);

volatile uint32_t lastTimeClickButton = 0;

void IRAM_ATTR clickButton() {
    uint32_t nowTimeClickButton = millis();
    if ((nowTimeClickButton - lastTimeClickButton) > DEBOUNCE_TIME_CLICK_BUTTON) {
        lastTimeClickButton = nowTimeClickButton;
        fanState = !fanState;
    }
}

void initBME280() {
    bool status;
    // Wire.begin(BME280_SCL_PIN, BME280_SDA_PIN);
    status = bme.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor");
        return;
    }
}

void initDisplay() {
    display.setBrightness(0x0f);
    display.clear();
}

void initFan() {
    analogWriteRange(255);
    pinMode(FAN_PWM_PIN, OUTPUT);
    analogWrite(FAN_PWM_PIN, 0);
}

void initPins() {
    Serial.begin(115200);

    initBME280();
    initFan();
    initDisplay();

    pinMode(BUTTON_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), clickButton, RISING);
}
