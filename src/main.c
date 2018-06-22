#include <math.h>
#include <ncursesw/ncurses.h>
#include <time.h>
#include <unistd.h>

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
#include "inc/timer.h"
#include "inc/dart.h"
/* end dbg */

int main(void)
{
  InitWindow();
  
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
  RankingEntry entry[11];
  RankingEntry player;
  uint8_t ranking_entries;

  clock_t cycles_start;
  uint8_t game_cycles;

  Dart dart;
  char c;
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
          LoadMapFromFile(&map);
          LoadObjectsFromMap(&map);
          ResetHero(&hero, &map.object.hero);
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

          ScreenRankingUpdate(entry, &window_ranking);
          ScreenGameUpdate();
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
    cycles_start = clock();
    switch(game->actual_screen) {
      case SCREEN_MENU:
        //  menu_controller
        game->actual_screen = MenuManager(&menu);
        break;
      case SCREEN_GAME:
        // game_controller
        if(game_cycles % 4 == 0) {
          game->actual_screen = HeroManager(&map, &hero);
        }
        /*
        DartInit(&dart, hero, hero.last_direction);
        DartEvaluatePosition(&map, &dart, DartPointToCheck(dart));
        ScreenGameMapUpdate(&map, &window_map);
        ScreenGameStatusUpdate(&hero, game_state, &window_status);
        */
        break;
      case SCREEN_RANKING:
        getch();
        game->actual_screen = SCREEN_MENU;
        break;
      case SCREEN_GAME_OVER:
      case SCREEN_GAME_COMPLETE:
        sprintf(player.name, "Jean");
        player.score = hero.score;
        LoadRankingFromFile(entry, &ranking_entries);
        AddEntryOnRanking(entry, player, &ranking_entries);
        AddRankingOnFile(entry, ranking_entries);
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
    TimeManager(cycles_start, &game_cycles);
  }
  // REMEMBER TO FREE THE MEMORY USED W/ WINDOWS, PANELS, MENUS, etc
  endwin();
}