// Your main file: menu.ino

// Libraries
#include <SPI.h>
#include <TFT_eSPI.h>
#include <WiFi.h>

// Include the header file you will create
#include "weather.h"

// TFT LCD object (defined once)
TFT_eSPI tft = TFT_eSPI();

// WiFi credentials (defined once)
const char* ssid = "Dina";
const char* password = "Dd78134003Segco";

// Button pins (replace with your actual pins)
const int BUTTON_UP_PIN = 21;
const int BUTTON_DOWN_PIN = 22;
const int BUTTON_SELECT_PIN = 23;

// Menu options
const char* menuItems[] = {"Weather", "Time", "Settings"};
const int numMenuItems = 3;
int currentSelection = 0;

// Function to draw the menu
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

  // Connect to WiFi in setup()
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
  delay(1000);

  drawMenu();
}

void loop() {
  // Read button states
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
    if (currentSelection == 0) { // "Weather" is the first item (index 0)
      WeatherData data;
      // Get and display weather data
      if (getWeatherData(data)) {
        displayWeather(tft, data);
      } else {
        // Handle error
      }
      delay(5000); // Display weather for 5 seconds
      drawMenu(); // Go back to the menu
    }
    // You can add more 'if' statements for other menu items here
    
    delay(250);
  }
}
