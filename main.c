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

 struct soEnemy enemy;
 int x = 40, y = 10;

 initWindow();

 initEnemy(&enemy, x, y, 3);

 rotateSight(&(enemy.sight), angle0);

 drawEnemy(&enemy);

 refresh();

 while(1);

 endwin();   // Restore normal terminal behavior
}
