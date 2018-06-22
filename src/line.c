#include "inc/line.h"

#include <stdlib.h>

#include "inc/translation.h"

#define LINE_CREATE_MIN_LENGTH 1

#define LINE_POINT_MAX_INIT_VALUE -32768
#define LINE_POINT_MIN_INIT_VALUE  32767



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
}
//===================================================================


void LineCopy(const Line *in_line, Line *out_line)
{
  LineReset(out_line);

  for(uint16_t i = 0; i < in_line->length; i++)
  {
    LineAppendPoint( LineGetPointRef(i, in_line), out_line );
  }

  LineSetAngle(in_line->angle, out_line);

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
}
//===================================================================


Line *NewLine()
{
  Line *line = malloc(sizeof(Line));

  LineSetAngle(ANGLE_0, line);

  LineSetLength(0, line);

  line->points = NewVectorPoint();

  line->max = &(line->points->max);
  line->min = &(line->points->min);

  return line;
}
//===================================================================


void LineRemoveLastPoint(Line *line)
{
  VectorPointRemoveLastPoint(line->points);

  LineSetLength( VectorPointGetSize(line->points), line );
}
//===================================================================


void LineReset(Line *line)
{
  LineSetAngle(ANGLE_0, line);

  LineSetLength(0, line);

  VectorPointReset(line->points);
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
