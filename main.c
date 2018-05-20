#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include "debug.h"

#include "unicodes.h"
#include "window.h"

#include "personages.h"
#include "drawing.h"

int main(void)
{

 struct Enemy enemy;
 int x = 40, y = 10;

 InitWindow();

 InitEnemy(x, y, 3, &enemy);

 RotateSight(kAngle0, &(enemy.sight));

 DrawEnemy(&enemy);

 refresh();

 while(1);

 endwin();   // Restore normal terminal behavior
}
