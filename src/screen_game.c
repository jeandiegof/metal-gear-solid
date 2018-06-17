#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include "inc/screen_game.h"
#include "inc/map_manager.h"

void ScreenGameStatusInit(WINDOW **window, PANEL **panel) {
  *window = CreateNewWindow(WINDOW_GAME_STATUS_LINES+WINDOW_OFFSET,
                           WINDOW_GAME_STATUS_COLUMNS+WINDOW_OFFSET,
                           0, 0);
  *panel = CreateNewPanel(*window);
}

void ScreenGameMapInit(WINDOW **window, PANEL **panel) {
  *window = CreateNewWindow(WINDOW_GAME_MAP_LINES+WINDOW_OFFSET,
                           WINDOW_GAME_MAP_COLUMNS+WINDOW_OFFSET,
                           5, 0);
  *panel = CreateNewPanel(*window);
}

void ScreenGameStatusUpdate(const Hero *hero, GameState game_state, WINDOW **window) {
  mvwprintw(*window, 1, 1, "Vidas: ");
  for (int i = 0; i < hero->life; ++i)
  {
    // TODO: change it to the heart unicode char
    mvwprintw(*window, 1, 9+i, "L  ");
  }

  mvwprintw(*window, 2, 1, "Pontos: %05d", hero->score);
  
  mvwprintw(*window, 3, 1, "Dardos: ");
  for (int i = 0; i < hero->ammo; ++i)
  {
    mvwprintw(*window, 3, 9+i, "|    ");
  }

  if(game_state) {
    mvwprintw(*window, 1, 25, "-= Running =-");
  } else {
    mvwprintw(*window, 1, 25, "-= Paused =- ");
  }
}

void ScreenGameMapUpdate(Map *map, WINDOW **map_window) {
  wmove(*map_window, 1, 1);
  for (uint16_t i = 0; i < MAX_HEIGHT; ++i)
  {
    for (int j = 0; j < MAX_LENGTH; ++j)
    {
      wprintw(*map_window, "%c", map->matrix[i][j]);
    }
    wmove(*map_window, 2+i, 1);
  }
}

void ScreenGameUpdate() {
  update_panels();
  doupdate();
}