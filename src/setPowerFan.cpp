#include "../include/setPowerFan.hpp"

#include "../include/config.hpp"

extern bool lastFanState;
extern uint8_t currentPowerFan;
extern uint8_t powerFanMQTT;
extern bool usingPowerFanMQTT;

uint8_t lastPowerFanPotentiometer = 0;

void setPowerFan(bool fanState) {
    uint8_t valuePowerFan = analogRead(POTENTIOMETER_PIN);
    uint8_t powerFanPotentiometer = 0;
    
    if (valuePowerFan >= 0 && valuePowerFan <= 10) {
        powerFanPotentiometer = 0;
    }
    else if (valuePowerFan > 10 && valuePowerFan < 85) {
        powerFanPotentiometer = 100;  
    }
    else if (valuePowerFan >= 85 && valuePowerFan < 170) {
        powerFanPotentiometer = 200;
    }
    else if (valuePowerFan >= 170) {
        powerFanPotentiometer = 255;
    }

    if (lastPowerFanPotentiometer != powerFanPotentiometer) {
        lastPowerFanPotentiometer = powerFanPotentiometer;
        if (usingPowerFanMQTT == true) {
            usingPowerFanMQTT = false;
        }
    }

    // if (usingPowerFanMQTT == false && lastPowerFanPotentiometer != powerFanPotentiometer) {
    //     lastPowerFanPotentiometer = powerFanPotentiometer;
    // }

    // if (usingPowerFanMQTT == true && lastPowerFanPotentiometer != powerFanPotentiometer) {
    //     usingPowerFanMQTT = false;
    //     lastPowerFanPotentiometer = powerFanPotentiometer;
    // }

    Serial.println("--------------------------------");
    Serial.println("State Fan: " + String(fanState));
    Serial.println("Power Fan Potentiometer: " + String(powerFanPotentiometer));
    Serial.println("State Fan MQTT: " + String(powerFanMQTT));

    uint8_t newPower = usingPowerFanMQTT ? powerFanMQTT : powerFanPotentiometer;

    if (fanState) {
        if (lastFanState != fanState) {
            lastFanState = fanState;
            analogWrite(FAN_PWM_PIN, currentPowerFan);
        } 
        else if (currentPowerFan != newPower) {
            currentPowerFan = newPower;
            analogWrite(FAN_PWM_PIN, currentPowerFan);
        }
    } 
    else {
        if (lastFanState != fanState) {
            lastFanState = fanState;
            analogWrite(FAN_PWM_PIN, 0);
            // digitalWrite(FAN_PWM_PIN, LOW);
        } 
        else if (currentPowerFan != newPower) {
            currentPowerFan = newPower;
        }
    }
}
