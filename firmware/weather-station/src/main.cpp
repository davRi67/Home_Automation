#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "sensor.h"
#include "display.h"

Adafruit_BME280 bme;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const unsigned long SENSOR_INTERVAL_MS = 5000;
unsigned long lastSensorRead = 0;
WeatherReading lastReading;

void setup() {
    Serial.begin(115200);
    delay(2000);
    Wire.begin();

    if (!bme.begin(0x76)) {
        Serial.println("ERREUR : BME280 non trouvé à l'adresse 0x76 !");
        Serial.println("Vérifier le câblage I2C et l'adresse.");
        while (true) { delay(1000); }  // bloque — pas de silence sur échec
    }

    initDisplay(u8g2);
    Serial.println("BME280 initialisé.");
}

void loop() {
    unsigned long now = millis();

    if (now - lastSensorRead >= SENSOR_INTERVAL_MS) {
        lastSensorRead = now;
        lastReading = readSensor(bme);

        if (lastReading.valid) {
            Serial.printf("T:%.2f H:%.1f P:%.1f Td:%.2f\n",
                lastReading.temperature, lastReading.humidity,
                lastReading.pressure, lastReading.dewPoint);
        }

        renderWeatherScreen(u8g2, lastReading);
    }
}