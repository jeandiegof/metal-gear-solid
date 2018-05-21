#ifndef DEBUG_H
#define DEBUG_H

#include <ncursesw/ncurses.h>

#include "inc/line.h"
#include "inc/personages.h"

void dSightBoundrypoints(Sight *sight);

void DebugSightBoundryPointsOffset(Sight *sight);

void dFlag();

void DebugInt(int input);

void DebugLine(Line *line);

#endif // DEBUG_H
