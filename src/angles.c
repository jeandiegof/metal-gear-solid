#include "inc/angles.h"

#include <stdlib.h>

int16_t AngleCorrection(const int16_t input_angle)
{
  int16_t angle = input_angle;

  while(angle >= 360)
  {
    angle -= 360;
  }

  while(angle < 0)
  {
    angle += 360;
  }

  if(!AngleIsValid(angle))
  {
    exit(1);
  }

  return angle;
}
//===================================================================


Point AngleGetDirectionVector(const int16_t angle)
{
  Point direction_vector;
  switch (angle)
  {
    case ANGLE_0:
      direction_vector.x = 1;
      direction_vector.y = 0;
      break;

    case ANGLE_45:
      direction_vector.x =  1;
      direction_vector.y = -1;
      break;

    case ANGLE_90:
      direction_vector.x =  0;
      direction_vector.y = -1;
      break;

    case ANGLE_135:
      direction_vector.x = -1;
      direction_vector.y = -1;
      break;

    case ANGLE_180:
      direction_vector.x = -1;
      direction_vector.y =  0;
      break;

    case ANGLE_225:
      direction_vector.x = -1;
      direction_vector.y =  1;
      break;

    case ANGLE_270:
      direction_vector.x = 0;
      direction_vector.y = 1;
      break;

    case ANGLE_315:
      direction_vector.x = 1;
      direction_vector.y = 1;
      break;
  }

  return direction_vector;
}
//===================================================================

bool AngleIsValid(const int16_t angle)
{
  switch (angle)
  {
    case ANGLE_0:
    case ANGLE_45:
    case ANGLE_90:
    case ANGLE_135:
    case ANGLE_180:
    case ANGLE_225:
    case ANGLE_270:
    case ANGLE_315:
      return true;
      break;

    default:
      return false;
      break;
  }
}
//===================================================================
