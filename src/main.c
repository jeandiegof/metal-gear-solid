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
#include "inc/vector_enemy.h"
/* end dbg */


int main(void)
{
  InitWindow();

//   struct timespec tim, tim2;
//   tim.tv_sec = 1;
//   tim.tv_nsec = 0;
//   //100000000L = 100ms
//   //500000000L = 500ms

//   Map map;

//   LoadMapFromFile(&map);

//   Point origin = {40,18};

//   Enemy *enemy = NewEnemy(ANGLE_90, 3, &origin, &map);

//  // for(uint16_t i = 0; i < 60; i++)
//  // {
//  //   EnemyMove(&map, enemy);

//  //   DebugPrintMap(&map);

//  //   refresh();

//  //   nanosleep(&tim , &tim2);
//  // }

//   // DebugPrintMap(&map);

//  ShowEnemy(enemy, &map);

// //  DebugEnemySightFullLines(enemy);

// //  DebugEnemySightInstantLines(enemy);

//   refresh();

//   DestroyEnemy(enemy);

//   while(1);

//  // Restore normal terminal behavior
//   endwin();
// }

  Game *game = NewGame();

  MENU *menu;
  WINDOW *window_menu;
  PANEL *panel_menu;
  ScreenMenuInit(&menu, &window_menu, &panel_menu);
  hide_panel(panel_menu);

  Map map;
  LoadMapFromFile(&map);
  LoadObjectsFromMap(&map);

  VectorEnemy *vector_enemy = NewVectorEnemy();
  Enemy *new_enemy;  
  Enemy *aux_enemy;

  for (int i = 0; i < map.object.enemy_free_index; ++i)
  {
     new_enemy = NewEnemy(EnemySortAngle(), 2, &(map.object.enemy[i]), &map);
     VectorEnemyAppend(new_enemy, vector_enemy);
  }

  struct timespec tim, tim2;
  tim.tv_sec = 0;
  tim.tv_nsec = 10000000L;
  //100000000L = 100ms
  //500000000L = 500ms

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
  uint8_t game_cycles = 0;

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
    // cycles_start = clock();

    switch(game->actual_screen) {
      case SCREEN_MENU:
        //  menu_controller
        game->actual_screen = MenuManager(&menu);
        break;
      case SCREEN_GAME:
        // game_controller
        if((game_cycles % 4) == 0) {
          game->actual_screen = HeroManager(&map, &hero);
        }
        if((game_cycles % 16) == 0) {
          for (int i = 0; i < vector_enemy->length; ++i)
          {
            aux_enemy = VectorEnemyGetByIndex(i, vector_enemy);
            EnemyMove(&map, aux_enemy);
            if(map.matrix[hero.base.point.y][hero.base.point.x] == '@' ||
               map.matrix[hero.base.point.y][hero.base.point.x] == '.')
            {
              map.matrix[map.object.hero_origin.y][map.object.hero_origin.x] = 'o';
              hero.base.point = map.object.hero_origin;
              if(--hero.life == 0) {
                game->actual_screen == GAME_OVER;
              }
            }
          }
        }
        ScreenGameMapUpdate(&map, &window_map);
        ScreenGameStatusUpdate(&hero, game_state, &window_status);
        break;
      case SCREEN_RANKING:
        getch();
        game->actual_screen = SCREEN_MENU;
        break;
      case SCREEN_GAME_OVER:
      case SCREEN_GAME_COMPLETE:
        if(getch() == 27) {
          sprintf(player.name, "Jean");
          player.score = hero.score;
          LoadRankingFromFile(entry, &ranking_entries);
          AddEntryOnRanking(entry, player, &ranking_entries);
          AddRankingOnFile(entry, ranking_entries);
          game->actual_screen = SCREEN_MENU;
        }
        break;
      case SCREEN_EXIT_GAME:
        DestroyGame(game);
        endwin();
        exit(0);
        break;
    }
    ScreenGameUpdate();
    // TimeManager(cycles_start, &game_cycles);
    nanosleep(&tim , &tim2);
    if(++game_cycles == 255)
    {
      game_cycles = 0;
    }
  }
  // REMEMBER TO FREE THE MEMORY USED W/ WINDOWS, PANELS, MENUS, etc
  endwin();
}