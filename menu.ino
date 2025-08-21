#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include "weather.h"
#include "time_helper.h" 
#include "ping_pong.h"

TFT_eSPI tft = TFT_eSPI();

const char* ssid = "Galaxy A34 5G 58C7";
const char* password = "3858nima";

const char* menuItems[] = {"Weather", "Time", "Ping pong"};
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

#define MODE_MENU 0
#define MODE_WEATHER 1
#define MODE_TIME 2
#define MODE_PINGPONG 3

int currentMode = MODE_MENU;

void loop() {
  if (digitalRead(BUTTON_UP_PIN) == LOW) {
    if (currentMode == MODE_MENU) {
      currentSelection--;
      if (currentSelection < 0) currentSelection = numMenuItems - 1;
      drawMenu();
    }
    delay(250);
  }

  if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
    if (currentMode == MODE_MENU) { // فقط در منو اجازه جابه‌جایی بده
      currentSelection++;
      if (currentSelection >= numMenuItems) currentSelection = 0;
      drawMenu();
    }
    delay(250);
  }

  if (digitalRead(BUTTON_SELECT_PIN) == LOW) {
    delay(250); // تأخیر برای دبینسینگ

    if (currentMode == MODE_MENU) { // اگر در منو هستیم
      if (currentSelection == 0) { // آب و هوا
        currentMode = MODE_WEATHER;
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
      } else if (currentSelection == 1) {
        currentMode = MODE_TIME;
        runClock(tft);
      } else if (currentSelection == 2) {
        currentMode = MODE_PINGPONG;
        runPong();
      }
    } else {
      if (currentMode == MODE_WEATHER || currentMode == MODE_TIME || currentMode == MODE_PINGPONG) {
        currentMode = MODE_MENU;
        drawMenu();
      }
    }

    while (digitalRead(BUTTON_SELECT_PIN) == LOW) {
      delay(10);
    }
  }
}
