#ifndef SIGHT_BOUNDRY_STRUCT_PRIVATE_H
#define SIGHT_BOUNDRY_STRUCT_PRIVATE_H

#include <stdint.h>

#include "inc/vector_line.h"
#include "inc/unicodes.h"

typedef struct SightBoundry
{
  char img[U_LENGTH];

  int16_t length;

  Line *line;

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

  SightBoundry *bound_1;

  SightBoundry *bound_2;

  SightBoundry *bound_3;

  VectorLine *full_lines;

  VectorLine *full_lines_1;

  VectorLine *full_lines_2;

  VectorLine *instant_lines;

  VectorLine *instant_lines_1;

  VectorLine *instant_lines_2;

}Sight;
//===================================================================

#endif // SIGHT_BOUNDRY_STRUCT_PRIVATE_H
