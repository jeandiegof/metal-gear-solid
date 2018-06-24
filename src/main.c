
#include <math.h>
#include <ncursesw/ncurses.h>

#include <unistd.h>

#include "inc/rectangle.h"
#include "inc/window.h"
#include "inc/enemy.h"
#include "inc/display.h"
#include "inc/detection.h"

#include "inc/manager_map.h"
#include "inc/debug.h"
#include "inc/manager_keyboard.h"
#include "inc/hero.h"
#include "inc/game_base.h"
#include "inc/ranking.h"
#include "inc/dart.h"
#include "inc/vector_enemy.h"
#include "inc/game_init.h"


int main(void)
{
  InitWindow();

  Game *game = NewGame();

  while(1)
  {
    GameCheckScreenMode(game);

    GameActiveScreenMode(game);
  }
}
