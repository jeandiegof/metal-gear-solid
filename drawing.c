#include "drawing.h"


void drawEnemy(soEnemy *enemy)
{
	drawPersonage(&(enemy->base));
	drawEnemySight(&(enemy->sight));
}
//===================================================================


void drawPersonage(saPersonageBase *personage)
{
	mvprintw(personage->point.y,
			 personage->point.x,
			 "%s", personage->img); /**< Print personage in x,y position */
}


void drawEnemySight(saSight *sight)
{

	updateDotLineSightImg(sight);

	for(uint8_t i = 0; i < sight->lenght; i++)
	{
		mvprintw(sight->boundry1.points[i].y,
				 sight->boundry1.points[i].x + sight->boundry1.offset[i].x,
				 "%s",sight->boundry1.img);

		mvprintw(sight->boundry2.points[i].y,
				 sight->boundry2.points[i].x + sight->boundry2.offset[i].x,
				 "%s",sight->boundry2.img);
	}
}
//===================================================================


void updateDotLineSightImg(saSight *sight)
{
	// Display boundries with proper orientation.
	switch (sight->angle)
	{
	case angle0:
	case angle180:
		strcpy(sight->boundry1.img, U_DOTLINE_NE);
		strcpy(sight->boundry2.img, U_DOTLINE_NW);
		break;

	case angle45:
	case angle225:
		strcpy(sight->boundry1.img, U_DOTLINE_V);
		strcpy(sight->boundry2.img, U_DOTLINE_H);
		break;

	case angle90:
	case angle270:
		strcpy(sight->boundry1.img, U_DOTLINE_NW);
		strcpy(sight->boundry2.img, U_DOTLINE_NE);
		break;

	case angle135:
	case angle315:
		strcpy(sight->boundry1.img, U_DOTLINE_H);
		strcpy(sight->boundry2.img, U_DOTLINE_V);
		break;

	default:
		printw("\n\nError in drawing.c -> updateDotLineSightImg() -> switch()\n\n");
		refresh();
		while (1);
		break;
	}
}
//===================================================================
