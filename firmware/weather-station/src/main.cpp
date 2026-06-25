// Sketch de validation — Nano ESP32 (ESP32-S3)
// Objectif : confirmer que le bus I2C détecte le BME/BMP280 et l'OLED,
//            et identifier le capteur via son chip ID (registre 0xD0).
#include <Arduino.h>
#include <Wire.h>

static const uint8_t CHIP_ID_REG  = 0xD0;
static const uint8_t ADDR_SENSOR  = 0x76;  // BME/BMP280
static const uint8_t ADDR_OLED    = 0x3C;  // SSD1306

static uint8_t readRegister(uint8_t devAddr, uint8_t reg) {
    Wire.beginTransmission(devAddr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(devAddr, (uint8_t)1);
    return Wire.available() ? Wire.read() : 0xFF;
}

void setup() {
    Serial.begin(115200);
    delay(2000);  // laisser le temps au moniteur CDC de se connecter

    Serial.println("\n=== Scanner I2C — Nano ESP32 (ESP32-S3) ===\n");

    // SDA = A4 / SCL = A5 (brochage Arduino standard)
    Wire.begin();

    // --- Scan complet du bus ---
    Serial.println("Scan I2C (0x01 - 0x7F) :");
    uint8_t found = 0;
    for (uint8_t addr = 1; addr < 128; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.printf("  [TROUVE] 0x%02X", addr);
            if (addr == ADDR_SENSOR) Serial.print("  <- capteur BME/BMP280");
            if (addr == ADDR_OLED)   Serial.print("  <- OLED SSD1306");
            Serial.println();
            found++;
        }
    }
    if (found == 0)
        Serial.println("  Aucun peripherique trouve — verifier cablage 3.3V et SDA/SCL.");
    Serial.printf("\n  Total : %u peripherique(s)\n\n", found);

    // --- Identification BME280 vs BMP280 ---
    Serial.println("Lecture chip ID @ 0x76, registre 0xD0 :");
    uint8_t chipId = readRegister(ADDR_SENSOR, CHIP_ID_REG);
    Serial.printf("  chip_id = 0x%02X  =>  ", chipId);
    switch (chipId) {
        case 0x60: Serial.println("BME280 — temperature + pression + humidite (OK)"); break;
        case 0x58: Serial.println("BMP280 — temperature + pression, SANS humidite (breakout violet ?)"); break;
        case 0xFF: Serial.println("Lecture impossible — peripherique absent ou erreur bus"); break;
        default:   Serial.printf("Inconnu (0x%02X) — adresse ou registre incorrect\n", chipId); break;
    }
}

void loop() {
    // Diagnostic one-shot : rien a faire en boucle
    delay(5000);
}
