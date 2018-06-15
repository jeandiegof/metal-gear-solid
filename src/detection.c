#include "inc/detection.h"


bool AreLinesIntersecting(const Line *line_1, const Line *line_2)
{
  for(uint16_t i = 0; i < line_1->length; i++)
  {
    if( IsPointInLine(LineGetPointRef(i,line_1), line_2) )
      return true;
    }
  return false;
}
//===================================================================

bool IsPointInLine(const Point *point, const Line *line)
{
  for(uint16_t i = 0; i < line->length; i++)
  {
    if( IsPointInPoint( point, LineGetPointRef(i,line) ) )
      return true;
  }
  return false;
}
//===================================================================

bool IsPointInPoint(const Point *point_1, const Point *point_2)
{
  if ( point_1->x == point_2->x &&
       point_1->y == point_2->y )
    return true;

  return false;
}
//===================================================================


bool IsPointInRectangle(const Point *point, const Rectangle *rec)
{
  // Checks the x range.
  if( point->x < rec->min.x || point->x > rec->max.x)
    return false;

  // Checks the y range.
  if (point->y < rec->min.y || point->y > rec->max.y)
    return false;

  // Is inside the rectangle.
  return true;
}
//===================================================================


bool IsPointInEnemy(const Point *point, const Enemy *enemy)
{
  // IF point is out of range THEN return false.
  // Checks the x range.
  if( point->x < enemy->min_point.x || point->x > enemy->max_point.x)
    return false;

  // Checks the y range.
  if (point->y < enemy->min_point.y || point->y > enemy->max_point.y)
    return false;

  // Checks the case where the point is over sight's boundries or
  // over enemy's icon.
  if( IsPointInLine(point, enemy->sight->bound_1->line) ||
      IsPointInLine(point, enemy->sight->bound_2->line) ||
      IsPointInLine(point, enemy->sight->bound_3->line) ||
      IsPointInPoint(&enemy->icon.point, point) )
    return true;

  // Checks the case where the point is inside or outside
  // sight's boundries.
  Line *detection_line = NewLine();

  uint8_t intersection_counter = 0;

  LineCreate(point, ANGLE_0, enemy->sight->length*2+1, detection_line);

  if(AreLinesIntersecting(detection_line, enemy->sight->bound_1->line))
    intersection_counter++;

  if(AreLinesIntersecting(detection_line, enemy->sight->bound_2->line))
    intersection_counter++;

  if(AreLinesIntersecting(detection_line, enemy->sight->bound_3->line))
    intersection_counter++;

  if(IsPointInLine(&enemy->icon.point, detection_line))
    intersection_counter++;

  if(intersection_counter != 1)
  {
    return false;
  }



  return true;
}
//===================================================================
