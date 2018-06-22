#include "inc/sight_boundry_private.h"

#include <string.h>

/**
 * @brief SightBoundrySetImg
 * @param boundry
 */
static void SightBoundrySetImg(SightBoundry *boundry);
//===================================================================


SightBoundry *NewSightBoundry()
{
  // Create SightBoundry object.
  SightBoundry *boundry = malloc(sizeof(SightBoundry));

  boundry->length = 0;

  strcpy(boundry->img, "?");

  boundry->line = NewLine();

  return boundry;
}
//===================================================================


void DestroySightBoundry(SightBoundry *boundry)
{
  DestroyLine(boundry->line);
  free(boundry);
}
//===================================================================


void SightBoundryCreate(const int16_t angle,
                        const int16_t length,
                        const Point *ref_point,
                        SightBoundry *boundry)
{
  // Reset lines.
  LineReset(boundry->line);

  // Init angle.
  LineSetAngle(angle, boundry->line);

  // Init image for the actual angle.
  SightBoundrySetImg(boundry);

  // Init length.
  if(length <= 0)
  {
    return;
  }

  Point origin;
  origin.x = ref_point->x + ( 1 * boundry->line->direction_vector.x );
  origin.y = ref_point->y + ( 1 * boundry->line->direction_vector.y );

  // Append the first point. SightBoundryGrow() requires the Line
  // object to have at least one point.
  LineAppendPoint(&origin, boundry->line);

  boundry->length = 1;

  for(uint8_t i = 1; i < length; i++)
  {
    SightBoundryGrow(boundry);
  }
}
//===================================================================


void SightBoundryGrow(SightBoundry *boundry)
{
  Point last_point;
  Point new_point;

  last_point = LineGetLastPoint(boundry->line);

  new_point.x = last_point.x + (2 * boundry->line->direction_vector.x);
  new_point.y = last_point.y + (1 * boundry->line->direction_vector.y);

  LineAppendPoint(&new_point, boundry->line);

  boundry->length = boundry->line->length;
}
//===================================================================


void SightBoundryShrink(SightBoundry *boundry)
{
  LineRemoveLastPoint(boundry->line);

  boundry->length = boundry->line->length;
}
//===================================================================


static void SightBoundrySetImg(SightBoundry *boundry)
{
  switch (boundry->line->angle)
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
