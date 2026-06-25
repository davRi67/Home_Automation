#pragma once
#include <U8g2lib.h>
#include "sensor.h"

void initDisplay(U8G2& u8g2);
void renderWeatherScreen(U8G2& u8g2, const WeatherReading& reading);