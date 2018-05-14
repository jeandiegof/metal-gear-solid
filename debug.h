#ifndef DEBUG_H
#define DEBUG_H

#include <ncursesw/ncurses.h>

#include "personages.h"

void dSightBoundrypoints(saSight *sight);

void dSightBoundryPointsOffset(saSight *sight);

void dFlag();

void dInt(int input);

#endif // DEBUG_H
