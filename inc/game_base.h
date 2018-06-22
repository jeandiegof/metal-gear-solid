#ifndef GAME_BASE_H
#define GAME_BASE_H

#include <ncursesw/menu.h>

typedef enum GameState {
  PAUSED = 0,
  RUNNING,
  GAME_OVER,
  GAME_COMPLETE,
  MOVEMENT_ALLOWED,
  MOVEMENT_FORBIDDEN,
} GameState;

typedef enum Screen {
  SCREEN_NAME,
  SCREEN_MENU,
  SCREEN_GAME,
  SCREEN_RANKING,
  SCREEN_GAME_OVER,
  SCREEN_GAME_COMPLETE,
  SCREEN_EXIT_GAME,
} Screen;

typedef struct Game {
  GameState state;
  Screen actual_screen;
  Screen last_screen;
} Game;

typedef enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT
} Direction;

Game *NewGame();
void DestroyGame(Game *game);

#endif // GAME_BASE_H