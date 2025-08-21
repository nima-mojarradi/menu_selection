#ifndef PING_PONG_H
#define PING_PONG_H

#include <SPI.h>
#include <TFT_eSPI.h>

// توابع
extern TFT_eSPI tft;
void runPong();

// متغیرها و ثوابت
const int BUTTON_UP_PIN = 22;
const int BUTTON_DOWN_PIN = 21;
const int BUTTON_SELECT_PIN = 23;
const int SCREEN_WIDTH = 240;
const int SCREEN_HEIGHT = 320;
const int PADDLE_WIDTH = 5;
const int PADDLE_HEIGHT = 40;
const int PADDLE_SPEED = 1;
const int BALL_SIZE = 5;
extern float ball_x_speed;
extern float ball_y_speed;
extern float player_paddle_x;
extern float player_paddle_y;
extern float ai_paddle_x;
extern float ai_paddle_y;
extern float ball_x;
extern float ball_y;
extern int player_score;
extern int ai_score;

void drawScore();
void resetBall();

#endif
