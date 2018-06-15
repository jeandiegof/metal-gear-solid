#include "inc/line.h"

#include <stdlib.h>

#include "inc/translation.h"

#define LINE_CREATE_MIN_LENGTH 1

#define LINE_POINT_MAX_INIT_VALUE -32768
#define LINE_POINT_MIN_INIT_VALUE  32767


static void LineInitMaxMinPoints(Line *line);
//===================================================================

static void LineUpdateMaxMinPoints(const Point *point, Line *line);
//===================================================================


void DestroyLine(Line *line)
{
  if (line != NULL)
  {
    DestroyVectorPoint(line->points);
    free(line);
   }
}
//===================================================================

void LineAppendPoint(const Point *point, Line *line)
{
  VectorPointAppend(point, line->points);

  line->length = VectorPointGetSize(line->points);

  LineUpdateMaxMinPoints(point, line);
}
//===================================================================


void LineCopy(const Line *in_line, Line *out_line)
{
  for(uint16_t i = 0; i < in_line->length; i++)
  {
    LineAppendPoint( LineGetPointRef(i, in_line), out_line );
  }

  LineSetAngle(in_line->angle, out_line);
//  out_line->angle = in_line->angle;

  out_line->length = in_line->length;
}
//===================================================================


void LineCreate(const Point *origin,
                const int16_t angle,
                const int16_t input_length,
                Line *line)
{
  // input_length should be greater or equal to 1.
  if(input_length < LINE_CREATE_MIN_LENGTH)
    return;

  LineReset(line);

  Point new_point;

  // Attributes the input angle to line.
  LineSetAngle(angle, line);

  // The first point is created based on the 'origin' parameter.
  LineAppendPoint(origin, line);

  // Builds the Line point by point, in the direction of direction_vector.
  for(uint8_t i = 1; i < input_length; i++)
  {
    new_point.x = origin->x + ( i * line->direction_vector.x );
    new_point.y = origin->y + ( i * line->direction_vector.y );

    // Appends new_point to the line object.
    LineAppendPoint(&new_point, line);
  }
}
//===================================================================


Point LineGetLastPoint(const Line *line)
{
  return VectorPointGetValue(line->length-1, line->points);
}
//===================================================================

Point LineGetPoint(const uint16_t index, const Line *line)
{
  return VectorPointGetValue(index, line->points);
}
//===================================================================


Point *LineGetPointRef(const uint16_t index, const Line *line)
{
  return VectorPointValueRef(index, line->points);
}
//===================================================================


void LineInsertPoint(const uint16_t index, const Point *point, Line *line)
{
  VectorPointInsert(index, point, line->points);

  line->length = VectorPointGetSize(line->points);

  LineUpdateMaxMinPoints(point, line);
}
//===================================================================


Line *NewLine()
{
  Line *line = malloc(sizeof(Line));

  LineSetAngle(ANGLE_0, line);

  LineSetLength(0, line);

  LineInitMaxMinPoints(line);

  line->points = NewVectorPoint();

  return line;
}
//===================================================================


void LineRemoveLastPoint(Line *line)
{
  if( VectorPointGetSize(line->points) <= 0 )
    return;

  // Direct access of VectorPoint member variable, in this case is safe.
  line->points->size--;

  LineSetLength( VectorPointGetSize(line->points), line );

  // Need to go through all the points to update maximum and minimun values.
  Point *aux_point;

  for(uint16_t i = 0; i < line->length; i++)
  {
    aux_point = LineGetPointRef(i, line);

    LineUpdateMaxMinPoints(aux_point, line);
  }
}
//===================================================================


void LineReset(Line *line)
{
  LineSetAngle(ANGLE_0, line);

  LineSetLength(0, line);

  LineInitMaxMinPoints(line);

  // Direct access of VectorPoint member variable, in this case is safe.
  line->points->size = 0;
}
//===================================================================

void LineSetAngle(const int16_t angle, Line *line)
{

  line->angle = AngleCorrection(angle);

  line->direction_vector = AngleGetDirectionVector(line->angle);
}
//===================================================================


void LineSetLength(const int16_t length, Line *line)
{
  if(length < 0)
  {
    line->length = 0;
    return;
  }

  line->length = length;
}
//===================================================================

static void LineInitMaxMinPoints(Line *line)
{
  line->max.x = LINE_POINT_MAX_INIT_VALUE;
  line->max.y = LINE_POINT_MAX_INIT_VALUE;

  line->min.x = LINE_POINT_MIN_INIT_VALUE;
  line->min.y = LINE_POINT_MIN_INIT_VALUE;
}
//===================================================================


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
  {
    line->max.x = point->x;
  }
  else if(point->x < line->min.x)
  {
    line->min.x = point->x;
  }

  if(point->y > line->max.y)
  {
    line->max.y = point->y;
  }
  else if(point->y < line->min.y)
  {
    line->min.y = point->y;
  }
}
//===================================================================
