#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include "sensor.h"

Adafruit_BME280 bme;

void setup() {
    Serial.begin(115200);
    delay(2000);
    Wire.begin();

    if (!bme.begin(0x76)) {
        Serial.println("ERREUR : BME280 non trouvé à l'adresse 0x76 !");
        Serial.println("Vérifier le câblage I2C et l'adresse.");
        while (true) { delay(1000); }  // bloque — pas de silence sur échec
    }
    Serial.println("BME280 initialisé.");
}

void loop() {
    WeatherReading r = readSensor(bme);

    if (!r.valid) {
        Serial.println("Lecture invalide — vérifier le capteur.");
    } else {
        Serial.printf("T: %.2f °C  |  H: %.1f %%  |  P: %.1f hPa  |  Td: %.2f °C\n",
                      r.temperature, r.humidity, r.pressure, r.dewPoint);
    }
    delay(5000);
}