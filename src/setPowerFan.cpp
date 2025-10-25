#include "../include/setPowerFan.hpp"

#include "../include/config.hpp"

bool lastFanState = false;
uint8_t lastPowerFan = 0;

void setPowerFan(bool fanState) {
    uint8_t valuePowerFan = analogRead(POTENTIOMETER_PIN);
    uint8_t powerFan;
    
    if (valuePowerFan >= 0 && valuePowerFan <= 10) {
        powerFan = 0;  
    } else if (valuePowerFan > 10 && valuePowerFan < 85) {
        powerFan = 85;  
    } else if (valuePowerFan >= 85 && valuePowerFan < 170) {
        powerFan = 170;
    } else if (valuePowerFan >= 170) {
        powerFan = 255;
    }

    if (fanState) {
        if (lastFanState != fanState) {
            lastFanState = fanState;
            analogWrite(FAN_PWM_PIN, lastPowerFan);
        } else if (lastPowerFan != powerFan) {
            lastPowerFan = powerFan;
            analogWrite(FAN_PWM_PIN, lastPowerFan);
        }
    } else {
        if (lastFanState != fanState) {
            lastFanState = fanState;
            analogWrite(FAN_PWM_PIN, 0);
        } else if (lastPowerFan != powerFan) {
            lastPowerFan = powerFan;
        }
    }
}
