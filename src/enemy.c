#include "inc/enemy.h"

#include <stdlib.h>
#include <string.h>

#include "inc/angles.h"
#include "inc/line.h"


Enemy *NewEnemy(const int16_t angle,
                const int16_t sight_length,
                const Point *origin)
{
  // Create Enemy object.
  Enemy *enemy = malloc(sizeof(Enemy));

	// Init enemy position.
  enemy->icon.point = *origin;

  // Init enemy image.
  strcpy(enemy->icon.img, U_ENEMY);

  // Create Enemy's Sight object.
  enemy->sight = NewSight();

  SightCreateBoundries(angle,
                       sight_length,
                       &enemy->icon.point,
                       enemy->sight);

  return enemy;
}
//===================================================================


void DestroyEnemy(Enemy *enemy)
{
  DestroySight(enemy->sight);
  free(enemy);
}
//===================================================================


void TranslateEnemy(const Translation direction,
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


void EnemyRotate(const uint16_t rotation_angle, Enemy *enemy)
{
  // Validates rotation_angle
  if(!AngleIsValid(rotation_angle))
  {
    exit(1);
  }

  SightCreateBoundries(rotation_angle,
                       enemy->sight->length,
                       &enemy->icon.point,
                       enemy->sight);

}
//===================================================================

// ----- END Global Functions Definitions
