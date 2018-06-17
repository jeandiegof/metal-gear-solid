#include "inc/sight_private.h"
#include "inc/sight_boundry_private.h"

#include <string.h>

#include "inc/angles.h"
#include "inc/translation.h"


static void SightCreateBoundry3(Sight *sight);
//===================================================================

static void SighValidateAngle(const int16_t angle, Sight *sight);
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
  SighValidateAngle(angle, sight);

  // Init sight's length.
  sight->length = length;

  // Init boundry angles.
  int16_t angle_1 = AngleCorrection( sight->angle + ANGLE_45);
  int16_t angle_2 = AngleCorrection( sight->angle - ANGLE_45);

  // Create Boundries.
  SightBoundryCreate( angle_1, sight->length, enemy_origin, sight->bound_1 );
  SightBoundryCreate( angle_2, sight->length, enemy_origin, sight->bound_2 );

  SightCreateBoundry3(sight);
}
//===================================================================


void SightGrow(Sight *sight)
{
  SightBoundryGrow(sight->bound_1);
  SightBoundryGrow(sight->bound_2);

  sight->length++;
}
//===================================================================

void SightShrink(Sight *sight)
{
  SightBoundryShrink(sight->bound_1);
  SightBoundryShrink(sight->bound_2);

  sight->length--;
}
//===================================================================


static void SightCreateBoundry3(Sight *sight)
{
  Point last_b2 = LineGetLastPoint(sight->bound_2->line);

  int16_t angle_3 = AngleCorrection( sight->angle + ANGLE_90 );

  Point direction_vector = AngleGetDirectionVector(angle_3);

  Point origin;
  // Negates this same invert operation inside SightBoundryCreate().
  origin.x = last_b2.x + ( -1 * direction_vector.x );
  origin.y = last_b2.y + ( -1 * direction_vector.y );

  // Calculates bound_3 length.
  // Arithmetic sequence for bound_3 length.
  int16_t length_3 = 3 + 2 * (sight->length - 1);

  // Tweak the point for sight's angle.
  switch (angle_3)
  {
    case ANGLE_0:
      origin.x -=  1;
      origin.y +=  1;
      break;

    case ANGLE_180:
      origin.x +=  1;
      origin.y -=  1;
      break;

    case ANGLE_90:
      origin.x += 1;
      break;

    case ANGLE_270:
      origin.x -= 1;
      break;
  }
  SightBoundryCreate(angle_3, length_3, &origin, sight->bound_3);
}
//===================================================================


static void SighValidateAngle(const int16_t angle, Sight *sight)
{
  // Init sight's angle.
  switch (sight->angle)
  {
    case ANGLE_0:
    case ANGLE_90:
    case ANGLE_180:
    case ANGLE_270:
      sight->angle = angle;
      break;
    default:
      printf("\n\nInvalid enemy angle.\n\n\n");
      exit(1);
      break;
  }
  return;
}
