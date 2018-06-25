#include "inc/game_update.h"

#include <ncursesw/ncurses.h>
#include "inc/unicodes.h"
#include "inc/manager_map.h"



void GameUpdateScreen()
{
  update_panels();
  doupdate();
}
//===================================================================


void GameUpdateScreenGame(Game *game)
{
  GameUpdateScreenMap(game);
  GameUpdateScreenStatus(game);
}
//===================================================================


void GameUpdateScreenMap(Game *game)
{
  wmove(game->window.map, 1, 1);
  for (uint16_t i = 0; i < MAX_HEIGHT; ++i)
  {
    for (int j = 0; j < MAX_LENGTH; ++j)
    {
      switch (game->map.matrix[i][j])
      {
        case 'K':
          wprintw(game->window.map, U_KEY);
          break;
        case '%':
          wprintw(game->window.map, U_AMMO);
          break;
        case '0':
          wprintw(game->window.map, U_HOSTAGE);
          break;
        case '@':
          wprintw(game->window.map, U_ENEMY);
          break;
        case 'Z':
          wprintw(game->window.map, U_ENEMY_SLEEP);
          break;
        default:
          wprintw(game->window.map, "%c", game->map.matrix[i][j]);
          break;
      }

    }
    wmove(game->window.map, 2+i, 1);
  }
  wredrawln(game->window.map,0,35);
}
//===================================================================


void GameUpdateScreenRanking(Game *game)
{
  RankingLoadFromFile(&(game->rank));

  // workaround to erase trash numbers.
  mvprintw(5,20,"  ");

  for (int i = 0; i < game->rank.entries; ++i)
  {
    mvwprintw(game->window.ranking, i+5, 8, "%2d. %s", i+1, game->rank.entry[i].name);
    mvwprintw(game->window.ranking, i+5, 25, "%5d", game->rank.entry[i].score);
  }
}
//===================================================================


void GameUpdateScreenStatus(Game *game)
{
  mvwprintw(game->window.status, 1, 1, "Vidas: ");

  for (int i = 0; i < game->hero->life; ++i)
  {
    // TODO: change it to the heart unicode char
    mvwprintw(game->window.status, 1, 9+i, "L  ");
  }

  mvwprintw(game->window.status, 2, 1, "Pontos: %05d", game->hero->score);

  mvwprintw(game->window.status, 3, 1, "Dardos: ");

  if(game->hero->ammo != 0)
  {
    for (int i = 0; i < game->hero->ammo; ++i)
    {
      mvwprintw(game->window.status, 3, 9+i, "|    ");
    }
  }
  else
  {
    mvwprintw(game->window.status, 3, 9, "     ");
  }

  if(game->state)
  {
    mvwprintw(game->window.status, 1, 25, "-= Running =-");
  }
  else
  {
    mvwprintw(game->window.status, 1, 25, "-= Paused =- ");
  }
}
//===================================================================


