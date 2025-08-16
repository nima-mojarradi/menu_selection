#include "time_helper.h"
#include "time.h"

void runClock(TFT_eSPI& tft) {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    tft.fillScreen(TFT_RED);
    tft.setCursor(0, 0);
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(2);
    tft.println("Failed to get time.");
    delay(2000);
    return;
  }
  
  char time_buffer[80];
  strftime(time_buffer, sizeof(time_buffer), "%H:%M:%S", &timeinfo);
  
  char date_buffer[80];
  strftime(date_buffer, sizeof(date_buffer), "%Y/%m/%d", &timeinfo);

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(10, 50);
  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(3);
  tft.println("Date:");
  tft.setCursor(10, 80);
  tft.setTextSize(4);
  tft.println(date_buffer);
  
  tft.setCursor(10, 140);
  tft.setTextColor(TFT_YELLOW);
  tft.setTextSize(3);
  tft.println("Time:");
  tft.setCursor(10, 170);
  tft.setTextSize(4);
  tft.println(time_buffer);
}
