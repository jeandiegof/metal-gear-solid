#ifndef DEBUG_H
#define DEBUG_H

#include <ncursesw/ncurses.h>

#include "inc/vector_line.h"
#include "inc/personage_base.h"
#include "inc/enemy.h"
#include "inc/display.h"
#include "inc/map_manager.h"

void dFlag();

void DebugInt(int input);

void DebugLine(Line *line);

void DebugEnemySightFullLines(const Enemy *enemy);

void DebugEnemySightInstantLines(const Enemy *enemy);

void DebugObjectsFromMap(Map *map);

void DebugPrintMap(Map *map);

#endif // DEBUG_H
