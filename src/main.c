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
#include "inc/keyboard_manager.h"
#include "inc/hero.h"
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
    
  GameInformation game_status;
  game_status.remaining_lifes = 3;
  game_status.darts = 5;
  game_status.status = 1;
  game_status.score = 0;

  WINDOW *window_status;
  WINDOW *window_map = NULL;
  PANEL *panel_status;
  PANEL *panel_map = NULL;

  ScreenGameStatusInit(&window_status, &panel_status);
  ScreenGameStatusUpdate(&game_status, &window_status);
  ScreenGameUpdate();

  ScreenGameMapInit(&window_map, &panel_map);
  ScreenGameMapUpdate(&map, &window_map);
  ScreenGameUpdate();
  
  Hero hero;
  hero.base.point.x = map.object.hero.x+MAP_OFFSET_X;
  hero.base.point.y = map.object.hero.y+MAP_OFFSET_Y;
  mvwprintw(window_map, 0, 5, "%d %d", hero.base.point.x, hero.base.point.y);
  
  char c;
  while(1) {
    if(kbhit()) {
      c = getch();
      switch(c) {
        case 'a':
          MoveHero(&map, &hero, LEFT);
          break;
        case 's':
          MoveHero(&map, &hero, DOWN);
          break;
        case 'd':
          MoveHero(&map, &hero, RIGHT);
          break;
        case 'w':
          MoveHero(&map, &hero, UP);
          break;
      }
      mvwprintw(window_map, 0, 0, "%c", c);
      LoadObjectsFromMap(&map);
      hero.base.point.x = map.object.hero.x+MAP_OFFSET_X;
      hero.base.point.y = map.object.hero.y+MAP_OFFSET_Y;
      ScreenGameMapUpdate(&map, &window_map);
      ScreenGameUpdate();
    }
  }

  while(1);
  endwin();
}
