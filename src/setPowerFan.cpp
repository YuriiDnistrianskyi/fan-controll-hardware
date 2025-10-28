#include "../include/setPowerFan.hpp"

#include "../include/powerFanEnum.hpp"
#include "../include/config.hpp"

extern bool lastFanState;
extern PowerFanEnum currentPowerFan;
extern PowerFanEnum powerFanMQTT;
extern bool usingPowerFanMQTT;

PowerFanEnum lastPowerFanPotentiometer = POWER_FAN_0;

void setPowerFan(bool fanState) {
    uint8_t valuePowerFan = analogRead(POTENTIOMETER_PIN);
    PowerFanEnum powerFanPotentiometer = POWER_FAN_0;
    
    if (valuePowerFan >= 0 && valuePowerFan <= 15) {
        powerFanPotentiometer = POWER_FAN_0;
    }
    else if (valuePowerFan > 15 && valuePowerFan < 85) {
        powerFanPotentiometer = POWER_FAN_1;  
    }
    else if (valuePowerFan >= 85 && valuePowerFan < 170) {
        powerFanPotentiometer = POWER_FAN_2;
    }
    else if (valuePowerFan >= 170) {
        powerFanPotentiometer = POWER_FAN_3;
    }

    if (lastPowerFanPotentiometer != powerFanPotentiometer) {
        lastPowerFanPotentiometer = powerFanPotentiometer;
        if (usingPowerFanMQTT == true) {
            usingPowerFanMQTT = false;
        }
    }

    PowerFanEnum newPower = usingPowerFanMQTT ? powerFanMQTT : powerFanPotentiometer;

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

    Serial.println("State Fan: " + String(fanState));
    Serial.println("Power Fan Potentiometer: " + String(powerFanPotentiometer));
    Serial.println("Power Fan MQTT: " + String(powerFanMQTT));
    Serial.print("Current Power Fan: ");
    Serial.println(fanState ? String(currentPowerFan) : "0");
}
