#include <Adafruit_BME280.h>

#include "../include/readData.hpp"

extern Adafruit_BME280 bme;

float readTemperature() {
    float temperature = bme.readTemperature() + 30.00; // + 30 for motor
    return temperature;
}

float readPressure() {
    float pressure = (bme.readPressure() / 100.0F); // hPa // But for motor -> kPa
    return pressure;
}
