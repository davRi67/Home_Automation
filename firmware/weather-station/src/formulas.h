#pragma once

/**
 * Calcule le point de rosée (°C) via la formule de Magnus.
 * @param temperatureCelsius  Température en °C
 * @param humidityPercent     Humidité relative en % (0–100)
 * @return Point de rosée en °C
 */
float calculateDewPoint(float temperatureCelsius, float humidityPercent);