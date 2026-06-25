#include "formulas.h"
#include <cmath>

float calculateDewPoint(float temperatureCelsius, float humidityPercent) {
    // Formule de Magnus (Lawrence 2005)
    // Valide pour T ∈ [-40°C, +60°C]
    const float a = 17.625f;
    const float b = 243.04f;
    float gamma = std::log(humidityPercent / 100.0f)
                  + (a * temperatureCelsius) / (b + temperatureCelsius);
    return (b * gamma) / (a - gamma);
}