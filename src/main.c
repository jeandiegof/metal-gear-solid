#include <math.h>
#include <ncursesw/ncurses.h>
#include <time.h>

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

  struct timespec tim, tim2;
  tim.tv_sec = 1;
  tim.tv_nsec = 0;
  //100000000L = 100ms
  //500000000L = 500ms

  Map map;

  LoadMapFromFile(&map);

  Point origin = {40,18};

  Enemy *enemy = NewEnemy(ANGLE_90, 2, &origin, &map);

//  for(uint16_t i = 0; i < 30; i++)
//  {
//    EnemyMove(&map, enemy);

//    DebugPrintMap(&map);

//    refresh();

//    nanosleep(&tim , &tim2);
//  }

  DebugPrintMap(&map);

//  ShowEnemy(enemy, &map);

//  DebugEnemySightFullLines(enemy);

//  DebugEnemySightInstantLines(enemy);

  refresh();

  DestroyEnemy(enemy);

  while(1);

 // Restore normal terminal behavior
  endwin();
}
