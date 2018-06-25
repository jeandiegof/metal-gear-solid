#include "inc/game_base.h"

#include <stdlib.h>
#include <time.h>

#include "inc/detection.h"

#include "inc/dart.h"
#include "inc/game_init.h"
#include "inc/game_menu.h"
#include "inc/game_update.h"

#include "inc/manager_keyboard.h"


static void GameRefreshMap(Game *game);
//===================================================================

static void GameInitVectorEnemy(Game *game);
//===================================================================

static void GameScreenGame(Game *game);
//===================================================================



Game *NewGame()
{
  Game *game = malloc(sizeof(Game));

  game->actual_screen = SCREEN_MENU;
  game->last_screen = SCREEN_GAME_OVER;

  game->state = RUNNING;

  game->cycles = NewCycles();

  // Title panel.
  GameInitScreenTitle(game);
  hide_panel(game->panel.title);

  // Menu panel.
  MenuInitScreen(game);
  hide_panel(game->panel.menu);

  // Status panel.
  GameInitScreenStatus(game);
  hide_panel(game->panel.status);

  // Paused panel;
  MenuInitPausedScreen(game);
  hide_panel(game->panel.paused);

  // Map panel.
  GameInitScreenMap(game);
  hide_panel(game->panel.map);

  // Ranking panel.
  GameInitScreenRanking(game);
  hide_panel(game->panel.ranking);

  // Game Over panel.
  GameInitScreenGameOver(game);
  hide_panel(game->panel.game_over);

  // Game Complete panel.
  GameInitScreenGameComplete(game);
  hide_panel(game->panel.game_complete);  

  // Init Ranking.
  switch(RankingLoadFromFile(&(game->rank)))
  {
    case CREATED_FILE:
    case READING_ERROR:
      // makes sure index is reseted.
      game->rank.entries = 0;
      break;

    case CREATED_FILE_FAILL:
      printf("\nFail to create ranking file.\n\n");
      exit(1);
      break;

    case EVERYTHING_OK:
      break;
  }

  // Init Hero.
  game->hero = NewHero(3, 5, &(game->map.object.hero));

  // Init Darts.
  for(uint8_t i = 0; i < DARTS_MAX_NUMBER_ON_MAP; i++)
  {
    game->vector_darts[i] = NewDart(&(game->hero->base.point));
  }
  game->darts_index = 0;

  // Init VectorEnemies
  game->vector_enemy = NewVectorEnemy();

  // Init Map
  GameRefreshMap(game);

  return game;
}
//===================================================================


void DestroyGame(Game *game)
{
  for(uint8_t i = 0; i < DARTS_MAX_NUMBER_ON_MAP; i++)
  {
    DestroyDart(game->vector_darts[i]);
  }

  DestroyCycles(game->cycles);

  DestroyVectorEnemy(game->vector_enemy);

  free(game);
}
//===================================================================


void GameCheckScreenMode(Game *game)
{
  if(game->actual_screen != game->last_screen)
  {
    game->last_screen = game->actual_screen;

    switch(game->actual_screen)
    {
      case SCREEN_MENU:
        show_panel(game->panel.title);
        show_panel(game->panel.menu);

        hide_panel(game->panel.paused);
        hide_panel(game->panel.status);
        hide_panel(game->panel.map);
        hide_panel(game->panel.ranking);
        hide_panel(game->panel.game_over);
        hide_panel(game->panel.game_complete);
        break;

      case SCREEN_GAME:
        switch (game->state)
        {
          case PAUSED:
            game->state = RUNNING;
            break;

          default:
            GameRefreshMap(game);

            HeroReset(game->hero, &(game->map.object.hero));
            GameInitScreenStatus(game);
            GameUpdateScreenStatus(game);

            CyclesInit(GAME_DART_TIME_MS, GAME_ENEMY_TIME_MS,
                       GAME_HERO_TIME_MS, game->cycles);
            break;
        }

        show_panel(game->panel.map);
        show_panel(game->panel.status);

        hide_panel(game->panel.paused);
        hide_panel(game->panel.title);
        hide_panel(game->panel.menu);
        hide_panel(game->panel.ranking);
        hide_panel(game->panel.game_over);
        hide_panel(game->panel.game_complete);
        break;

      case SCREEN_PAUSED:

        show_panel(game->panel.paused);
        break;

      case SCREEN_RANKING:

        RankingLoadFromFile(&(game->rank));
        GameUpdateScreenRanking(game);

        show_panel(game->panel.ranking);

        hide_panel(game->panel.paused);
        hide_panel(game->panel.title);
        hide_panel(game->panel.map);
        hide_panel(game->panel.status);
        hide_panel(game->panel.menu);
        hide_panel(game->panel.game_over);
        hide_panel(game->panel.game_complete);
        break;

      case SCREEN_GAME_OVER:
        show_panel(game->panel.game_over);

        hide_panel(game->panel.paused);
        hide_panel(game->panel.title);
        hide_panel(game->panel.map);
        hide_panel(game->panel.status);
        hide_panel(game->panel.menu);
        hide_panel(game->panel.game_complete);
        break;

      case SCREEN_GAME_COMPLETE:
        show_panel(game->panel.game_complete);

        hide_panel(game->panel.paused);
        hide_panel(game->panel.title);
        hide_panel(game->panel.map);
        hide_panel(game->panel.status);
        hide_panel(game->panel.menu);
        hide_panel(game->panel.game_over);
        break;

      case SCREEN_EXIT_GAME:
        // This is handle in GameActiveScreenMode().
        break;

      default:
        game->actual_screen = SCREEN_MENU;
    }
    GameUpdateScreen();
  }
}
//===================================================================

