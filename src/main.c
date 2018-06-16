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
/* end dbg */

int main(void)
{
  /*
  InitWindow();

  Point origin = {40,10};

  Point test_point = {45, 10};

  Enemy *enemy = NewEnemy(ANGLE_270, 2, &origin);

  if(IsPointInEnemy(&test_point,enemy))
  {
    printw("IN");
  }
  else
  {
    printw("OUT");
  }

  ShowEnemy(enemy);
  ShowPoint(&test_point, "p");

  refresh();

  DestroyEnemy(enemy);

  while(1);

 // Restore normal terminal behavior
  endwin();
  */
  InitWindow();

  Map map;
  LoadMapFromFile(&map);
  LoadObjectsFromMap(&map);
  DebugObjectsFromMap(&map);

  refresh();
  while(1);
  endwin();
}
