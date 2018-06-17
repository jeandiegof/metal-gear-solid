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
    
  GameState game_state = RUNNING;

  WINDOW *window_status = NULL;
  WINDOW *window_map = NULL;
  PANEL *panel_status = NULL;
  PANEL *panel_map = NULL;

  Hero hero = NewHero(3, 5, &map.object.hero);

  ScreenGameStatusInit(&window_status, &panel_status);
  ScreenGameStatusUpdate(&hero, game_state, &window_status);
  ScreenGameUpdate();

  ScreenGameMapInit(&window_map, &panel_map);
  ScreenGameMapUpdate(&map, &window_map);
  ScreenGameUpdate();
  
  
  char c;
  while(1) {
    if(kbhit()) {
      mvwprintw(window_map, 0, 5, "%03d %03d", hero.base.point.x, hero.base.point.y);
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
        case 'p':
          game_state = PAUSED;
          break;
        case 'r':
          game_state = RUNNING;
          break;
      }
      mvwprintw(window_map, 0, 0, "%c", c);
      ScreenGameMapUpdate(&map, &window_map);
      ScreenGameStatusUpdate(&hero, game_state, &window_status);
      ScreenGameUpdate();
    }
  }

  while(1);
  endwin();
}
