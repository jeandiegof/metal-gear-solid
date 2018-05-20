#include "drawing.h"


void DrawEnemy(Enemy *enemy)
{
	DrawPersonage(&(enemy->base));
	DrawEnemySight(&(enemy->sight));
}
//===================================================================


void DrawPersonage(PersonageBase *personage)
{
	mvprintw(personage->point.y,
			 personage->point.x,
			 "%s", personage->img); /**< Print personage in x,y position */
}
//===================================================================

void DrawEnemySight(Sight *sight)
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
	case kAngle0:
	case kAngle180:
		strcpy(sight->bound1.img, U_DOTLINE_NE);
		strcpy(sight->bound2.img, U_DOTLINE_NW);
		break;

	case kAngle45:
	case kAngle225:
		strcpy(sight->bound1.img, U_DOTLINE_V);
		strcpy(sight->bound2.img, U_DOTLINE_H);
		break;

	case kAngle90:
	case kAngle270:
		strcpy(sight->bound1.img, U_DOTLINE_NW);
		strcpy(sight->bound2.img, U_DOTLINE_NE);
		break;

	case kAngle135:
	case kAngle315:
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
