#ifndef SCREEN_MENU_H
#define SCREEN_MENU_H

#include "inc/window.h"
#include <ncursesw/menu.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]));
#define MARK_SIZE          4
#define MAX_CHOICE_SIZE    15
#define MAX_CHOICES        10

void ScreenMenuInit (MENU **menu, WINDOW **window, PANEL **panel);

#endif // SCREEN_MENU_H