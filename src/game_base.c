#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include "inc/game_base.h"

Game *NewGame() {
  Game *game = malloc(sizeof(Game));
  game->actual_screen = SCREEN_MENU;
  game->last_screen = SCREEN_GAME_OVER;
  return game;
}

void DestroyGame(Game *game) {
  free(game);
}