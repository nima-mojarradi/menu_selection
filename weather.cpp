#include "weather.h"
#include <HTTPClient.h>

// API and city information
const String openWeatherMapApiKey = "0da42fc97e00bbde9fae47f103a71ca6";
const String city = "Tehran";
const String units = "metric";
const String lang = "fa";

bool getWeatherData(WeatherData& data) {
  HTTPClient http;
  String serverPath = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "&units=" + units + "&appid=" + openWeatherMapApiKey + "&lang=" + lang;
  http.begin(serverPath.c_str());
  int httpResponseCode = http.GET();
  if (httpResponseCode == HTTP_CODE_OK) {
    String payload = http.getString();
    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, payload);
    if (error) { return false; }
    data.temperature = doc["main"]["temp"].as<float>();
    data.humidity = doc["main"]["humidity"].as<int>();
    data.pressure = doc["main"]["pressure"].as<int>();
    data.description = doc["weather"][0]["description"].as<String>();
    data.iconCode = doc["weather"][0]["icon"].as<String>();
    return true;
  } else {
    return false;
  }
}

void displayWeather(TFT_eSPI& tft, const WeatherData& data) {
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.print("City: ");
  tft.println(city);
  tft.setTextSize(4);
  tft.setTextColor(TFT_YELLOW);
  tft.print(data.temperature);
  tft.println(" C");
  tft.setTextSize(2);
  tft.setTextColor(TFT_CYAN);
  tft.print("Humidity: ");
  tft.print(data.humidity);
  tft.println("%");
  tft.setTextColor(TFT_ORANGE);
  tft.print("Pressure: ");
  tft.print(data.pressure);
  tft.println("hPa");
  tft.setTextColor(TFT_GREEN);
  tft.println(data.description);
}
