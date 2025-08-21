#include "ping_pong.h"

//// تعریف و مقداردهی متغیرها
//TFT_eSPI tft = TFT_eSPI();

float ball_x_speed = 1.5;
float ball_y_speed = 1.5;
float player_paddle_x = 10;
float player_paddle_y = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
float ai_paddle_x = SCREEN_WIDTH - 10 - PADDLE_WIDTH;
float ai_paddle_y = (SCREEN_HEIGHT / 2) - (PADDLE_HEIGHT / 2);
float ball_x = SCREEN_WIDTH / 2;
float ball_y = SCREEN_HEIGHT / 2;
int player_score = 0;
int ai_score = 0;

// توابع کمکی
void drawScore() {
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(SCREEN_WIDTH / 4, 10);
  tft.print(player_score);
  tft.setCursor((SCREEN_WIDTH / 4) * 3, 10);
  tft.print(ai_score);
}

void resetBall() {
  ball_x = SCREEN_WIDTH / 2;
  ball_y = SCREEN_HEIGHT / 2;
  ball_x_speed = (random(0, 2) == 0) ? 1.5 : -1.5;
  ball_y_speed = (random(0, 2) == 0) ? 1.5 : -1.5;
  delay(1000);
}

// تابع اصلی بازی
void runPong() {
  // تنظیمات اولیه
  player_score = 0;
  ai_score = 0;
  tft.fillScreen(TFT_BLACK);
  drawScore();

  while (digitalRead(BUTTON_SELECT_PIN) == HIGH) {
    float last_player_paddle_y = player_paddle_y;
    float last_ai_paddle_y = ai_paddle_y;
    float last_ball_x = ball_x;
    float last_ball_y = ball_y;

    if (digitalRead(BUTTON_UP_PIN) == LOW) {
      player_paddle_y -= PADDLE_SPEED;
      if (player_paddle_y < 0) player_paddle_y = 0;
    }
    if (digitalRead(BUTTON_DOWN_PIN) == LOW) {
      player_paddle_y += PADDLE_SPEED;
      if (player_paddle_y > SCREEN_HEIGHT - PADDLE_HEIGHT) player_paddle_y = SCREEN_HEIGHT - PADDLE_HEIGHT;
    }
    if (ai_paddle_y + (PADDLE_HEIGHT / 2) < ball_y) {
      ai_paddle_y += PADDLE_SPEED;
    }
    if (ai_paddle_y + (PADDLE_HEIGHT / 2) > ball_y) {
      ai_paddle_y -= PADDLE_SPEED;
    }
    ball_x += ball_x_speed;
    ball_y += ball_y_speed;
    if (ball_y <= 0 || ball_y >= SCREEN_HEIGHT - BALL_SIZE) {
      ball_y_speed = -ball_y_speed;
    }
    if (ball_x <= player_paddle_x + PADDLE_WIDTH && ball_x >= player_paddle_x &&
        ball_y >= player_paddle_y && ball_y <= player_paddle_y + PADDLE_HEIGHT) {
      ball_x_speed = -ball_x_speed;
    }
    if (ball_x >= ai_paddle_x - BALL_SIZE && ball_x <= ai_paddle_x &&
        ball_y >= ai_paddle_y && ball_y <= ai_paddle_y + PADDLE_HEIGHT) {
      ball_x_speed = -ball_x_speed;
    }
    if (ball_x < 0) {
      ai_score++;
      resetBall();
      drawScore();
    }
    if (ball_x > SCREEN_WIDTH) {
      player_score++;
      resetBall();
      drawScore();
    }
    tft.fillRect(player_paddle_x, last_player_paddle_y, PADDLE_WIDTH, PADDLE_HEIGHT, TFT_BLACK);
    tft.fillRect(ai_paddle_x, last_ai_paddle_y, PADDLE_WIDTH, PADDLE_HEIGHT, TFT_BLACK);
    tft.fillRect(last_ball_x, last_ball_y, BALL_SIZE, BALL_SIZE, TFT_BLACK);
    tft.fillRect(player_paddle_x, player_paddle_y, PADDLE_WIDTH, PADDLE_HEIGHT, TFT_WHITE);
    tft.fillRect(ai_paddle_x, ai_paddle_y, PADDLE_WIDTH, PADDLE_HEIGHT, TFT_WHITE);
    tft.fillRect(ball_x, ball_y, BALL_SIZE, BALL_SIZE, TFT_CYAN);
    delay(10);
  }
}
