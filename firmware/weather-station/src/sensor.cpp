#include "sensor.h"
#include "formulas.h"

WeatherReading readSensor(Adafruit_BME280& bme) {
    WeatherReading r;
    r.temperature = bme.readTemperature();
    r.humidity    = bme.readHumidity();
    r.pressure    = bme.readPressure() / 100.0f;  // Pa → hPa
    r.dewPoint    = calculateDewPoint(r.temperature, r.humidity);

    // Valeurs NaN ou hors plage = lecture invalide
    r.valid = !isnan(r.temperature) && !isnan(r.humidity) && !isnan(r.pressure)
              && r.temperature > -40.0f && r.temperature < 85.0f
              && r.humidity > 0.0f && r.humidity <= 100.0f;
    return r;
}