#ifndef COLISION_H
#define COLISION_H

#include <stdio.h>
#include <stdbool.h>

#include "inc/enemy.h"


bool AreLinesIntersecting(const Line *line_1, const Line *line_2);


bool IsPointInLine(const Point *point, const Line *line);


bool IsPointInPoint(const Point *point_1, const Point *point_2);


bool IsPointInRectangle(const Point *point, const Rectangle *rec);


bool IsPointInEnemy(const Point *point, const Enemy *enemy);


int16_t IfObjectOverLineGetIndex(const Line *line, const Map *map);

bool IsObjectBetweenPointsHorizontal(const Point *origin_point,
                                     const Point *point,
                                     const Map *map);


bool IsObjectBetweenPointsVertical(const Point *origin_point,
                                   const Point *point,
                                   const Map *map);


bool IsPointAnObject(const Point *point, const Map *map);

#endif // COLISION_H
