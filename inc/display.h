#ifndef DRAWING_H
#define DRAWING_H

#include "inc/rectangle.h"
#include "inc/personage_base.h"
#include "inc/enemy.h"
#include "inc/translation.h"


void ShowPoint(const Point *point, const char img[]);
//===================================================================

void ShowLine(const Line *line, const char img[]);
//===================================================================

void ShowRectangle(const Rectangle *rectangle, const char img[]);
//===================================================================

void ShowEnemy(Enemy *enemy);
//===================================================================

void ShowPersonageIcon(PersonageBase *personage);
//===================================================================

void ShowEnemySight(Sight *sight);
//===================================================================


#endif // DRAWING_H
