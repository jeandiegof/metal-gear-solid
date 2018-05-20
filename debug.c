#include "debug.h"

void dSightBoundrypoints(Sight *sight)
{
	printw("\n\nBoundry1 \tBoundry2\n");
	printw(" x \t y \t x \t y\n");
	for(int i=0; i < sight->lenght; i++)
	{
		printw("%d \t%d \t%d \t%d\n",
			   sight->bound1.points[i].x,
			   sight->bound1.points[i].y,
			   sight->bound2.points[i].x,
			   sight->bound2.points[i].y);
	}

	refresh();
	getch();
}
//===================================================================

void DSightBoundryPointsOffset(Sight *sight)
{
	printw("\n\nBoundry1 \tBoundry2\n");
	printw(" x \t y \t x \t y\n");
	for(int i=0; i < sight->lenght; i++)
	{
		printw("%d \t%d \t%d \t%d\n",
			   sight->bound1.points[i].x + sight->bound1.offset[i].x,
			   sight->bound1.points[i].y + sight->bound1.offset[i].y,
			   sight->bound2.points[i].x + sight->bound2.offset[i].x,
			   sight->bound2.points[i].y + sight->bound2.offset[i].y);
	}

	refresh();
	getch();
}
//===================================================================


void dFlag()
{
	mvprintw(0,50,"Here!!!");
	refresh();
	getch();
}
//===================================================================


void dInt(int input)
{
	mvprintw(0,50,"%d", input);
	refresh();
	getch();
}
//===================================================================
