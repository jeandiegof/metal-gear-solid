#ifndef DEBUG_H
#define DEBUG_H

#include <ncursesw/ncurses.h>

#include "inc/line.h"
#include "inc/personage_base.h"
#include "inc/enemy.h"

void dFlag();

void DebugInt(int input);

void DebugLine(Line *line);

#endif // DEBUG_H
