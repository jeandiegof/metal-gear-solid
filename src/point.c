#include "inc/point.h"

#include <stdlib.h>

Point PointGetArrayMaxValues(const Point *point_array, const uint16_t size)
{
  if(size < 2)
    exit(1);

  Point max;

  max.x = point_array[0].x;
  max.y = point_array[0].y;

  for(uint8_t i = 1; i < size; i++)
  {
    if(max.x < point_array[i].x)
      max.x = point_array[i].x;

    if(max.y < point_array[i].y)
      max.y = point_array[i].y;
  }

  return max;
}
//===================================================================


Point PointGetArrayMinValues(const Point *point_array, const uint16_t size)
{
  if(size < 2)
    exit(1);

  Point min;

  min.x = point_array[0].x;
  min.y = point_array[0].y;

  for(uint8_t i = 1; i < size; i++)
  {
    if(min.x > point_array[i].x)
      min.x = point_array[i].x;

    if(min.y > point_array[i].y)
      min.y = point_array[i].y;
  }

  return min;
}
//===================================================================
