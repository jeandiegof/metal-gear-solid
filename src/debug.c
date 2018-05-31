#include "inc/debug.h"

void dFlag()
{
	mvprintw(0,50,"Here!!!");
	refresh();
	getch();
}
//===================================================================


void DebugInt(int input)
{
	mvprintw(0,50,"%d", input);
	refresh();
	getch();
}
//===================================================================

void DebugLine(Line *line)
{
  mvprintw(0,0,"Line Debug:\n");
  printw("Angle: %d \t Lenght: %d\n",line->angle, line->lenght);
  printw("Line Points:\n");
  for(uint8_t i = 0; i < line->lenght; i++)
  {
    printw("Index: %d \t X = %d \t Y = %d\n", i, LineGetPoint(i, line).x, LineGetPoint(i, line).y);
  }
  refresh();
  getch();
}
