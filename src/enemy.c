#include "inc/enemy.h"

#include <stdlib.h>
#include <string.h>

#include "inc/sight_private.h"
#include "inc/angles.h"
#include "inc/line.h"

Enemy *NewEnemy(const int16_t angle,
                const int16_t sight_length,
                const Point *origin,
                const Map *map)
{
  // Create Enemy object.
  Enemy *enemy = malloc(sizeof(Enemy));

	// Init enemy position.
  enemy->icon.point = *origin;

  // Init enemy image.
  strcpy(enemy->icon.img, U_ENEMY);

  enemy->sleep = 0;

  // Length test.
  if(sight_length <= 0)
  {
    enemy->sight_active = 0;
    return enemy;
  }

  enemy->sight_active = 1;

  // Create Enemy's Sight object.
  enemy->sight = NewSight();

  // Create Boundries.
  SightCreateBoundries(angle,
                       sight_length,
                       &enemy->icon.point,
                       enemy->sight);

  // Adapt Sight to map objects.
  SightCreateInstantLines(map, enemy->sight);

  return enemy;
}
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
  if(enemy->sight->length > 0)
    return true;
  else
    return false;
}
//===================================================================


void EnemySightGrow(Enemy *enemy)
{
  enemy->sight->length++;

  SightCreateBoundries(enemy->sight->angle,
                       enemy->sight->length,
                       &enemy->icon.point,
                       enemy->sight);


}
//===================================================================


void EnemyRotate(const int16_t rotation_angle, Enemy *enemy)
{
  int16_t new_angle = AngleCorrection(rotation_angle + enemy->sight->angle);

  SightCreateBoundries(new_angle,
                       enemy->sight->length,
                       &enemy->icon.point,
                       enemy->sight);

}
//===================================================================


void EnemySightShrink(Enemy *enemy)
{
  if(--enemy->sight->length <= 0)
    return;

  SightCreateBoundries(enemy->sight->angle,
                       enemy->sight->length,
                       &enemy->icon.point,
                       enemy->sight);
}
//===================================================================


void EnemyTranslate(const Translation direction,
                    const uint16_t scalar,
                    Enemy *enemy)
{
//  // Translate Icon.
//  TranslatePoint(direction, scalar, &enemy->icon.point);

//  // Translate Sight.

//  // Boundry 1
//  TranslateLine(direction, scalar, enemy->sight->bound1->directional_line);
//  TranslateLine(direction, scalar, enemy->sight->bound1->visible_line);

//  // Boundry 2
//  TranslateLine(direction, scalar, enemy->sight->bound2->directional_line);
//  TranslateLine(direction, scalar, enemy->sight->bound2->visible_line);
}
//===================================================================


// ----- END Global Functions Definitions
