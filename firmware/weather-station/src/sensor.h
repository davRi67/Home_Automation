#pragma once
#include <Adafruit_BME280.h>

struct WeatherReading {
    float temperature;  // °C
    float humidity;     // %
    float pressure;     // hPa
    float dewPoint;     // °C
    bool  valid;        // false si le capteur ne répond pas
};

WeatherReading readSensor(Adafruit_BME280& bme);