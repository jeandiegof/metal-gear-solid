#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/game_definitions.h"
#include "inc/manager_map.h"
#include "inc/personage_base.h"
#include "inc/sight_structs.h"
#include "inc/translation.h"

#define ENEMY_MATRIX_CHAR        '@'
#define ENEMY_SLEEP_MATRIX_CHAR  'Z'
#define ENEMY_SIGHT_MATRIX_CHAR  '.'

typedef enum EnemyStatus
{
  kEnemyMoving,
  kEnemySleeping,
  kEnemyWaiting
}EnemyStatus;


typedef struct Enemy
{
  PersonageBase icon;

  Sight *sight;

  bool sight_active;

  uint16_t sleep_total;

  uint16_t sleep_counter;

  uint8_t steps_total;

  uint8_t steps_counter;

  Translation motion;

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

int16_t EnemySortAngle();
//===================================================================

int16_t EnemySortLength(int16_t range_1, int16_t range_2);
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

void EnemyHitSignal(Map *map, Enemy *enemy);

#endif // STRUCTPERSONAGE_H
