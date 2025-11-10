#include <Adafruit_BME280.h>

#include "../include/readData.hpp"

extern Adafruit_BME280 bme;

float readData() {
    float temperature = bme.readTemperature() + 30.00;
    return temperature;
}
