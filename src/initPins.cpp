#include <Adafruit_BME280.h>
#include <TM1637Display.h>

#include "../include/initPins.hpp"

#include "../include/config.hpp"

extern fanState;

Adafruit_BME280 bme;
TM1637Display display(BME280_SCL_PIN, BME280_SDA_PIN);

volatile uint32_t lastTimeClickButton = 0;

void IRAM_ATTR clickbutton() {
    uint32_t nowTimeClikcButton = millis();
    if ((nowTimeClickButton - lastTimeClickButton) > DEBOUNCE_TIME_CLICK_BUTTON) {
        lastTimeClickButton = nowTimeClickButton;
        fanState = !fanstate;
    }
}

void initBME280() {
    bool status;
    status = bme.begin(0x76);
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor");
        while(1);
    }
}

void initDisplay() {
    display.setBrightness(0x0f);
    display.clear();
}

void initPins() {
    // init BME280
    initBME280();

    // init Fan

    // init display
    initDisplay();

    // init button
    pinMode(BUTTON_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), clickButton, RISING);
}
