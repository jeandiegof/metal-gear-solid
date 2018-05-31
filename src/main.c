#include <math.h>

#include "inc/debug.h"

#include "inc/line.h"
#include "inc/rectangle.h"
#include "inc/window.h"
#include "inc/personages.h"
#include "inc/display.h"

int main(void)
{

  InitWindow();

  Point origin = {40,10};

  Enemy *enemy = NewEnemy(&origin, 3);

  ShowEnemy(enemy);

  DestroyEnemy(enemy);
// RotateSight(ANGLE_0, &(enemy.sight));

// DrawEnemy(&enemy);

// Line *line = NewLine();

// Point origin = {40,10};
// Point p2 = {42,10};

// LineCreate(&origin, ANGLE_0, 4, line);

// Rotate45(LineGetPointRef(0,line), line);
// Rotate45(LineGetPointRef(0,line), line);
//// Rotate45(LineGetPointRef(0,line), line);
//// Rotate45(LineGetPointRef(0,line), line);
// Rotate180(LineGetPointRef(0,line), line);

// Rectangle *rec = NewRectangle();

// Point corn_1 = {4,4};
// Point corn_2 = {7,7};

// RectangleCreate(&corn_1, &corn_2, rec);

// ShowRectangle(rec, "#");

// DestroyRectangle(rec);

 while(1);

 endwin();   // Restore normal terminal behavior
}
