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
  // Is point in the x range?
  if ( point->x <  line->min->x || point->x >  line->max->x )
    return false;

  // Is point in the y range?
  if ( point->y < line->min->y || point->y > line->max->y )
    return false;

  switch (line->angle)
  {
    case ANGLE_0:
    case ANGLE_90:
    case ANGLE_180:
    case ANGLE_270:
      return true;
      break;

    case ANGLE_45:
    case ANGLE_135:
    case ANGLE_225:
    case ANGLE_315:
      for(uint16_t i = 0; i < line->length; i++)
      {
        if(IsPointInPoint(LineGetPointRef(i, line), point))
          return true;
      }
      return false;
      break;
  }

  // Just to avoid compiler warnings, functions never reachs this line;
  return true;
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
  // Little workaround to cover two blind points in the logic.
  if(enemy->sight->angle == ANGLE_90)
 {
    Point aux_point = LineGetPoint(0, enemy->sight->bound_3->line);
    aux_point.x -= enemy->sight->bound_3->line->direction_vector.x;
    if(IsPointInPoint(point, &aux_point))
      return true;
  }
  else if(enemy->sight->angle == ANGLE_270)
  {
    Point aux_point = LineGetLastPoint(enemy->sight->bound_3->line);
    aux_point.x += enemy->sight->bound_3->line->direction_vector.x;
    if(IsPointInPoint(point, &aux_point))
      return true;
  }


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

  // Checks the case whether the point is inside or outside
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

  DestroyLine(detection_line);

  if(intersection_counter != 1)
  {
    return false;
  }

  return true;
}
//===================================================================


int16_t IfObjectOverLineGetIndex(const Line *line, const Map *map)
{
  for(uint16_t i = 0; i < line->length; i++)
  {
    if( IsPointAnObject(LineGetPointRef(i, line), map) )
      return i;
  }

  // There is no object over the line.
  return -1;
}
//===================================================================

bool IsObjectBetweenPointsHorizontal(const Point *origin_point,
                                     const Point *point,
                                     const Map *map)
{
  Point map_point = *origin_point;

  int16_t max_x;
  int16_t min_x;

  int16_t distance;

  if(origin_point->x < point->x)
  {
    max_x = point->x;
    min_x = origin_point->x;
  }
  else
  {
    max_x = origin_point->x;
    min_x = point->x;
  }

  distance = max_x - min_x;

  for(uint16_t i = 0; i <= distance; i++)
  {
    map_point.x = min_x + i;
    if(IsPointAnObject(&map_point, map))
      return true;
  }

  return false;
}
//===================================================================


bool IsObjectBetweenPointsVertical(const Point *origin_point,
                                   const Point *point,
                                   const Map *map)
{
  Point map_point = *origin_point;

  int16_t max_y;
  int16_t min_y;

  int16_t distance;

  if(origin_point->y < point->y)
  {
    max_y = point->y;
    min_y = origin_point->y;
  }
  else
  {
    max_y = origin_point->y;
    min_y = point->y;
  }

  distance = max_y - min_y;

  for(uint16_t i = 0; i <= distance; i++)
  {
    map_point.y = min_y + i;
    if(IsPointAnObject(&map_point, map))
      return true;
  }

  return false;
}
//===================================================================


bool IsPointAnObject(const Point *point, const Map *map)
{
  switch (map->matrix[point->y][point->x])
  {
    case '#':
    case 'x':
    case '@':
    case '0':
    case 'K':
    case '%':
      return true;
      break;

    default:
      return false;
  }
}
//===================================================================
