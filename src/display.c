#include <ncursesw/ncurses.h>
#include <string.h>

#include "inc/display.h"


void ShowLine(const Line *line, const char img[])
{
  for(uint8_t i = 0; i < line->lenght; i++)
  {
    mvprintw(LineGetPoint(i,line).y,
             LineGetPoint(i,line).x,
             "%s", img);
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

  ShowLine(sight->bound1, sight->bound1_img);
  ShowLine(sight->bound2, sight->bound2_img);
//  UpdateDotLineSightImg(sight);
//	for(uint8_t i = 0; i < sight->lenght; i++)
//	{
//		mvprintw(sight->bound1.points[i].y,
//				 sight->bound1.points[i].x + sight->bound1.offset[i].x,
//				 "%s",sight->bound1_img);

//		mvprintw(sight->bound2.points[i].y,
//				 sight->bound2.points[i].x + sight->bound2.offset[i].x,
//				 "%s",sight->bound2_img);
//	}
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
	// Display boundries with proper orientation.
	switch (sight->angle)
	{
  case ANGLE_0:
  case ANGLE_180:
    strcpy(sight->bound1_img, U_DOTLINE_NE);
    strcpy(sight->bound2_img, U_DOTLINE_NW);
		break;

  case ANGLE_45:
  case ANGLE_225:
    strcpy(sight->bound1_img, U_DOTLINE_V);
    strcpy(sight->bound2_img, U_DOTLINE_H);
		break;

  case ANGLE_90:
  case ANGLE_270:
    strcpy(sight->bound1_img, U_DOTLINE_NW);
    strcpy(sight->bound2_img, U_DOTLINE_NE);
		break;

  case ANGLE_135:
  case ANGLE_315:
    strcpy(sight->bound1_img, U_DOTLINE_H);
    strcpy(sight->bound2_img, U_DOTLINE_V);
		break;

	default:
		printw("\n\nError in drawing.c -> updateDotLineSightImg() -> switch()\n\n");
		refresh();
		while (1);
		break;
	}
}
//===================================================================

