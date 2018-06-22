#include "inc/display.h"

#include <ncursesw/ncurses.h>
#include <string.h>



void HidePoint(const Point *point)
{
    mvprintw(point->y, point->x, " ");
}
//===================================================================


void HideLine(const Line *line)
{
  for(uint16_t i = 0; i < line->length; i++)
  {
    HidePoint(LineGetPointRef(i, line));
  }
}
//===================================================================


//void HideLine(const Line *line, Map *map)
//{
//  Point aux_point;

//  bool end_flag = 0;

//  for(uint8_t i = 0; i < line->length; i++)
//  {
//    aux_point = LineGetPoint(i,line);
//    switch(map->matrix[aux_point.y][aux_point.x])
//    {
//      case '#':
//      case 'x':
//        end_flag = 1;
//        break;

//      case '@':
//      case '0':
//      case 'K':
//      case '%':
//        break;

//      default:
//        HidePoint(&aux_point);
//        map->matrix[aux_point.y][aux_point.x] = ' ';
//        break;
//    }
//    if(end_flag)
//      break;
//  }
//}
//===================================================================


//void HideEnemySight(Sight *sight, Map *map)
//{
//  HideLine(sight->bound_1->line, map);
//  HideLine(sight->bound_2->line, map);
//  HideLine(sight->bound_3->line, map);
//}
////===================================================================


//void HideEnemy(Enemy *enemy, Map *map)
//{
//  HidePoint( &(enemy->icon.point) );

//  HideEnemySight(enemy->sight, map);

//}
////===================================================================




void ShowPoint(const Point *point, const char img[])
{
  mvprintw(point->y, point->x, "%s", img);
}
//===================================================================


void ShowLine(const Line *line, const char img[])
{
  for(uint16_t i = 0; i < line->length; i++)
  {
    ShowPoint(LineGetPointRef(i, line), img);
  }
}
//===================================================================


void ShowEnemySightBoundry(SightBoundry *boundry,  Map *map)
{
  Point aux_point;

  bool end_flag = 0;

  for(uint8_t i = 0; i < boundry->length; i++)
  {
    aux_point = LineGetPoint(i, boundry->line);

    switch(map->matrix[aux_point.y][aux_point.x])
    {
      case '#':
      case 'x':
        end_flag = 1;
        break;

      case '@':
      case '0':
      case 'K':
      case '%':
        break;

      default:
        ShowPoint(&aux_point, boundry->img);
        break;
    }
    if(end_flag)
      break;
  }  
}
//===================================================================


void ShowEnemySight(Sight *sight, Map *map)
{

  // Print in blue color.
//  attron(COLOR_PAIR(2));
  ShowEnemySightBoundry(sight->bound_1, map);
  ShowEnemySightBoundry(sight->bound_2, map);
  ShowEnemySightBoundry(sight->bound_3, map);

//  attron(COLOR_PAIR(2));
//  ShowLine(sight->bound_1->visible_line, "v");
//  ShowLine(sight->bound_2->visible_line, "h");
//  ShowLine(sight->bound_3->visible_line, "o");

//  attron(COLOR_PAIR(2));
//  ShowLine(sight->bound_3->limit_line, "o");
//  attron(COLOR_PAIR(1));
//  ShowLine(sight->bound_1->limit_line, "1");
//  ShowLine(sight->bound_2->limit_line, "2");

}
//===================================================================


void ShowEnemy(Enemy *enemy, Map *map)
{
  ShowPoint( &(enemy->icon.point), enemy->icon.img );

  if(!enemy->sight_active)
    return;

  ShowEnemySight(enemy->sight, map);
}
//===================================================================
