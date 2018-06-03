#include <ncursesw/ncurses.h>
#include <string.h>

#include "inc/display.h"

void ShowPoint(const Point *point, const char img[])
{
  mvprintw(point->y, point->x, "%s", img);
}
//===================================================================

void ShowLine(const Line *line, const char img[])
{
  for(uint8_t i = 0; i < line->lenght; i++)
  {
    ShowPoint( LineGetPointRef(i,line), img);
  }
  refresh();
}
//===================================================================


void ShowRectangle(const Rectangle *rectangle, const char img[])
{
  ShowLine(rectangle->bottom_line, img);
  ShowLine(rectangle->right_line, img);
  ShowLine(rectangle->top_line, img);
  ShowLine(rectangle->left_line, img);
}
//===================================================================


void ShowPersonageBase(PersonageBase *personage)
{
  mvprintw(personage->point.y,
           personage->point.x,
           "%s", personage->img); /**< Print personage in x,y position */
  refresh();
}
//===================================================================


void ShowEnemySight(Sight *sight)
{
  // Print in blue color.
  attron(COLOR_PAIR(2));
  ShowLine(sight->bound1->offset_line, sight->bound1->img);
  ShowLine(sight->bound2->offset_line, sight->bound2->img);

//  attron(COLOR_PAIR(1));
//  ShowLine(sight->bound1->directional_line, sight->bound1->img);
//  ShowLine(sight->bound2->directional_line, sight->bound2->img);
}
//===================================================================


void ShowEnemy(Enemy *enemy)
{
  ShowPersonageBase(&(enemy->icon));
  ShowEnemySight(enemy->sight);
}
//===================================================================

