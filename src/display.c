#include "inc/display.h"


void ShowEnemy(Enemy *enemy)
{
  ShowPersonage(&(enemy->base));
  ShowEnemySight(&(enemy->sight));
  refresh();
}
//===================================================================


void ShowPersonage(PersonageBase *personage)
{
	mvprintw(personage->point.y,
			 personage->point.x,
			 "%s", personage->img); /**< Print personage in x,y position */
}
//===================================================================

void ShowEnemySight(Sight *sight)
{

  UpdateDotLineSightImg(sight);

	for(uint8_t i = 0; i < sight->lenght; i++)
	{
		mvprintw(sight->bound1.points[i].y,
				 sight->bound1.points[i].x + sight->bound1.offset[i].x,
				 "%s",sight->bound1.img);

		mvprintw(sight->bound2.points[i].y,
				 sight->bound2.points[i].x + sight->bound2.offset[i].x,
				 "%s",sight->bound2.img);
	}
}
//===================================================================


void UpdateDotLineSightImg(Sight *sight)
{
	// Display boundries with proper orientation.
	switch (sight->angle)
	{
  case ANGLE_0:
  case ANGLE_180:
		strcpy(sight->bound1.img, U_DOTLINE_NE);
		strcpy(sight->bound2.img, U_DOTLINE_NW);
		break;

  case ANGLE_45:
  case ANGLE_225:
		strcpy(sight->bound1.img, U_DOTLINE_V);
		strcpy(sight->bound2.img, U_DOTLINE_H);
		break;

  case ANGLE_90:
  case ANGLE_270:
		strcpy(sight->bound1.img, U_DOTLINE_NW);
		strcpy(sight->bound2.img, U_DOTLINE_NE);
		break;

  case ANGLE_135:
  case ANGLE_315:
		strcpy(sight->bound1.img, U_DOTLINE_H);
		strcpy(sight->bound2.img, U_DOTLINE_V);
		break;

	default:
		printw("\n\nError in drawing.c -> updateDotLineSightImg() -> switch()\n\n");
		refresh();
		while (1);
		break;
	}
}
//===================================================================

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
