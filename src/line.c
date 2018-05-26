#include <stdlib.h>

#include "inc/line.h"

static void LineUpdateMaxMinPoints(const Point *point, Line *line);

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

  /*
   * This struct defines xy coordinates for the directional vector of the line.
   * This vector is later used to formulate a parametric equation for both x
   * and y axis.
   */
  struct
  {
    int8_t x;
    int8_t y;
  } directional_vector = {0};

  Point new_point;

  // Validates and set line->lenght.
  // Lenght should be greater or equal to 2.
  if(lenght >= 2)

    line->lenght = lenght;

  else

    line->lenght = 2;

  // The first point is created based on the 'origin' argument.
  LineAppendPoint(origin, line);

  // Attributes the input angle to line.
  line->angle = angle;

  /*
   * Creates a directional vector to describes a parametric equation for a
   * given line angle.
   * If angle is not valid, set angle to ANGLE_0.
   */
  switch (angle)
  {
    default:
    case ANGLE_0:
      // If angle is invalid, ensures it is set to ANGLE_0;
      line->angle = 0;

      directional_vector.x = 1;
      directional_vector.y = 0;
      break;

    case ANGLE_45:
      directional_vector.x =  1;
      directional_vector.y = -1;
      break;

    case ANGLE_90:
      directional_vector.x =  0;
      directional_vector.y = -1;
      break;

    case ANGLE_135:
      directional_vector.x = -1;
      directional_vector.y = -1;
      break;

    case ANGLE_180:
      directional_vector.x = -1;
      directional_vector.y =  0;
      break;

    case ANGLE_225:
      directional_vector.x = -1;
      directional_vector.y =  1;
      break;

    case ANGLE_270:
      directional_vector.x = 0;
      directional_vector.y = 1;
      break;

    case ANGLE_315:
      directional_vector.x = 1;
      directional_vector.y = 1;
      break;
  }

  // Builds the Line point by point, based on the parametric equation.
  for(uint8_t i = 1; i < lenght; i++)
  {
    new_point.x = origin->x + ( i * directional_vector.x );
    new_point.y = origin->y + ( i * directional_vector.y );

    // Appends new_point to the line object.
    LineAppendPoint(&new_point, line);
  }
}

void DestroyLine(Line *line)
{
  if (line != NULL)
  {
    DestroyVectorPoint(line->points);
    free(line);
   }
}


Point LineGetPoint(const uint16_t index, const Line *line)
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


Line *NewLine()
{
  Line *line = malloc(sizeof(Line));

  line->angle = ANGLE_0;

  line->lenght = 0;

  line->max.x = 0;
  line->max.y = 0;
  line->min.x = 0;
  line->min.y = 0;

  line->points = NewVectorPoint();

  return line;
}


/**
 * @brief Finds if a specific point has values greater or smaller than
 * the maximuns and minimuns stored in a Line struct.
 *
 * @param point[in]
 * @param line[out]
 *
 * @note Private Function.
 */

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


