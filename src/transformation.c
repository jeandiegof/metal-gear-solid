#include <stdint.h>
#include <math.h>

#include "inc/log.h"
#include "inc/debug.h"
#include "inc/transformation.h"


void Rotate45(const Point *origin_point, Line *line)
{
  Point *line_point;

  // Absolute distance between the origin_point and the line point.
  int16_t abs_distance;

  for(uint16_t i = 0; i < line->lenght; i++)
  {
    line_point = LineGetPointRef(i, line);

    switch (line->angle)
    {
      case ANGLE_0:
      case ANGLE_315:
        abs_distance = abs( line_point->x - origin_point->x );
        TranslateN(abs_distance, line_point);
        LineInsertPoint( i, line_point, line );
        break;

      case ANGLE_45:
      case ANGLE_90:
        abs_distance = abs( line_point->y - origin_point->y );
        TranslateW(abs_distance, line_point);
        LineInsertPoint( i, line_point , line );
        break;

      case ANGLE_135:
      case ANGLE_180:
        abs_distance = abs( line_point->x - origin_point->x );
        TranslateS(abs_distance, line_point);
        LineInsertPoint( i, line_point, line );
        break;

      case ANGLE_225:
      case ANGLE_270:
        abs_distance = abs( line_point->y - origin_point->y );
        TranslateE(abs_distance, line_point);
        LineInsertPoint( i, line_point, line );
        break;
    }
  }

  if(line->angle == ANGLE_315)
    line->angle = ANGLE_0;
  else
    line->angle += ANGLE_45;
}
//===================================================================

void Rotate180(const Point *origin_point, Line *line)
{
  Point *line_point;
  Point new_point;

  int16_t distance;

  for(uint8_t i = 0; i < line->lenght; i++)
  {
    line_point = LineGetPointRef(i, line);

    distance = origin_point->x - line_point->x;
    new_point.x = origin_point->x + distance;

    distance = origin_point->y - line_point->y;
    new_point.y = origin_point->y + distance;

    LineInsertPoint( i, &new_point, line );
  }

  line->angle += ANGLE_180;
  if(line->angle > ANGLE_315)
    line->angle -= 360;
}
//===================================================================

void RotateEnemy(const uint16_t rotation_angle, Enemy *enemy)
{
  // Validates rotation_angle
  switch (rotation_angle)
  {
    case ANGLE_0:
    case ANGLE_45:
    case ANGLE_90:
    case ANGLE_135:
    case ANGLE_180:
    case ANGLE_225:
    case ANGLE_270:
    case ANGLE_315:
      break;
    default:
      exit(1);
      break;
  }

  int16_t counter_angle = rotation_angle;

  if( counter_angle >= ANGLE_180 )
  {
    Rotate180(&(enemy->icon.point), enemy->sight->bound1->directional_line);
    Rotate180(&(enemy->icon.point), enemy->sight->bound2->directional_line);

    counter_angle -= ANGLE_180;
  }

  for(uint8_t i = 0; counter_angle > 0; i++)
  {
    Rotate45(&(enemy->icon.point), enemy->sight->bound1->directional_line);
    Rotate45(&(enemy->icon.point), enemy->sight->bound2->directional_line);

    counter_angle -= ANGLE_45;
  }

  // Update sight's angle variable.
  enemy->sight->angle += rotation_angle;

  // Update boundries's angle variables.
  enemy->sight->bound1->angle = enemy->sight->bound1->directional_line->angle;
  enemy->sight->bound2->angle = enemy->sight->bound2->directional_line->angle;

  SightUpdate(enemy->sight);
}
//===================================================================

void TranslateE(const uint16_t scalar, Point *point)
{
  point->x = point->x + scalar;
}
//===================================================================


void TranslateN(const uint16_t scalar, Point *point)
{
  point->y = point->y - scalar;
}
//===================================================================


void TranslateS(const uint16_t scalar, Point *point)
{
  point->y = point->y + scalar;
}
//===================================================================


void TranslateW(const uint16_t scalar, Point *point)
{
	point->x = point->x - scalar;
}
//===================================================================


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
  for(uint16_t i = 0; i < line->lenght; i++)
    TranslatePoint(direction, scalar, LineGetPointRef(i, line) );
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


void TranslateEnemy(const Translation direction,
                    const uint16_t scalar,
                    Enemy *enemy)
{
  // Translate Icon.
  TranslatePoint(direction, scalar, &enemy->icon.point);

  // Translate Box.
  TranslateRectangle(direction, scalar, enemy->box);

  // Translate Sight.

  // Boundry 1
  TranslateLine(direction, scalar, enemy->sight->bound1->directional_line);
  TranslateLine(direction, scalar, enemy->sight->bound1->offset_line);

  // Boundry 2
  TranslateLine(direction, scalar, enemy->sight->bound2->directional_line);
  TranslateLine(direction, scalar, enemy->sight->bound2->offset_line);
}
//===================================================================
