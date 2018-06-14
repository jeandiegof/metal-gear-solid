#include "inc/detection.h"

bool FindPointDirectionFromLine();

bool IsPointInPoint(const Point *point_1, const Point *point_2)
{
  if ( point_1->x == point_2->x &&
       point_1->y == point_2->y )
    return true;

  return false;
}

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

bool IsPointInEnemy(const Point *point, const Enemy *enemy)
{
//  // Is point inside Enemy's Box?
//  if( ! IsPointInRectangle(point, enemy->box) )
//    return false;

  // Is point at enemy's icon position?
  if ( IsPointInPoint(point, &(enemy->icon.point)) )
       return true;

  Point oposite_corner;

  bool flag_sight_is_diagonal = 1;

  // Sight detection when sight direction is diagonal.
  switch (enemy->sight->angle)
  {
    case ANGLE_45:
    case ANGLE_225:
      oposite_corner.x = LineGetPoint(enemy->sight->length-1,
                                      enemy->sight->bound_2->visible_line).x;

      oposite_corner.y = LineGetPoint(enemy->sight->length-1,
                                      enemy->sight->bound_1->visible_line).y;
      break;

    case ANGLE_135:
    case ANGLE_315:
      oposite_corner.x = LineGetPoint(enemy->sight->length-1,
                                      enemy->sight->bound_1->visible_line).x;

      oposite_corner.y = LineGetPoint(enemy->sight->length-1,
                                      enemy->sight->bound_2->visible_line).y;
      break;

    default:
      flag_sight_is_diagonal = 0;
      break;
  }

  if( flag_sight_is_diagonal )
  {
    Rectangle *rec = NewRectangle();

    RectangleCreate(&(enemy->icon.point), &oposite_corner, rec);

    if( IsPointInRectangle(point, rec) )
    {
      DestroyRectangle(rec);
      return true;
    }
    else
    {
      DestroyRectangle(rec);
      return false;
    }
  }
  return false;
}

