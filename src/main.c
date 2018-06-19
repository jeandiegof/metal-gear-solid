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
#include "inc/screen_menu.h"
#include "inc/game_base.h"
#include "inc/ranking.h"
/* end dbg */

int main(void)
{
  InitWindow();
  
  // Map map;
  // LoadMapFromFile(&map);
  // LoadObjectsFromMap(&map);
    
  // GameState game_state = RUNNING;

  // WINDOW *window_status = NULL;
  // WINDOW *window_map = NULL;
  // PANEL *panel_status = NULL;
  // PANEL *panel_map = NULL;

  // Hero hero = NewHero(3, 5, &map.object.hero);

  // ScreenGameStatusInit(&window_status, &panel_status);
  // ScreenGameStatusUpdate(&hero, game_state, &window_status);
  // ScreenGameUpdate();

  // ScreenGameMapInit(&window_map, &panel_map);
  // ScreenGameMapUpdate(&map, &window_map);
  // ScreenGameUpdate();
  
  
  // char c;
  // while(1) {
  //   if(kbhit()) {
  //     mvwprintw(window_map, 0, 5, "%03d %03d", hero.base.point.x, hero.base.point.y);
  //     c = getch();
  //     switch(c) {
  //       case 'a':
  //         MoveHero(&map, &hero, LEFT);
  //         break;
  //       case 's':
  //         MoveHero(&map, &hero, DOWN);
  //         break;
  //       case 'd':
  //         MoveHero(&map, &hero, RIGHT);
  //         break;
  //       case 'w':
  //         MoveHero(&map, &hero, UP);
  //         break;
  //       case 'p':
  //         game_state = PAUSED;
  //         break;
  //       case 'r':
  //         game_state = RUNNING;
  //         break;
  //     }
  //     mvwprintw(window_map, 0, 0, "%c", c);
  //     ScreenGameMapUpdate(&map, &window_map);
  //     ScreenGameStatusUpdate(&hero, game_state, &window_status);
  //     ScreenGameUpdate();
  //   }
  // }

  /* old menu
  MENU *menu;
  WINDOW *window_menu;
  PANEL *panel_menu;
  
  menu = CreateMenu(&window_menu);
  panel_menu = CreateMenuNewPanel(window_menu);

  char opt;
  while((opt = getch()) != 'z') {
    switch(opt) {
      case 's':
        menu_driver(menu, REQ_DOWN_ITEM);
        break;
      case 'w':
        menu_driver(menu, REQ_UP_ITEM);
        break;
      case 10:

        break;
    }
    ScreenGameUpdate();
  }
  */

  Game *game = NewGame();
  game->actual_screen = SCREEN_RANKING;

  MENU *menu;
  WINDOW *window_menu;
  PANEL *panel_menu;
  ScreenMenuInit(&menu, &window_menu, &panel_menu);
  hide_panel(panel_menu);

  Map map;
  LoadMapFromFile(&map);
  LoadObjectsFromMap(&map);
  
  // TODO: stop using GameState var and change it to Game struct
  GameState game_state = RUNNING;
  Hero hero = NewHero(3, 5, &map.object.hero);
    
  WINDOW *window_status;
  PANEL *panel_status;
  ScreenGameStatusInit(&window_status, &panel_status);
  ScreenGameStatusUpdate(&hero, game_state, &window_status);
  hide_panel(panel_status);
  
  WINDOW *window_map;
  PANEL *panel_map;
  ScreenGameMapInit(&window_map, &panel_map);
  ScreenGameMapUpdate(&map, &window_map);
  hide_panel(panel_map);
  
  // init das telas;
  RankingEntry entry[10];
  uint8_t count;
  RankingEntry this;
  sprintf(this.name, "EITA");
  this.score = 7;

  char c;
  char opt;
  while(1) {
    if(game->actual_screen != game->last_screen) {
      game->last_screen = game->actual_screen;
      switch(game->actual_screen) {
        case SCREEN_MENU:
          show_panel(panel_menu);
          hide_panel(panel_status);
          hide_panel(panel_map);
          break;
        case SCREEN_GAME:
          show_panel(panel_map);
          show_panel(panel_status);
          hide_panel(panel_menu);
          break;
        case SCREEN_RANKING:
          break;
        case SCREEN_GAME_OVER:
          break;
        case SCREEN_GAME_COMPLETE:
          break;
        case SCREEN_EXIT_GAME:
          break;
        default:
          game->actual_screen = SCREEN_MENU;
      }
      ScreenGameUpdate();
    }
    switch(game->actual_screen) {
      case SCREEN_MENU:
        //  menu_controller
        game->actual_screen = MenuManager(&menu);
        break;
      case SCREEN_GAME:
        // game_controller
        game->actual_screen = HeroManager(&map, &hero);
        ScreenGameMapUpdate(&map, &window_map);
        ScreenGameStatusUpdate(&hero, game_state, &window_status);
        break;
      case SCREEN_RANKING:
        
        LoadRankingFromFile(entry, &count);
        DebugRanking(entry, count);
        printw("\n\n");
        SortRanking(entry, count);
        DebugRanking(entry, count);
        getch();


        // if(count < 10) {
        //   entry[count] = this;
        //   AddEntriesOnRanking(entry, count);
        // } else {
        //   entry[9] = this;
        //   AddEntriesOnRanking(entry, 10);
        // }

        
        
        // sprintf(entry[0].name, "A");
        // entry[0].score = 1;
        // sprintf(entry[1].name, "B");
        // entry[1].score = 2;
        // sprintf(entry[2].name, "C");
        // entry[2].score = 3;
        // sprintf(entry[3].name, "D");
        // entry[3].score = 4;
        // sprintf(entry[4].name, "E");
        // entry[4].score = 5;
        // sprintf(entry[5].name, "F");
        // entry[5].score = 6;
        // sprintf(entry[6].name, "G");
        // entry[6].score = 7;
        // sprintf(entry[7].name, "H");
        // entry[7].score = 8;
        // sprintf(entry[8].name, "I");
        // entry[8].score = 9;
        // sprintf(entry[9].name, "J");
        // entry[9].score = 10;


        // printw("\n\n");
        // printw("\n\n");
        // AddEntriesOnRanking(entry, 10);
        // DebugRanking(entry, count);
        // SortRanking(entry, count);
        // DebugRanking(entry, count);
        
        getch();

        endwin();
        exit(0);
        break;
      case SCREEN_GAME_OVER:
        endwin();
        exit(0);  
        break;
      case SCREEN_GAME_COMPLETE:
        break;
      case SCREEN_EXIT_GAME:
        endwin();
        exit(0);
        break;
    }
    ScreenGameUpdate();
  }
  // REMEMBER TO FREE THE MEMORY USED W/ WINDOWS, PANELS, MENUS, etc
  DestroyGame(game);
  while(1);
  endwin();
}
