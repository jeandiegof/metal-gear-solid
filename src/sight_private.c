#include "inc/sight_private.h"
#include "inc/sight_boundry_private.h"

#include <string.h>
#include <math.h>

#include "inc/angles.h"
#include "inc/detection.h"
#include "inc/translation.h"



static void SightCreateBoundry3(Sight *sight);
//===================================================================

static int16_t SightIfObjectBetweenBoundryGetIndex(const Map *map,
                                                   const Sight *sight,
                                                   const SightBoundry *boundry);
//===================================================================

static void SightIfObjectOverResizeInstantLine(const Line *original_line,
                                               const Map *map,
                                               Line *instant_line);
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

  // Create VectorLine.
  sight->full_lines = NewVectorLine();

  // Create VectorLine.
  sight->full_lines_1 = NewVectorLine();

  // Create VectorLine.
  sight->full_lines_2 = NewVectorLine();

  // Create VectorLine.
  sight->instant_lines = NewVectorLine();

  // Create VectorLine.
  sight->instant_lines_1 = NewVectorLine();

  // Create VectorLine.
  sight->instant_lines_2 = NewVectorLine();

  return sight;
}
//===================================================================


void DestroySight(Sight *sight)
{
  DestroySightBoundry(sight->bound_1);
  DestroySightBoundry(sight->bound_2);
  DestroySightBoundry(sight->bound_3);

  DestroyVectorLine(sight->full_lines);
  DestroyVectorLine(sight->instant_lines);

  DestroyVectorLine(sight->full_lines_1);
  DestroyVectorLine(sight->instant_lines_1);

  DestroyVectorLine(sight->full_lines_2);
  DestroyVectorLine(sight->instant_lines_2);

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

  SightFill(enemy_origin, sight);
}
//===================================================================


void SightCreateInstantLines(const Map *map, Sight *sight)
{
  Line *full_line;
  Line *new_instant_line = NewLine();

  int16_t vector_1_length;
  int16_t vector_2_length;

  vector_1_length = IfObjectOverLineGetIndex(sight->bound_1->line, map);
  vector_2_length = IfObjectOverLineGetIndex(sight->bound_2->line, map);

  switch (sight->angle)
  {
    case ANGLE_0:
    case ANGLE_180:
      if(vector_1_length == -1)
      {
        vector_1_length = SightIfObjectBetweenBoundryGetIndex(map,
                                                              sight,
                                                              sight->bound_1);
      }
      if(vector_2_length == -1)
      {
        vector_2_length = SightIfObjectBetweenBoundryGetIndex(map,
                                                              sight,
                                                              sight->bound_2);
      }
      break;
    case ANGLE_90:
    case ANGLE_270:
      if(vector_1_length == -1)
      {
        vector_1_length = SightIfObjectBetweenBoundryGetIndex(map,
                                                              sight,
                                                              sight->bound_1);
      }
      else
      {
        vector_1_length = (vector_1_length * 2) + 1;
      }
      if(vector_2_length == -1)
      {
        vector_2_length = SightIfObjectBetweenBoundryGetIndex(map,
                                                              sight,
                                                              sight->bound_2);
      }
      else
      {
        vector_2_length = (vector_2_length * 2) + 1;
      }
      break;
  }

  // Create instant_lines for enemy axis.
  full_line = VectorLineGetLine(0, sight->full_lines);
  SightIfObjectOverResizeInstantLine(full_line, map, new_instant_line);
  VectorLineAppend(new_instant_line, sight->instant_lines);

  // Create instant_lines for boundries.
  for(uint16_t i = 0; i < vector_1_length; i++)
  {
    full_line = VectorLineGetLine(i, sight->full_lines_1);
    SightIfObjectOverResizeInstantLine(full_line, map, new_instant_line);
    VectorLineAppend(new_instant_line, sight->instant_lines_1);
  }
  for(uint16_t i = 0; i < vector_2_length; i++)
  {
    full_line = VectorLineGetLine(i, sight->full_lines_2);
    SightIfObjectOverResizeInstantLine(full_line, map, new_instant_line);
    VectorLineAppend(new_instant_line, sight->instant_lines_2);
  }

  VectorLineAppendVector(sight->instant_lines_1, sight->instant_lines);
  VectorLineAppendVector(sight->instant_lines_2, sight->instant_lines);
}
//===================================================================


