#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include "weather.h"
#include "time_helper.h" // Include your new time header file

TFT_eSPI tft = TFT_eSPI();

const char* ssid = "Galaxy A34 5G 58C7";
const char* password = "3858nima";

const int BUTTON_UP_PIN = 22;
const int BUTTON_DOWN_PIN = 21;
const int BUTTON_SELECT_PIN = 23;

const char* menuItems[] = {"Weather", "Time", "Settings"};
const int numMenuItems = 3;
int currentSelection = 0;

void drawMenu() {
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(3);
  for (int i = 0; i < numMenuItems; i++) {
    tft.setCursor(20, 50 + (i * 40));
    if (i == currentSelection) {
      tft.setTextColor(TFT_YELLOW);
      tft.print("> ");
    } else {
      tft.setTextColor(TFT_WHITE);
      tft.print("  ");
    }
    tft.println(menuItems[i]);
  }
}

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  pinMode(BUTTON_UP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_DOWN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT_PIN, INPUT_PULLUP);

  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    tft.print(".");
  }
  tft.println("\nWiFi connected!");
  configTime(12600, 0, "pool.ntp.org");
  delay(1000);

  drawMenu();
}

void loop() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    currentSelection--;
    if (currentSelection < 0) currentSelection = numMenuItems - 1;
    drawMenu();
    delay(250);
  }

  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    currentSelection++;
    if (currentSelection >= numMenuItems) currentSelection = 0;
    drawMenu();
    delay(250);
  }

  if (digitalRead(BUTTON_SELECT_PIN) == LOW) {
    if (currentSelection == 0) { // Weather
      WeatherData data;
      if (getWeatherData(data)) {
        displayWeather(tft, data);
      } else {
        tft.fillScreen(TFT_RED);
        tft.setCursor(0, 0);
        tft.setTextColor(TFT_WHITE);
        tft.setTextSize(2);
        tft.println("Failed to get weather data.");
        delay(2000);
      }
      delay(5000);
      drawMenu();
    } else if (currentSelection == 1) { // Time
      runClock(tft);
      delay(5000);
      drawMenu();
    }
    delay(250);
  }
}
