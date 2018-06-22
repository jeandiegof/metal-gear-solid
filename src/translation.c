#include "inc/translation.h"

#include <math.h>

#include "inc/log.h"
#include "inc/debug.h"


static void TranslateE(const uint16_t scalar, Point *point);


static void TranslateN(const uint16_t scalar, Point *point);


static void TranslateS(const uint16_t scalar, Point *point);


static void TranslateW(const uint16_t scalar, Point *point);


void TranslatePoint(const Translation direction,
                    const uint16_t scalar,
                    Point *point)
{
  switch (direction)
  {
    case kEast:
      TranslateE(scalar, point);
      break;

    case kNorth:
      TranslateN(scalar, point);
      break;

    case kSouth:
      TranslateS(scalar, point);
      break;

    case kWest:
      TranslateW(scalar, point);
      break;
  }
}
//===================================================================


void TranslateLine(const Translation direction,
                   const uint16_t scalar,
                   Line *line)
{
  for(uint16_t i = 0; i < line->length; i++)
    TranslatePoint(direction, scalar, LineGetPointRef(i, line));
}
//===================================================================


void TranslateVectorLine(const Translation direction,
                         const uint16_t scalar,
                         VectorLine *vector)
{
  for(uint16_t i = 0; i < vector->length; i++)
  {
    TranslateLine(direction, scalar, VectorLineGetLine(i, vector));
  }
}
//===================================================================


void TranslateRectangle(const Translation direction,
                        const uint16_t scalar,
                        Rectangle *rectangle)
{
  TranslateLine(direction, scalar, rectangle->bottom_line);
  TranslateLine(direction, scalar, rectangle->right_line);
  TranslateLine(direction, scalar, rectangle->top_line);
  TranslateLine(direction, scalar, rectangle->left_line);
}
//===================================================================


static void TranslateE(const uint16_t scalar, Point *point)
{
  point->x = point->x + scalar;
}
//===================================================================


static void TranslateN(const uint16_t scalar, Point *point)
{
  point->y = point->y - scalar;
}
//===================================================================


static void TranslateS(const uint16_t scalar, Point *point)
{
  point->y = point->y + scalar;
}
//===================================================================


static void TranslateW(const uint16_t scalar, Point *point)
{
  point->x = point->x - scalar;
}
//===================================================================