void SightFill(const Point *enemy_origin, Sight *sight)
{
  Point bound_origin;

  Point direction_vector = AngleGetDirectionVector(sight->angle);

  Line *new_full_line = NewLine();

  int16_t line_length;
  int16_t line_last_coord;

  // Line in the same axis as enemy icon. Origin is different for each angle.
  Point enemy_line_origin;
  enemy_line_origin.x = enemy_origin->x + direction_vector.x;
  enemy_line_origin.y = enemy_origin->y + direction_vector.y;

  VectorLineReset(sight->full_lines);
  VectorLineReset(sight->full_lines_1);
  VectorLineReset(sight->full_lines_2);

  switch (sight->angle)
  {
    case ANGLE_0:
    case ANGLE_180:
      // Enemy icon line.
      line_length = sight->length * 2;
      LineCreate(&enemy_line_origin, sight->angle, line_length, new_full_line);
      VectorLineAppend(new_full_line, sight->full_lines);

      line_last_coord = enemy_origin->x +
                        (direction_vector.x * sight->length * 2);

      for(uint8_t i = 0; i < sight->length; i++)
      {
        // Bound_1 lines.
        bound_origin  = LineGetPoint(i, sight->bound_1->line);
        line_length = abs(line_last_coord - bound_origin.x) + 1;
        LineCreate(&bound_origin, sight->angle, line_length, new_full_line);
        VectorLineAppend(new_full_line, sight->full_lines_1);

        // Bound_2 lines.
        bound_origin  = LineGetPoint(i, sight->bound_2->line);
        line_length = abs(line_last_coord - bound_origin.x) + 1;
        LineCreate(&bound_origin, sight->angle, line_length, new_full_line);
        VectorLineAppend(new_full_line, sight->full_lines_2);
      }
      break;

    case ANGLE_90:
    case ANGLE_270:
      // Enemy icon line.
      line_length = sight->length + 1;
      LineCreate(&enemy_line_origin, sight->angle, line_length, new_full_line);
      VectorLineAppend(new_full_line, sight->full_lines);

      line_last_coord = enemy_origin->y +
                        (direction_vector.y * ( sight->length + 1 ) );

      for(uint8_t i = 0; i < sight->length; i++)
      {
        // Bound_1 lines. Always odd number.
        bound_origin  = LineGetPoint(i, sight->bound_1->line);
        line_length = abs(line_last_coord - bound_origin.y) + 1;
        LineCreate(&bound_origin, sight->angle, line_length, new_full_line);
        VectorLineAppend(new_full_line, sight->full_lines_1);

        if(i >= 1)
        {
          // Bound_1 line gaps.
          bound_origin = LineGetPoint(i, sight->bound_1->line);
          bound_origin.x -= sight->bound_1->line->direction_vector.x;
          line_length = abs(line_last_coord - bound_origin.y) + 1;
          LineCreate(&bound_origin, sight->angle, line_length, new_full_line);
          VectorLineAppend(new_full_line, sight->full_lines_1);
        }

        // Bound_2 lines. Always even number.
        bound_origin  = LineGetPoint(i, sight->bound_2->line);
        line_length = abs(line_last_coord - bound_origin.y) + 1;
        LineCreate(&bound_origin, sight->angle, line_length, new_full_line);
        VectorLineAppend(new_full_line, sight->full_lines_2);

        if(i >= 1)
        {
          // Bound_2 line gaps.
          bound_origin = LineGetPoint(i, sight->bound_2->line);
          bound_origin.x -= sight->bound_2->line->direction_vector.x;
          line_length = abs(line_last_coord - bound_origin.y) + 1;
          LineCreate(&bound_origin, sight->angle, line_length, new_full_line);
          VectorLineAppend(new_full_line, sight->full_lines_2);
        }
      }
      break;
  }

  VectorLineAppendVector(sight->full_lines_1, sight->full_lines);
  VectorLineAppendVector(sight->full_lines_2, sight->full_lines);

  DestroyLine(new_full_line);
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


static int16_t SightIfObjectBetweenBoundryGetIndex(const Map *map,
                                                   const Sight *sight,
                                                   const SightBoundry *boundry)
{
  if( sight->length >= 2 )
  {
    Point *point_1;
    Point *point_2;
    Point gap_point;

    switch (sight->angle)
    {
      case ANGLE_0:
      case ANGLE_180:
        for(uint8_t i = 1; i < sight->length; i++ )
        {
          point_1 = LineGetPointRef(i-1, boundry->line);
          point_2 = LineGetPointRef(i,   boundry->line);

          if(IsObjectBetweenPointsHorizontal(point_1, point_2, map) ||
             IsObjectBetweenPointsVertical(point_2, point_1, map))
          {
            return i;
          }
        }
        return boundry->length;
        break;

      case ANGLE_90:
      case ANGLE_270:
        for(uint8_t i = 1; i < sight->length; i++ )
        {
          point_1 = LineGetPointRef(i-1, boundry->line);
          point_2 = LineGetPointRef(i,   boundry->line);

          if(IsObjectBetweenPointsHorizontal(point_2, point_1, map)||
             IsObjectBetweenPointsVertical(point_1, point_2, map))
          {
            gap_point = *point_2;
            gap_point.x -= boundry->line->direction_vector.x;

            if(IsObjectBetweenPointsHorizontal(point_1, &gap_point, map))
            {
              return ((i*2)-1);
            }
            return ((i*2)-1);
          }
        }
        return (1 + 2*(boundry->length-1));
        break;
    }
  }
  // Line is smaller than two and this algorithm isn't required.
  return boundry->length;
}
//===================================================================


static void SightIfObjectOverResizeInstantLine(const Line *original_line,
                                               const Map *map,
                                               Line *instant_line)
{
  LineReset(instant_line);

  int16_t object_index = IfObjectOverLineGetIndex(original_line, map);

  if( object_index >= 0 )
  {
    for(uint16_t i = 0; i < object_index; i++)
    {
      LineAppendPoint( LineGetPointRef(i, original_line), instant_line );
    }
  }
  else
  {
    // Line not resized.
    LineCopy(original_line, instant_line);
  }
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
//===================================================================
