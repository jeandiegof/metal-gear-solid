#ifndef STRUCTPERSONAGE_H
#define STRUCTPERSONAGE_H

#include <stdint.h>

#include "inc/line.h"
#include "inc/rectangle.h"
#include "inc/personage_base.h"

typedef struct SightBoundry
{
  char img[U_LENGHT];

  uint8_t lenght;

  int16_t angle;

  Line *directional_line;

  Line *offset_line;

}SightBoundry;
//===================================================================

/**
 * @brief Abstract struct. Gives sight to the object.
 *
 *
 * Sight is a triangle which origin's at personage position.
 * The orientation is related to personage's angle, the height of this
 * triangle has its size determined by #lenght.
 *
 */
typedef struct Sight
{
  int16_t angle;

  uint8_t lenght;

  struct SightBoundry *bound1;

  struct SightBoundry *bound2;

}Sight;
//===================================================================

typedef struct Enemy
{
  /** Image and its position at the terminal.*/
  struct PersonageBase icon;

  struct Sight *sight;

  /** @brief A box around the enemy used for detection algorith and limits
   *  for translation.
   */
  struct Rectangle *box;

}Enemy;
//===================================================================


Enemy *NewEnemy(const Point *origin, const uint8_t sight_lenght);

void DestroyEnemy(Enemy *enemy);

void SightUpdate(Sight *sight);

#endif // STRUCTPERSONAGE_H
