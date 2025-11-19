#include <Adafruit_BME280.h>

#include "../include/readData.hpp"

extern Adafruit_BME280 bme;

float readTemperature() {
    float temperature = bme.readTemperature() + 30.00;
    return temperature;
}

float readPressure() {
    float pressure = (bme.readPressure() / 100.0F) * 16 * pow(10, -5);
    return pressure;
}
