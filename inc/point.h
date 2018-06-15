#ifndef POINT_H
#define POINT_H

#include <stdint.h>

/**
 * @brief Abstract struct for a point in console.
 *
 * Implements a point in x, y coordinate system.
 *
 * Although coordinates that a console can represet are always positive,
 * the variables #x and #y are from type @c int16_t. Meaning that they
 * could be used to store negative values. This feature can be useful in
 * some situations, e.g. storage of some offset value.
 *
*/
typedef struct Point
{
  int16_t x;
  int16_t y;
}Point;


Point PointGetArrayMaxValues(const Point *point_array, const uint16_t size);
//===================================================================

Point PointGetArrayMinValues(const Point *point_array, const uint16_t size);
//===================================================================

#endif // POINT_H
