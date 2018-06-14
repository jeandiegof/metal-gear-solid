#include <math.h>

#include "inc/debug.h"

#include "inc/line.h"
#include "inc/rectangle.h"
#include "inc/window.h"
#include "inc/enemy.h"
#include "inc/display.h"
#include "inc/detection.h"

int main(void)
{

  InitWindow();

  Point origin = {40,10};

//  Point obj = {34,9};

  Enemy *enemy = NewEnemy(ANGLE_0, 2, &origin);

//  EnemyRotate(ANGLE_270, enemy);

//  SightShrink(enemy->sight);
//  Line *line = NewLine();

//  RotateEnemy(ANGLE_315, enemy);

//  Point init = LineGetPoint(2,enemy->sight->bound1->offset_line);

//  LineCreate(&init, ANGLE_45, 5, line);

//  Rotate180(&(enemy->icon.point), line);
//  Rotate(&(enemy->icon.point), line);
//  TranslateEnemy(kEast, 10, enemy);
//  TranslateEnemy(kNorth, 5, enemy);

//  ShowPoint(&obj, "o");

  ShowEnemy(enemy);

//  ShowLine(line, U_DOTLINE_NE);

//  if(IsPointInEnemy(&obj, enemy))
//    mvprintw(0,0, "Point is INSIDE!");
//  else
//    mvprintw(0,0, "Point is OUTSIDE!");

  refresh();
//  ShowRectangle(enemy->box, "#");

  DestroyEnemy(enemy);

 while(1);

 endwin();   // Restore normal terminal behavior
}
