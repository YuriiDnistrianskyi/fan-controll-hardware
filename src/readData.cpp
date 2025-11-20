#include <Adafruit_BME280.h>

#include "../include/readData.hpp"

extern Adafruit_BME280 bme;

float readTemperature() {
    float temperature = bme.readTemperature() + 30.00;
    return temperature;
}

float readPressure() {
    float pressure = (bme.readPressure() / 100.0F); // hPa
    return pressure;
}
