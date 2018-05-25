#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include "inc/debug.h"

#include "inc/unicodes.h"
#include "inc/line.h"
#include "inc/window.h"
#include "inc/personages.h"
#include "inc/display.h"

int main(void)
{

// struct Enemy enemy;
// int x = 40, y = 10;

 InitWindow();

// InitEnemy(x, y, 3, &enemy);

// RotateSight(ANGLE_0, &(enemy.sight));

// DrawEnemy(&enemy);

 Line *line = NewLine("myline");

 Point origin = {40,10};
 Point p2 = {42,10};

 LineCreate(&origin, ANGLE_0, 4, line);

 Rotate45(LineGetPointRef(0,line), line);
 Rotate45(LineGetPointRef(0,line), line);
// Rotate45(LineGetPointRef(0,line), line);
// Rotate45(LineGetPointRef(0,line), line);
 Rotate180(LineGetPointRef(0,line), line);

// DebugLine(line);
 ShowLine(line, "\\");

 DestroyLine(line);

 while(1);

 endwin();   // Restore normal terminal behavior
}
