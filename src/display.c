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
  ShowLine(sight->bound1->offset_line, sight->bound1->img);
  ShowLine(sight->bound2->offset_line, sight->bound2->img);

//  ShowPoint(LineGetPointRef(1, sight->bound1->directional_line), "8");
//  refresh();
//  ShowLine(sight->bound1->directional_line, "8");
//  ShowLine(sight->bound2->directional_line, "8");
}
//===================================================================


void ShowEnemy(Enemy *enemy)
{
  ShowPersonageBase(&(enemy->icon));
  ShowEnemySight(enemy->sight);
}
//===================================================================


void UpdateDotLineSightImg(Sight *sight)
{
//	// Display boundries with proper orientation.
//	switch (sight->angle)
//	{
//  case ANGLE_0:
//  case ANGLE_180:
//    strcpy(sight->bound1_img, U_DOTLINE_NE);
//    strcpy(sight->bound2_img, U_DOTLINE_NW);
//		break;

//  case ANGLE_45:
//  case ANGLE_225:
//    strcpy(sight->bound1_img, U_DOTLINE_V);
//    strcpy(sight->bound2_img, U_DOTLINE_H);
//		break;

//  case ANGLE_90:
//  case ANGLE_270:
//    strcpy(sight->bound1_img, U_DOTLINE_NW);
//    strcpy(sight->bound2_img, U_DOTLINE_NE);
//		break;

//  case ANGLE_135:
//  case ANGLE_315:
//    strcpy(sight->bound1_img, U_DOTLINE_H);
//    strcpy(sight->bound2_img, U_DOTLINE_V);
//		break;

//	default:
//		printw("\n\nError in drawing.c -> updateDotLineSightImg() -> switch()\n\n");
//		refresh();
//		while (1);
//		break;
//	}
}
//===================================================================

