#include "display.h"
#include <stdio.h>  // snprintf

void initDisplay(U8G2& u8g2) {
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setFontRefHeightExtendedText();
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();
    u8g2.setFontDirection(0);
}

void renderWeatherScreen(U8G2& u8g2, const WeatherReading& reading) {
    char buf[32];

    u8g2.firstPage();
    do {
        u8g2.setFont(u8g2_font_6x10_tf);

        if (!reading.valid) {
            u8g2.drawStr(0, 24, "Capteur indisponible");
            return;
        }

        // Ligne 1 : Température et Humidité
        snprintf(buf, sizeof(buf), "T:%.1fC  H:%.0f%%", reading.temperature, reading.humidity);
        u8g2.drawStr(0, 0, buf);

        // Ligne 2 : Pression
        snprintf(buf, sizeof(buf), "P: %.1f hPa", reading.pressure);
        u8g2.drawStr(0, 13, buf);

        // Ligne 3 : Point de rosée
        snprintf(buf, sizeof(buf), "Td: %.1f C", reading.dewPoint);
        u8g2.drawStr(0, 26, buf);

        // Séparateur horizontal
        u8g2.drawHLine(0, 40, 128);

        // Ligne 4 : titre / statut
        u8g2.setFont(u8g2_font_5x7_tf);
        u8g2.drawStr(0, 43, "Station Meteo  v1.0");

    } while (u8g2.nextPage());
}