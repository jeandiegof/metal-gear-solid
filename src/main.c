#include <math.h>

#include "inc/debug.h"

#include "inc/line.h"
#include "inc/rectangle.h"
#include "inc/window.h"
#include "inc/enemy.h"
#include "inc/display.h"

int main(void)
{

  InitWindow();

  Point origin = {40,10};

  Enemy *enemy = NewEnemy(&origin, 3);

  RotateEnemy(ANGLE_0, enemy);

  TranslateEnemy(kEast, 10, enemy);
  TranslateEnemy(kNorth, 5, enemy);

  ShowEnemy(enemy);

//  ShowRectangle(enemy->box, "#");

  DestroyEnemy(enemy);

 while(1);

 endwin();   // Restore normal terminal behavior
}
