#ifndef GAME_BASE_H
#define GAME_BASE_H

typedef enum GameState {
  PAUSED = 0,
  RUNNING,
  GAME_OVER,
  GAME_COMPLETE,
  MOVEMENT_ALLOWED,
  MOVEMENT_FORBIDDEN,
} GameState;

typedef enum Direction {
  UP,
  DOWN,
  RIGHT,
  LEFT
} Direction;

typedef struct GameInformation {
  uint8_t remaining_lifes;
  uint8_t darts;
  uint8_t status;
  uint16_t score;
} GameInformation;

#endif // GAME_BASE_H