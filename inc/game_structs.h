#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include <ncursesw/menu.h>
#include <ncursesw/panel.h>
#include <time.h>

#include "inc/dart_struct.h"
#include "inc/game_cycles.h"
#include "inc/game_definitions.h"
#include "inc/game_enums.h"
#include "inc/hero.h"
#include "inc/manager_map.h"
#include "inc/ranking.h"
#include "inc/vector_enemy.h"

#define DARTS_MAX_NUMBER_ON_MAP 10

typedef struct GameWindow
{
  WINDOW *title;
  WINDOW *menu;
  WINDOW *status;
  WINDOW *paused;
  WINDOW *map;
  WINDOW *save;
  WINDOW *ranking;
  WINDOW *game_over;
  WINDOW *game_complete;
}GameWindow;
//===================================================================

typedef struct GamePanel
{
  PANEL *title;
  PANEL *menu;
  PANEL *status;
  PANEL *paused;
  PANEL *map;
  PANEL *save;
  PANEL *ranking;
  PANEL *game_over;
  PANEL *game_complete;
}GamePanel;
//===================================================================

typedef struct Game
{
  GameCycles *cycles;

  GameState state;

  GameScreen actual_screen;

  GameScreen last_screen;

  GameWindow window;

  GamePanel panel;

  MENU *menu;

  MENU *menu_paused;

  Map map;

  Hero *hero;

  Dart *vector_darts[DARTS_MAX_NUMBER_ON_MAP];

  uint8_t darts_index;

  VectorEnemy *vector_enemy;

  Ranking rank;

} Game;
//===================================================================

#endif // GAME_STRUCTS_H
