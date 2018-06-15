#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>

#include "inc/personage_base.h"
#include "inc/sight_structs.h"
#include "inc/translation.h"


typedef struct Enemy
{
  struct PersonageBase icon;

  struct Sight *sight;

  Point max_point;
  Point min_point;

}Enemy;
//===================================================================

/**
 * @brief NewEnemy
 * @param angle
 * @param sight_length
 * @param origin
 * @return
 */
Enemy *NewEnemy(const int16_t angle,
                const int16_t sight_length,
                const Point *origin);
//===================================================================

/**
 * @brief DestroyEnemy
 * @param enemy
 */
void DestroyEnemy(Enemy *enemy);
//===================================================================

/**
 * @brief TranslateEnemy
 * @param direction
 * @param scalar
 * @param enemy
 */
void TranslateEnemy(const Translation direction,
                    const uint16_t scalar,
                    Enemy *enemy);
//===================================================================

/**
 * @brief RotateEnemy
 * @param rotation_angle
 * @param enemy
 */
void EnemyRotate(const int16_t rotation_angle, Enemy *enemy);
//===================================================================

#endif // STRUCTPERSONAGE_H
