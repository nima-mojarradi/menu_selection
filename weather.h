#ifndef WEATHER_H
#define WEATHER_H

#include <TFT_eSPI.h>
#include <ArduinoJson.h>

// Struct for weather data
struct WeatherData {
  float temperature;
  int humidity;
  int pressure;
  String description;
  String iconCode;
};

// Function declarations
bool getWeatherData(WeatherData& data);
void displayWeather(TFT_eSPI& tft, const WeatherData& data);

#endif
