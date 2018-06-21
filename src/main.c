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
#include "inc/screen_game_over.h"
#include "inc/screen_game_complete.h"
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
  //game->actual_screen = SCREEN_RANKING;

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
  
  WINDOW *window_ranking;
  PANEL *panel_ranking;
  ScreenRankingInit(&window_ranking, &panel_ranking);
  hide_panel(panel_ranking);
  
  WINDOW *window_game_over;
  PANEL *panel_game_over;
  ScreenGameOverInit(&window_game_over, &panel_game_over);
  hide_panel(panel_game_over);

  WINDOW *window_game_complete;
  PANEL *panel_game_complete;
  ScreenGameCompleteInit(&window_game_complete, &panel_game_complete);
  hide_panel(panel_game_complete);


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
          hide_panel(panel_ranking);
          hide_panel(panel_game_over);
          hide_panel(panel_game_complete);
          break;
        case SCREEN_GAME:
          ResetHero(&hero, &map.object.hero);
          // TODO: remove it from here:
          ScreenGameMapInit(&window_map, &panel_map);
          ScreenGameMapUpdate(&map, &window_map);
          ScreenGameStatusUpdate(&hero, game_state, &window_status);
          show_panel(panel_map);
          show_panel(panel_status);
          hide_panel(panel_menu);
          hide_panel(panel_ranking);
          hide_panel(panel_game_over);
          hide_panel(panel_game_complete);
          break;
        case SCREEN_RANKING:
          hide_panel(panel_map);
          hide_panel(panel_status);
          hide_panel(panel_menu);
          show_panel(panel_ranking);
          hide_panel(panel_game_over);
          hide_panel(panel_game_complete);
          break;
        case SCREEN_GAME_OVER:
          hide_panel(panel_map);
          hide_panel(panel_status);
          hide_panel(panel_menu);
          show_panel(panel_game_over);
          hide_panel(panel_game_complete);
          break;
        case SCREEN_GAME_COMPLETE:
          hide_panel(panel_map);
          hide_panel(panel_status);
          hide_panel(panel_menu);
          hide_panel(panel_game_over);
          show_panel(panel_game_complete);
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
        ScreenRankingUpdate(entry, &window_ranking);
        ScreenGameUpdate();
        getch();
        game->actual_screen = SCREEN_MENU;
        break;
      case SCREEN_GAME_OVER:
        getch();
        getch();
        game->actual_screen = SCREEN_MENU;
        break;
      case SCREEN_GAME_COMPLETE:
        getch();
        getch();
        game->actual_screen = SCREEN_MENU;
        break;
      case SCREEN_EXIT_GAME:
        DestroyGame(game);
        endwin();
        exit(0);
        break;
    }
    ScreenGameUpdate();
  }
  // REMEMBER TO FREE THE MEMORY USED W/ WINDOWS, PANELS, MENUS, etc
  while(1);
  endwin();
}