void GameActiveScreenMode(Game *game)
{
  switch(game->actual_screen)
  {
    case SCREEN_MENU:
      game->actual_screen = MenuManager(game->menu);
      game->state = RUNNING;
      break;

    case SCREEN_GAME:
      GameScreenGame(game);
      break;

    case SCREEN_RANKING:
      if(getch() == 27)
      {
        fflush(stdin);

        game->actual_screen = SCREEN_MENU;
      }
      break;

    case SCREEN_GAME_OVER:
    case SCREEN_GAME_COMPLETE:
      if(getch() == 27)
      {
        fflush(stdin);

        RankingEntry entry;
        sprintf(entry.name, "Hero");
        entry.score = game->hero->score;

        RankingAddEntry(&entry, &(game->rank));
        RankingaSaveOnFile(&(game->rank));

        game->actual_screen = SCREEN_MENU;
      }
      break;

    case SCREEN_EXIT_GAME:
      DestroyGame(game);
      endwin();
      exit(0);
      break;

    case SCREEN_PAUSED:
      game->actual_screen = MenuPausedManager(game->menu_paused);
      break;
  }
  GameUpdateScreen();
}
//===================================================================


static void GameRefreshMap(Game *game)
{
  MapInit(&(game->map));

  GameInitVectorEnemy(game);

  for(uint8_t i = 0; i < DARTS_MAX_NUMBER_ON_MAP; i++)
  {
    DartReset(&(game->hero->base.point), game->vector_darts[i]);
  }
  game->darts_index = 0;

  GameUpdateScreenMap(game);
}
//===================================================================


static void GameInitVectorEnemy(Game *game)
{
  VectorEnemyReset(game->vector_enemy);

  Enemy *new_enemy;
  for (int i = 0; i < game->map.object.enemy_free_index; i++)
  {
     new_enemy = NewEnemy(EnemySortAngle(),
                          2,
                          &(game->map.object.enemy[i]),
                          &(game->map));

     VectorEnemyAppend(new_enemy, game->vector_enemy);
  }

}
//===================================================================

static void GameScreenGame(Game *game)
{  
  if(kbhit())
  {
    char option = getch();
    fflush(stdin);

    // IF enough time has passed THEN check the user input.
    if( CyclesIsTimeUpHero(game->cycles) && game->state != PAUSED)
    {
      // IF is direction THEN move hero.
      game->actual_screen = HeroManager(option, &(game->map), game->hero);

      // IF is space bar THEN creates a dart.
      if(option == 32)
      {
        DartCreate(game);
      }
      GameUpdateScreenGame(game);
    }

    if(option == 'p')
    {
      game->actual_screen = SCREEN_PAUSED;
      game->state = PAUSED;
      GameUpdateScreenStatus(game);
    }
  }

  // IF enough time has passed THEN move all the enemies
  if( CyclesIsTimeUpEnemies(game->cycles) && game->state != PAUSED)
  {
    for (int i = 0; i < game->vector_enemy->length; ++i)
    {
      Enemy *aux_enemy;
      aux_enemy = VectorEnemyGetByIndex(i, game->vector_enemy);

      // Move one enemy. IF is slepping THEN this function don't move the enemy,
      // just increment the enemy->sleep_counter.
      EnemyMove(&(game->map), aux_enemy);

      // IF hero is inside enemy vision THEN call HeroDetectedSignal().
      if( IsPointInEnemy(&(game->hero->base.point), &(game->map)) )
      {
        game->actual_screen = HeroDetectedSignal(&(game->map), game->hero);
      }

      // Workaround: bug where enemy hiddes the key after it is cath the first
      // time.
      if(game->hero->key == 0)
      {
        game->map.matrix[game->map.object.key.y][game->map.object.key.x] = 'K';
      }
    }
    GameUpdateScreenGame(game);
  }

  // IF enough time has passed THEN move all the darts active in the map.
  if( CyclesIsTimeUpDart(game->cycles) && game->state != PAUSED)
  {
    // IF there is darts on the map THEN calls DartManager() and updates
    // the screen.
    if( game->darts_index > 0 )
    {
      DartManager(game);

      GameUpdateScreenGame(game);
    }
  }

  CyclesWait(game->cycles);
}
//===================================================================
