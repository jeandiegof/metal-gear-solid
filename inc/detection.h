#ifndef COLISION_H
#define COLISION_H

#include <stdio.h>
#include <stdbool.h>

#include "inc/enemy.h"

bool IsPointInPoint(const Point *point_1, const Point *point_2);


bool IsPointInRectangle(const Point *point, const Rectangle *rec);


bool IsPointInEnemy(const Point *point, const Enemy *enemy);

#endif // COLISION_H
