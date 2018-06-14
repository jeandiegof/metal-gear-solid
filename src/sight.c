#include "inc/sight.h"
#include "inc/sight_boundry_private.h"

#include <string.h>

#include "inc/angles.h"
#include "inc/translation.h"


static void SightCreateBoundry3(Sight *sight);
//===================================================================

static void SighTweakLimitGapYValues(Sight *sight);
//===================================================================


Sight *NewSight()
{
  // Create Sight object.
  Sight *sight = malloc(sizeof(Sight));

  sight->length = 0;

  sight->angle = ANGLE_0;

  // Create Sight's Boundry 1 object.
  sight->bound_1 = NewSightBoundry();

  // Create Sight's Boundry 2 object.
  sight->bound_2 = NewSightBoundry();

  // Create Sight's Boundry 3 object.
  sight->bound_3 = NewSightBoundry();

  return sight;
}
//===================================================================


void DestroySight(Sight *sight)
{
  DestroySightBoundry(sight->bound_1);
  DestroySightBoundry(sight->bound_2);
  DestroySightBoundry(sight->bound_3);
  free(sight);
}
//===================================================================


void SightCreateBoundries(const int16_t angle,
                          const int16_t length,
                          const Point *enemy_origin,
                          Sight *sight)
{
  // Init sight's angle.
  sight->angle = AngleCorrection(angle);

  // Init sight's length.
  sight->length = length;

  // Init boundry angles.
  int16_t angle_1 = AngleCorrection( sight->angle + ANGLE_45);
  int16_t angle_2 = AngleCorrection( sight->angle - ANGLE_45);

  // Create Boundries.
  SightBoundryCreate( angle_1, sight->length, enemy_origin, sight->bound_1 );
  SightBoundryCreate( angle_2, sight->length, enemy_origin, sight->bound_2 );

  SightCreateBoundry3(sight);

  // Little hack to limit_lines used in sight's detection algorithm.
  SighTweakLimitGapYValues(sight);
}
//===================================================================


void SightGrow(Sight *sight)
{
  SightBoundryGrow(sight->bound_1);
  SightBoundryGrow(sight->bound_2);

  SighTweakLimitGapYValues(sight);

  sight->length++;
}
//===================================================================


void SightGrowBoundry1(Sight *sight)
{
  SightBoundryGrow(sight->bound_1);

  SighTweakLimitGapYValues(sight);
}
//===================================================================

void SightGrowBoundry2(Sight *sight)
{
  SightBoundryGrow(sight->bound_2);

  SighTweakLimitGapYValues(sight);
}
//===================================================================

void SightShrink(Sight *sight)
{
  if(sight->length <= 0)
    return;

  SightBoundryShrink(sight->bound_1);
  SightBoundryShrink(sight->bound_2);

  SighTweakLimitGapYValues(sight);

  sight->length--;
}
//===================================================================


static void SightCreateBoundry3(Sight *sight)
{
  Point last_b2 = LineGetLastPoint(sight->bound_2->visible_line);

  int16_t angle_3 = AngleCorrection( sight->angle + ANGLE_90 );

  Point direction_vector = AngleGetDirectionVector(angle_3);

  Point origin;
  // Negates this same invert operation inside SightBoundryCreate().
  origin.x = last_b2.x + ( -1 * direction_vector.x );
  origin.y = last_b2.y + ( -1 * direction_vector.y );

  // Calculates bound_3 length.
  int16_t length_3;
  direction_vector = AngleGetDirectionVector(sight->angle);

  switch (angle_3)
  {
    case ANGLE_0:
    case ANGLE_90:
    case ANGLE_180:
    case ANGLE_270:
      // Tweak the point for sight's angle.
      origin.x = origin.x + ( 1 * direction_vector.x );
      origin.y = origin.y + ( 1 * direction_vector.y );

      // Arithmetic sequence.
      length_3 = 3 + 2 * (sight->length - 1);
      break;

    case ANGLE_45:
    case ANGLE_135:
    case ANGLE_225:
    case ANGLE_315:
      // Tweak the point for sight's angle.
//      origin.x = origin.x + ( 2 * direction_vector.x );
//      origin.y = origin.y + ( 1 * direction_vector.y )+1;

      length_3 = sight->length;
      break;
  }

  SightBoundryCreate(angle_3, length_3, &origin, sight->bound_3);
}
//===================================================================


static void SighTweakLimitGapYValues(Sight *sight)
{
  Point *aux_point;

  switch (sight->angle)
  {
    case ANGLE_0:
      for(uint8_t i = 1; i < sight->bound_1->limit_line->length; i+=2)
      {
        aux_point = LineGetPointRef(i, sight->bound_1->limit_line);
        TranslatePoint(kSouth, 1, aux_point);
      }

      for(uint8_t i = 1; i < sight->bound_2->limit_line->length; i+=2)
      {
        aux_point = LineGetPointRef(i, sight->bound_2->limit_line);
        TranslatePoint(kNorth, 1, aux_point);
      }
      break;

    case ANGLE_45:
      for(uint8_t i = 1; i < sight->bound_3->limit_line->length; i+=2)
      {
        aux_point = LineGetPointRef(i, sight->bound_3->limit_line);
        TranslatePoint(kSouth, 1, aux_point);
      }
      break;

    case ANGLE_180:
      for(uint8_t i = 1; i < sight->bound_1->limit_line->length; i+=2)
      {
        aux_point = LineGetPointRef(i, sight->bound_1->limit_line);
        TranslatePoint(kNorth, 1, aux_point);
      }

      for(uint8_t i = 1; i < sight->bound_2->limit_line->length; i+=2)
      {
        aux_point = LineGetPointRef(i, sight->bound_2->limit_line);
        TranslatePoint(kSouth, 1, aux_point);
      }
      break;

    case ANGLE_225:
      for(uint8_t i = 1; i < sight->bound_3->limit_line->length; i+=2)
      {
        aux_point = LineGetPointRef(i, sight->bound_3->limit_line);
        TranslatePoint(kNorth, 1, aux_point);
      }
      break;
  }
}
//===================================================================
