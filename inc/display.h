#ifndef DRAWING_H
#define DRAWING_H

#include "inc/enemy.h"
#include "inc/map_manager.h"
#include "inc/personage_base.h"
#include "inc/rectangle.h"
#include "inc/translation.h"


void HidePoint(const Point *point);
//===================================================================

void HideLine(const Line *line);
//===================================================================

void HideEnemySight(Sight *sight, Map *map);
//===================================================================

void HideEnemy(Enemy *enemy, Map *map);
//===================================================================


void ShowPoint(const Point *point, const char img[]);
//===================================================================

void ShowLine(const Line *line, const char img[]);
//===================================================================

void ShowEnemySightBoundry(SightBoundry *boundry, Map *map);
//===================================================================

void ShowEnemySight(Sight *sight, Map *map);
//===================================================================

void ShowEnemy(Enemy *enemy, Map *map);
//===================================================================



#endif // DRAWING_H
