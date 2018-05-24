#include <stdlib.h>
#include <string.h>

#include "inc/line.h"


void LineAppendPoint(const Point *point, Line *line)
{
  VectorPointAppend(point, line->points);

  LineUpdateMaxMinPoints(point, line);
}

void LineCreate(const Point *origin,
                const int16_t angle,
                const int16_t lenght,
                Line *line)
{

  struct
  {
    /*
     * Flag for direction, used as multiplier:
     *     direction = -1 :
     *         Coordinates of Line will be decreased in relation to origin.
     *
     *     direction = 1 :
     *         Coordinates of Line will be increasead in relation to origin.
     */
    int8_t direction;

    // Bollean flag, enable or disable axis coordinate modification.
    uint8_t select;
  }  axis_x={0}, axis_y={0};

  Point new_point;

  // Validates and set line->lenght.
  // Lenght should be greater or equal to 2.
  if(lenght >= 2)
    line->lenght = lenght;
  else
    line->lenght = 2;

  // Attributes the angle to line.
  line->angle = angle;

  LineAppendPoint(origin, line);

  /*
   * Validates angle and set some flags based on angle's value.
   * Those flags are latter used to perform some math when choosing the
   * right placement to Line's points.
   * If angle is not valid, set angle to ANGLE_0.
   */
  switch (angle)
  {
    default:
    case ANGLE_0:
      // If the case 'default:' is invoked, meaning, angle isn't valid.
      // Set angle to ANGLE_0.
      line->angle = 0;

      // Enable x coordinates modification.
      axis_x.select = 1;

      // x coordinates will be incremented, i.e., East direction.
      axis_x.direction = 1;
      break;

    case ANGLE_45:
      // Enable x coordinates modification.
      axis_x.select = 1;

      // Enable y coordinates modification.
      axis_y.select = 1;

      // x coordinates will be incremented, i.e., East direction.
      axis_x.direction = 1;

      // y coordinates will be decremented, i.e., North direction.
      axis_y.direction = -1;
      break;

    case ANGLE_90:
      // Enable y coordinates modification.
      axis_y.select = 1;

      // y coordinates will be decremented, i.e., North direction.
      axis_y.direction = -1;
      break;

    case ANGLE_135:
      // Enable x coordinates modification.
      axis_x.select = 1;

      // Enable y coordinates modification.
      axis_y.select = 1;

      // x coordinates will be decremented, i.e., West direction.
      axis_x.direction = -1;

      // y coordinates will be decremented, i.e., North direction.
      axis_y.direction = -1;
      break;

    case ANGLE_180:
      // Enable x coordinates modification.
      axis_x.select = 1;

      // x coordinates will be decremented, i.e., West direction.
      axis_x.direction = -1;
      break;

    case ANGLE_225:
      // Enable x coordinates modification.
      axis_x.select = 1;

      // Enable y coordinates modification.
      axis_y.select = 1;

      // x coordinates will be decremented, i.e., West direction.
      axis_x.direction = -1;

      // y coordinates will be incremented, i.e., South direction.
      axis_y.direction = 1;
      break;

    case ANGLE_270:
      // Enable y coordinates modification.
      axis_y.select = 1;

      // y coordinates will be incremented, i.e., South direction.
      axis_y.direction = 1;
      break;

    case ANGLE_315:
      // Enable x coordinates modification.
      axis_x.select = 1;

      // Enable y coordinates modification.
      axis_y.select = 1;

      // x coordinates will be incremented, i.e., East direction.
      axis_x.direction = 1;

      // y coordinates will be incremented, i.e., South direction.
      axis_y.direction = 1;
      break;
  }

  /*
   * Here is the math behind the equation inside the if's statements below:
   *
   *   if(axis_ .select):
   *
   *     If axis_ . select == 0, then the coordinate will not be
   *     modified in any loop iteration.
   *
   *   new_point. = origin->  + ( i * axis_ .direction ):
   *
   *     axis_ .direction will be -1 or +1. Thus, it controls if
   *     origin-> will be incremented or decremented by i value.
   *
   * This loop creates a Line object using a set of points one after another.
   *
   */
  for(uint8_t i = 1; i < lenght; i++)
  {
    if(axis_x.select)
      new_point.x = origin->x + ( i * axis_x.direction );
    else
      new_point.x = origin->x;

    if(axis_y.select)
      new_point.y = origin->y + ( i * axis_y.direction );
    else
      new_point.y = origin->y;

    // Appends new_point to the line object.
    LineAppendPoint(&new_point, line);
  }
}

void DestroyLine(Line *line)
{
  if (line != NULL)
  {
    DestroyVectorPoint(line->points);
    free (line);
   }
}


const Point LineGetPoint(const uint16_t index, const Line *line)
{
  return VectorPointValue(index, line->points);
}


Point *LineGetPointRef(const uint16_t index, const Line *line)
{
  return VectorPointValueRef(index, line->points);
}


void LineInsertPoint(const uint16_t index, const Point *point, Line *line)
{
  VectorPointInsert(index, point, line->points);

  line->lenght = VectorPointSize(line->points);

  LineUpdateMaxMinPoints(point, line);
}


Line *NewLine(const char name[])
{
  Line *line = malloc(sizeof(Line));

  line->angle = ANGLE_0;

  line->lenght = 0;

  line->max.x = 0;
  line->max.y = 0;
  line->min.x = 0;
  line->min.y = 0;

  strcpy(line->name, name);

  line->points = NewVectorPoint();

  return line;
}


static void LineUpdateMaxMinPoints(const Point *point, Line *line)
{
  if(point->x > line->max.x)

    line->max.x = point->x;

  else if(point->x < line->min.x)

    line->min.x = point->x;

  if(point->y > line->max.y)

    line->max.y = point->y;

  else if(point->y < line->min.y)

    line->min.y = point->y;
}


