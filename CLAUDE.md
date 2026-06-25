# Contexte projet — dede_automation (Home Automation)

## Station météo (firmware actuel)
- Carte : Arduino Nano ESP32 (ESP32-S3), projet PlatformIO
- Emplacement : firmware/weather-station/
- Capteurs I2C : BME280 (0x76) + OLED SSD1306 (0x3C) sur A4(SDA)/A5(SCL), 3,3V
- ⚠️ Vérifier registre 0xD0 : 0x60 = BME280, 0x58 = BMP280
  (les breakouts violets contiennent souvent un BMP280 sans humidité)

## Méthode de travail
- Requirements-first : FR-x/NFR-x tracés, critères Gherkin, tests liés
- Mesurer avant d'inférer ; isoler les variables par phase
- Expliquer le « pourquoi » avant le « comment »
- Points de vérification : git status avant/après add, etc.
- Langue de travail : français

## Tâche en cours
- Valider la config PlatformIO via un sketch scanner I2C + lecture chip ID
- Priorité 1 firmware : acquisition capteur + affichage OLED local (sans WiFi)
- Priorité 2 : WiFi + MQTT vers le Pi