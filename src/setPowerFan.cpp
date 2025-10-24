#include "../include/setPowerFan.hpp"

#include "../include/config.hpp"

uint8_t lastValuePowerFan = 0;

void setPowerFan(bool fanState) {
    uint8_t valuePowerFan = analogRead(POTENTIOMETER_PIN);

    if (abs(valuePowerFan - lastValuePowerFan) > 40) {
        lastValuePowerFan = valuePowerFan;
        Serial.println("Power Fan: " + String(valuePowerFan));
        // set poser on fan
    }
}
