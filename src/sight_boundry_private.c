#include "inc/sight_boundry_private.h"

#include <string.h>

/**
 * @brief SightBoundrytCreateVisibleLine
 * @param origin
 * @param boundry
 */
static void SightBoundrytCreateVisibleLine(const Point *origin,
                                           SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundryFillLimitLine
 * @param boundry
 */
static void SightBoundryFillLimitLine(SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundryGrowVisibleLine
 * @param boundry
 */
static void SightBoundryGrowVisibleLine(SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundrySetImg
 * @param boundry
 */
static void SightBoundrySetImg(SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundryShrinkVisibleLine
 * @param boundry
 */
static void SightBoundryShrinkVisibleLine(SightBoundry *boundry);
//===================================================================


SightBoundry *NewSightBoundry()
{
  // Create SightBoundry object.
  SightBoundry *boundry = malloc(sizeof(SightBoundry));

  boundry->angle = ANGLE_0;

  boundry->length = 0;

  boundry->visible_line = NewLine();

  boundry->limit_line = NewLine();

  return boundry;
}
//===================================================================


void DestroySightBoundry(SightBoundry *boundry)
{
  DestroyLine(boundry->visible_line);
  DestroyLine(boundry->limit_line);
  free(boundry);
}
//===================================================================


void SightBoundryCreate(const int16_t angle,
                        const int16_t length,
                        const Point *ref_point,
                        SightBoundry *boundry)
{
  // Reset lines.
  LineReset(boundry->visible_line);
  LineReset(boundry->limit_line);

  // Init angle.
  boundry->angle = AngleCorrection(angle);

  // Init boundry direction vector.
  boundry->direction_vector = AngleGetDirectionVector(boundry->angle);

  // Init image for the actual angle.
  SightBoundrySetImg(boundry);

  // Init length.
  boundry->length = length;

  Point aux_point;
  aux_point.x = ref_point->x + ( 1 * boundry->direction_vector.x );
  aux_point.y = ref_point->y + ( 1 * boundry->direction_vector.y );

//  if(boundry->angle == ANGLE_0 || boundry->angle == ANGLE_180)
//    aux_point.x += 1 * boundry->direction_vector.x;
  SightBoundrytCreateVisibleLine(&aux_point, boundry);

  SightBoundryFillLimitLine(boundry);
}
//===================================================================


void SightBoundryGrow(SightBoundry *boundry)
{
  boundry->length++;

  SightBoundryGrowVisibleLine(boundry);

  SightBoundryFillLimitLine(boundry);
}
//===================================================================


void SightBoundryShrink(SightBoundry *boundry)
{
  boundry->length--;

  SightBoundryShrinkVisibleLine(boundry);

  SightBoundryFillLimitLine(boundry);
}
//===================================================================





static void SightBoundrytCreateVisibleLine(const Point *origin,
                                           SightBoundry *boundry)
{
  // Init angle.
  LineSetAngle(boundry->angle, boundry->visible_line);

  // Append the first point. SightBoundryGrowVisibleLine() requires the Line
  // object to have at least one point.
  LineAppendPoint(origin, boundry->visible_line);

  for(uint8_t i = 1; i < boundry->length; i++)
  {
    SightBoundryGrowVisibleLine(boundry);
  }
}
//===================================================================


static void SightBoundryFillLimitLine(SightBoundry *boundry)
{
  // Verify if there is need for limit lines.
  if(boundry->length < 2)
    return;

  // Reset limit_line.
  LineReset(boundry->limit_line);

  // COPY VISIBLE POINTS TO LIMIT_LINE

  // If angle is 90 or 270 just do a raw copy.
  if(boundry->angle == ANGLE_90 || boundry->angle == ANGLE_270)
  {
    LineCopy(boundry->visible_line, boundry->limit_line);
    return;
  }

  // If angle is different from 90 or 270, then create gaps in the limit line.
  uint16_t index = 0;

  // Init angle.
  LineSetAngle(boundry->angle, boundry->limit_line);

  // Copy visible_line to limit_line, leaving a gap in the array.
  for(uint8_t i = 0; i < boundry->length; i++)
  {
    LineInsertPoint(index,
                    LineGetPointRef(i, boundry->visible_line),
                    boundry->limit_line);
    index += 2;
  }

  // Fill the gaps in the limit line.
  Point next_point;
  Point gap_point;

  for(uint8_t i = 2; i < boundry->limit_line->length; i+=2)
  {
    next_point = LineGetPoint(i, boundry->limit_line);

    gap_point.x = next_point.x + ( -1 * boundry->direction_vector.x);
    gap_point.y = next_point.y;

    LineInsertPoint(i-1, &gap_point, boundry->limit_line);
  }
}
//===================================================================


static void SightBoundryGrowVisibleLine(SightBoundry *boundry)
{
  Point last_point;
  Point new_point;

  last_point = LineGetLastPoint(boundry->visible_line);

  new_point.x = last_point.x + (2 * boundry->direction_vector.x);
  new_point.y = last_point.y + (1 * boundry->direction_vector.y);

  LineAppendPoint(&new_point, boundry->visible_line);
}
//===================================================================


static void SightBoundrySetImg(SightBoundry *boundry)
{
  switch (boundry->angle)
  {
    case ANGLE_0:
    case ANGLE_180:
      strcpy(boundry->img, U_DOTLINE_H);
      break;

    case ANGLE_45:
    case ANGLE_225:
      strcpy(boundry->img, U_DOTLINE_NE);
      break;

    case ANGLE_90:
    case ANGLE_270:
      strcpy(boundry->img, U_DOTLINE_V);
      break;

    case ANGLE_135:
    case ANGLE_315:
      strcpy(boundry->img, U_DOTLINE_NW);
      break;
  }
}
//===================================================================


static void SightBoundryShrinkVisibleLine(SightBoundry *boundry)
{
  if(boundry->visible_line->length <= 0)
    return;

  LineRemoveLastPoint(boundry->visible_line);
}
//===================================================================
