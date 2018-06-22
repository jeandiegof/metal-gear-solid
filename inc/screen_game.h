#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H

#include "inc/window.h"
#include "inc/map_manager.h"
#include "inc/game_base.h"
#include "hero.h"

#define WINDOW_OFFSET                 2
#define WINDOW_GAME_STATUS_LINES      3
#define WINDOW_GAME_STATUS_COLUMNS    80
#define WINDOW_GAME_MAP_LINES         25       
#define WINDOW_GAME_MAP_COLUMNS       80

void ScreenGameStatusInit(WINDOW **window, PANEL **panel);
void ScreenGameStatusUpdate(const Hero *hero, GameState game_state, WINDOW **window);
void ScreenGameMapInit(WINDOW **window, PANEL **panel);
void ScreenGameMapUpdate(Map *map, WINDOW **map_window);
void ScreenGameUpdate();

#endif // SCREEN_GAME_H