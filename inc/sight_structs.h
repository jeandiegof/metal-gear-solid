#ifndef SIGHT_BOUNDRY_STRUCT_PRIVATE_H
#define SIGHT_BOUNDRY_STRUCT_PRIVATE_H

#include <stdint.h>

#include "inc/line.h"
#include "inc/unicodes.h"

typedef struct SightBoundry
{
  char img[U_length];

  int16_t length;

  int16_t angle;

  Point direction_vector;

  Line *visible_line;

  Line *limit_line;

}SightBoundry;
//===================================================================

/**
 * @brief Abstract struct. Gives sight to the object.
 *
 *
 * Sight is a triangle which origin's at personage position.
 * The orientation is related to personage's angle, the height of this
 * triangle has its size determined by #length.
 *
 */
typedef struct Sight
{
  int16_t angle;

  int16_t length;

  struct SightBoundry *bound_1;

  struct SightBoundry *bound_2;

  struct SightBoundry *bound_3;

}Sight;
//===================================================================

#endif // SIGHT_BOUNDRY_STRUCT_PRIVATE_H
