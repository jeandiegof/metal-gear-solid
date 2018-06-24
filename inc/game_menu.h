#ifndef SCREEN_MENU_H
#define SCREEN_MENU_H

#include <ncursesw/menu.h>
#include <ncursesw/panel.h>

#include "inc/game_structs.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]));
#define MARK_SIZE          4
#define MAX_CHOICE_SIZE    15
#define MAX_CHOICES        10

void MenuInitScreen(Game *game);

void MenuInitPausedScreen(Game *game);

GameScreen MenuManager(MENU *menu);

GameScreen MenuPausedManager(MENU *menu);

#endif // SCREEN_MENU_H
