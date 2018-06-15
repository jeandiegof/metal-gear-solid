#include "inc/enemy.h"

#include <stdlib.h>
#include <string.h>

#include "inc/sight_private.h"
#include "inc/angles.h"
#include "inc/line.h"

static void EnemyGetMaxMinPoints(Enemy *enemy);
//===================================================================


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

  EnemyGetMaxMinPoints(enemy);

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


void EnemyRotate(const int16_t rotation_angle, Enemy *enemy)
{
  int16_t new_angle = AngleCorrection(rotation_angle + enemy->sight->angle);

  SightCreateBoundries(new_angle,
                       enemy->sight->length,
                       &enemy->icon.point,
                       enemy->sight);

  EnemyGetMaxMinPoints(enemy);
}
//===================================================================


static void EnemyGetMaxMinPoints(Enemy *enemy)
{
  // Temporary arrays.
  Point max_array[4];
  Point min_array[4];

  // Finds which is the greatest values for y and x.
  max_array[0] = enemy->sight->bound_1->line->max;
  max_array[1] = enemy->sight->bound_2->line->max;
  max_array[2] = enemy->sight->bound_3->line->max;
  max_array[3] = enemy->icon.point;

  enemy->max_point = PointGetArrayMaxValues(max_array,4);

  // Finds which is the smallest values for y and x.
  min_array[0] = enemy->sight->bound_1->line->min;
  min_array[1] = enemy->sight->bound_2->line->min;
  min_array[2] = enemy->sight->bound_3->line->min;
  min_array[3] = enemy->icon.point;

  enemy->min_point = PointGetArrayMinValues(min_array,4);
}
//===================================================================

// ----- END Global Functions Definitions
