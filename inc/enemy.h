#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/map_manager.h"
#include "inc/personage_base.h"
#include "inc/sight_structs.h"
#include "inc/translation.h"

typedef enum EnemyStatus
{
  kMoving,
  kSleeping,
  kWaiting
}EnemyStatus;


typedef struct Enemy
{
  PersonageBase icon;

  Sight *sight;

  bool sight_active;

  bool sleep;

  uint16_t sleep_counter;

  bool already_moving;

  Translation motion;

  uint8_t steps;

  uint8_t steps_counter;

  EnemyStatus status;


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
                const Point *origin,
                Map *map);
//===================================================================

/**
 * @brief DestroyEnemy
 * @param enemy
 */
void DestroyEnemy(Enemy *enemy);
//===================================================================


void EnemyMove(Map *map, Enemy *enemy);
//===================================================================

/**
 * @brief RotateEnemy
 * @param rotation_angle
 * @param enemy
 */
void EnemyRotate(const int16_t rotation_angle, Map *map, Enemy *enemy);
//===================================================================

/**
 * @brief TranslateEnemy
 * @param direction
 * @param scalar
 * @param enemy
 */
void EnemyTranslate(const Translation direction,
                    const uint16_t scalar,
                    Map *map,
                    Enemy *enemy);
//===================================================================
#endif // STRUCTPERSONAGE_H
