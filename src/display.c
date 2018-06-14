#include "inc/display.h"

#include <ncursesw/ncurses.h>
#include <string.h>



void ShowPoint(const Point *point, const char img[])
{
  mvprintw(point->y, point->x, "%s", img);
}
//===================================================================

void ShowLine(const Line *line, const char img[])
{
  for(uint8_t i = 0; i < line->length; i++)
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


void ShowPersonageIcon(PersonageBase *personage)
{
  mvprintw(personage->point.y,
           personage->point.x,
           "%s", personage->img); /**< Print personage in x,y position */
  mvprintw(personage->point.y,
           personage->point.x,
           "x"); /**< Print personage in x,y position */
  refresh();
}
//===================================================================


void ShowEnemySight(Sight *sight)
{
  // Print in blue color.
  attron(COLOR_PAIR(2));
  ShowLine(sight->bound_1->visible_line, sight->bound_1->img);
  ShowLine(sight->bound_2->visible_line, sight->bound_2->img);
  ShowLine(sight->bound_3->visible_line, sight->bound_3->img);

//  attron(COLOR_PAIR(2));
//  ShowLine(sight->bound_1->visible_line, "v");
//  ShowLine(sight->bound_2->visible_line, "h");
//  ShowLine(sight->bound_3->visible_line, "o");

  attron(COLOR_PAIR(1));
//  ShowLine(sight->bound_1->limit_line, "v");
//  ShowLine(sight->bound_2->limit_line, "h");
//  ShowLine(sight->bound_3->limit_line, "o");
}
//===================================================================


void ShowEnemy(Enemy *enemy)
{
  ShowPersonageIcon(&(enemy->icon));
  ShowEnemySight(enemy->sight);
}
//===================================================================

