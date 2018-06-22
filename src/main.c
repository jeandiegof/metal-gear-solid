#include <math.h>
#include <ncursesw/ncurses.h>

#include "inc/rectangle.h"
#include "inc/window.h"
#include "inc/enemy.h"
#include "inc/display.h"
#include "inc/detection.h"

/* dbg */
#include "inc/map_manager.h"
#include "inc/debug.h"
#include "inc/screen_game.h"
/* end dbg */


int main(void)
{
  InitWindow();

  Map map;

  LoadMapFromFile(&map);

  Point origin = {40,18};

  Enemy *enemy = NewEnemy(ANGLE_90, 3, &origin, &map);

  DebugPrintMap(&map);

//  mvprintw(9, 34, U_DOTLINE_H);

  ShowEnemy(enemy, &map);

//  DebugEnemySightFullLines(enemy);

//  DebugEnemySightInstantLines(enemy);

  refresh();

  DestroyEnemy(enemy);

  while(1);

 // Restore normal terminal behavior
  endwin();
}
