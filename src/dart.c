#include "inc/dart.h"

#include <stdlib.h>

#include "inc/manager_keyboard.h"


static GameState DartEvaluatePosition(Map *map, Dart *dart, Point p);
//===================================================================

static GameState DartMove(Map *map, Dart *dart, Point p);
//===================================================================

static Point DartPointToCheck(Dart *dart);
//===================================================================


void DartCreate(Game *game)
{
  if(game->darts_index >= DARTS_MAX_NUMBER_ON_MAP || game->hero->ammo <= 0)
  {
    return;
  }

  Dart *new_dart = game->vector_darts[game->darts_index];
  game->darts_index++;

  game->hero->ammo--;
  new_dart->steps = 0;
  new_dart->active = 1;
  new_dart->point = game->hero->base.point;
  new_dart->direction = game->hero->last_direction;

  mvprintw(5, 20, "%03d %03d", new_dart->point.x, new_dart->point.y);
  refresh();
}
//===================================================================


void DartManager(Game *game)
{
  Dart *aux_dart;

  Point p;

  GameState game_state;

  for(uint8_t i = 0; i < game->darts_index ; i++)
  {
    aux_dart = game->vector_darts[i];

    p = DartPointToCheck(aux_dart);

    game_state = DartMove(&(game->map), aux_dart, p);

    if(aux_dart->active == 0)
    {
      Dart transfer_dart;
      for(uint8_t k = 1; k < game->darts_index; k++)
      {
        transfer_dart = *(game->vector_darts[k]);
        *(game->vector_darts[k-1]) = transfer_dart;
      }
      game->darts_index--;
    }

    if(game_state == ENEMY_FOUND)
    {
      Enemy *hit_enemy = VectorEnemyGetByPoint(&p, game->vector_enemy);
      EnemyHitSignal(&(game->map), hit_enemy);
    }
  }
}
//===================================================================


void DartReset(const Point *point, Dart *dart)
{
  dart->steps = 0;
  dart->active = 0;
  dart->erase_sight = false;
  dart->point = *point;
}
//===================================================================


Dart *NewDart(const Point *point)
{
  Dart *dart = malloc(sizeof(Dart));

  DartReset(point, dart);

  return dart;
}
//===================================================================


void DestroyDart(Dart *dart)
{
  free(dart);
}
//===================================================================


static GameState DartEvaluatePosition(Map *map, Dart *dart, Point p)
{
  // Make sure it won't erase hero position.
  if(dart->steps > 0)
  {
    // Erase actual dart position from matrix.
    map->matrix[dart->point.y][dart->point.x] = ' ';
  }

  switch(map->matrix[p.y][p.x])
  {
    case ' ':
      if(dart->erase_sight)
      {
        dart->erase_sight  = false;
        map->matrix[dart->point.y][dart->point.x] = '.';
      }

      if(++dart->steps == 12)
      {
        return DART_VANISH;
      }
      return MOVEMENT_ALLOWED;
      break;

    case '.':
      if(dart->erase_sight)
      {
        dart->erase_sight  = false;
        map->matrix[dart->point.y][dart->point.x] = '.';
      }

      dart->erase_sight = true;

      if(++dart->steps == 12)
      {
        return DART_VANISH;
      }
      return MOVEMENT_ALLOWED;
      break;

    case '#':
    case '%':
    case 'x':
    case 'K':
    case 'Z':
      return DART_VANISH;
      break;

    case '0':
      return HOSTAGE_FOUND;
      break;

    case '@':
      return ENEMY_FOUND;
      break;
  }

  //Just to avoid compiler warning.
  return MOVEMENT_FORBIDDEN;
}
//===================================================================


static GameState DartMove(Map *map, Dart *dart, Point p)
{
  GameState game_state = DartEvaluatePosition(map, dart, p);

  switch(game_state)
  {
    case MOVEMENT_ALLOWED:
      map->matrix[p.y][p.x] = '-';
      dart->point = p;
      break;

    case ENEMY_FOUND:
      map->matrix[p.y][p.x] = 'Z';
      dart->active = 0;
      dart->erase_sight  = false;
      return ENEMY_FOUND;
      break;

    case DART_VANISH:
      dart->active = 0;
      dart->erase_sight  = false;
      break;

    case HOSTAGE_FOUND:
      map->matrix[p.y][p.x] = ' ';
      dart->active = 0;
      dart->erase_sight  = false;
      break;

      // Just to avoid compiler warning.
    case RUNNING:
    case PAUSED:
    case GAME_COMPLETE:
    case MOVEMENT_FORBIDDEN:
      break;
  }
  return RUNNING;
}
//===================================================================


static Point DartPointToCheck(Dart *dart)
{
  Point p = dart->point;

  switch(dart->direction) {
    case UP:
      if(--p.y < 0) {
        p.y = 0;
      }
      break;
    case DOWN:
      if(++p.y > 25) {
        p.y = 25;
      }
      break;
    case LEFT:
      if(--p.x < 0) {
        p.x = 0;
      }
      break;
    case RIGHT:
      if(++p.x > 80) {
        p.x = 80;
      }
      break;
  }
  return p;
}
//===================================================================

