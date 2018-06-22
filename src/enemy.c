#include "inc/enemy.h"

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "inc/sight_private.h"
#include "inc/angles.h"
#include "inc/line.h"
#include "inc/detection.h"

static void EnemyEraseFromMatrix(Map *map, Enemy *enemy);
//===================================================================

static Translation EnemySortAction();
//===================================================================

static uint8_t EnemySortSteps();
//===================================================================

static void EnemyTransferTomMatrix(Map *map, Enemy *enemy);
//===================================================================



void DestroyEnemy(Enemy *enemy)
{
  if(enemy->sight_active)
    DestroySight(enemy->sight);

  free(enemy);
}
//===================================================================


bool EnemyIsSightActive(Enemy *enemy)
{
  return enemy->sight_active;
}
//===================================================================


void EnemyMove(Map *map, Enemy *enemy)
{
  if(enemy->status == kWaiting)
  {
    enemy->motion = EnemySortAction();
    enemy->steps = EnemySortSteps();
    enemy->status = kMoving;
  }

  switch (enemy->motion)
  {
    case kStop:
      enemy->steps_counter++;
      break;

    case kNorth:
      EnemyRotate(ANGLE_90, map, enemy);
      EnemyTranslate(enemy->motion, 1, map, enemy);
      enemy->steps_counter++;
      break;

    case kSouth:
      EnemyRotate(ANGLE_270, map, enemy);
      EnemyTranslate(enemy->motion, 1, map, enemy);
      enemy->steps_counter++;
      break;

    case kWest:
      EnemyRotate(ANGLE_180, map, enemy);
      EnemyTranslate(enemy->motion, 1, map, enemy);
      enemy->steps_counter++;
      break;

    case kEast:
      EnemyRotate(ANGLE_0, map, enemy);
      EnemyTranslate(enemy->motion, 1, map, enemy);
      enemy->steps_counter++;
      break;
  }

  if(enemy->steps_counter == enemy->steps)
  {
    enemy->steps_counter = 0;
    enemy->status = kWaiting;
  }
}
//===================================================================


void EnemyRotate(const int16_t rotation_angle, Map *map, Enemy *enemy)
{
  if(rotation_angle == enemy->sight->angle)
    return;

  EnemyEraseFromMatrix(map, enemy);

  SightCreate(rotation_angle,
              enemy->sight->length,
              &enemy->icon.point,
              enemy->sight);

  // Adapt Sight to map objects.
  SightCreateInstantLines(map, enemy->sight);

  EnemyTransferTomMatrix(map, enemy);
}
//===================================================================


void EnemyTranslate(const Translation direction,
                    const uint16_t scalar,
                    Map *map,
                    Enemy *enemy)
{
  EnemyEraseFromMatrix(map, enemy);

  // Translate enemy icon.
  TranslatePoint(direction, scalar, &(enemy->icon.point));

  // IF enemy is in the same position as an object, revert operation.
  if(IsPointAnObject(&(enemy->icon.point), map))
  {
    TranslatePoint(direction, (-1 * scalar), &(enemy->icon.point));
  }
  else
  {
    SightCreate(enemy->sight->angle,
                enemy->sight->length,
                &enemy->icon.point,
                enemy->sight);

    // Adapt Sight to map objects.
    SightCreateInstantLines(map, enemy->sight);
  }

  EnemyTransferTomMatrix(map, enemy);
}
//===================================================================


Enemy *NewEnemy(const int16_t angle,
                const int16_t sight_length,
                const Point *origin,
                Map *map)
{
  // Create Enemy object.
  Enemy *enemy = malloc(sizeof(Enemy));

  // Init enemy position.
  enemy->icon.point = *origin;

  // Init enemy image.
  strcpy(enemy->icon.img, U_ENEMY);

  // Length test.
  if(sight_length <= 0)
  {
    enemy->sight_active = 0;
    return enemy;
  }

  enemy->sight_active = true;
  enemy->sleep = false;
  enemy->sleep_counter = 0;

  enemy->steps_counter = 0;
  enemy->steps = 0;
  enemy->status = kWaiting;

  // Create Enemy's Sight object.
  enemy->sight = NewSight();

  // Create Boundries.
  SightCreate(angle,
              sight_length,
              &enemy->icon.point,
              enemy->sight);

  // Adapt Sight to map objects.
  SightCreateInstantLines(map, enemy->sight);

  EnemyTransferTomMatrix(map, enemy);

  return enemy;
}
//===================================================================





static void EnemyEraseFromMatrix(Map *map, Enemy *enemy)
{
  Line *aux_line;
  Point *aux_point;

  // Erase enemy icon.
  map->matrix[enemy->icon.point.y][enemy->icon.point.x] = ' ';

  // Erase Sight points.
  for(uint16_t i = 0; i < enemy->sight->instant_lines->length; i++)
  {
    aux_line = VectorLineGetLine(i, enemy->sight->instant_lines);

    for(uint16_t j = 0; j < aux_line->length; j++)
    {
      aux_point = LineGetPointRef(j, aux_line);

      map->matrix[aux_point->y][aux_point->x] = ' ';
    }
  }
}
//===================================================================


static Translation EnemySortAction()
{
  srand(time(NULL));

  switch (rand()%5)
  {
    case 0:
      return kNorth;

    case 1:
      return kSouth;

    case 2:
      return kEast;

    case 3:
      return kWest;

    case 4:
      return kStop;
  }
  // Program never reaches this point, just to avoid compiler warning.
  return kStop;
}
//===================================================================


static uint8_t EnemySortSteps()
{
  srand(time(NULL));

  return ( (rand()%3) + 2 );
}
//===================================================================

static void EnemyTransferTomMatrix(Map *map, Enemy *enemy)
{
  Line *aux_line;
  Point *aux_point;

  // Tranfer enemy icon.
  map->matrix[enemy->icon.point.y][enemy->icon.point.x] = '@';

  // Transfer Sight points.
  for(uint16_t i = 0; i < enemy->sight->instant_lines->length; i++)
  {
    aux_line = VectorLineGetLine(i, enemy->sight->instant_lines);

    for(uint16_t j = 0; j < aux_line->length; j++)
    {
      aux_point = LineGetPointRef(j, aux_line);

      map->matrix[aux_point->y][aux_point->x] = '.';
    }
  }
}
//===================================================================
