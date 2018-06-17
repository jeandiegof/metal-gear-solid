#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H

#include "inc/window.h"

#define WINDOW_OFFSET                 2
#define WINDOW_GAME_STATUS_LINES      3
#define WINDOW_GAME_STATUS_COLUMNS    80
#define WINDOW_GAME_MAP_LINES         25       
#define WINDOW_GAME_MAP_COLUMNS       80

typedef struct GameInformation {
  uint8_t remaining_lifes;
  uint8_t darts;
  uint8_t status;
  uint16_t score;
} GameInformation;

void ScreenGameStatusInit(WINDOW **window, PANEL **panel);
void ScreenGameMapInit(WINDOW **window, PANEL **panel);
void ScreenGameUpdate();
void ScreenGameStatusUpdate(GameInformation *game_status, WINDOW **window);

#endif