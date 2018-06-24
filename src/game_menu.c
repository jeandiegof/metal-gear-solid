#include "inc/game_menu.h"

#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <stdlib.h>

#include "inc/manager_keyboard.h"
#include "inc/window.h"

void MenuInitScreen(Game *game)
{
  char *choices[] = {
                    " Novo Jogo (n)",
                    " Ranking   (r)",
                    " Sair      (ESC)",
                    "",
                  };

  const uint8_t n_choices = ARRAY_SIZE(choices);

  ITEM **items;
  items = calloc(n_choices + 1, sizeof(ITEM *));

  for (int i = 0; i < n_choices; ++i)
  {
    items[i] = new_item(choices[i], choices[3]);
  }
  items[n_choices] = (ITEM *) NULL;

  game->menu = new_menu((ITEM **)items);
  
  game->window.menu = newwin(10, 20, 17, 30);
  set_menu_win(game->menu , game->window.menu);
  set_menu_sub(game->menu , derwin(game->window.menu, MAX_CHOICES, MARK_SIZE+MAX_CHOICE_SIZE, 3, 15));
  set_menu_mark(game->menu , " -> ");

  refresh();
  post_menu(game->menu );

  game->panel.menu = CreateNewPanel(game->window.menu);
}
//===================================================================


void MenuInitPausedScreen(Game *game)
{
  char *choices[] = {
                    " Continuar (c)",
                    " Menu      (m)",
                    " Sair      (ESC)",
                    "",
                  };

  const uint8_t n_choices = ARRAY_SIZE(choices);

  ITEM **items;
  items = calloc(n_choices + 1, sizeof(ITEM *));

  for (int i = 0; i < n_choices; ++i)
  {
    items[i] = new_item(choices[i], choices[3]);
  }
  items[n_choices] = (ITEM *) NULL;

  game->menu_paused = new_menu((ITEM **)items);

  game->window.paused = newwin(10, 20, 17, 30);
  set_menu_win(game->menu_paused , game->window.paused);
  set_menu_sub(game->menu_paused , derwin(game->window.paused, 4, MARK_SIZE+MAX_CHOICE_SIZE, 3, 15));
  set_menu_mark(game->menu_paused , " -> ");

  refresh();
  post_menu(game->menu_paused);

  game->panel.paused = CreateNewPanel(game->window.paused);
}
//===================================================================


GameScreen MenuManager(MENU *menu)
{
  char opt;
  const ITEM *actual_item;
  if(kbhit()) {
    opt = getch();
    switch(opt)
    {
      case 'w':
        menu_driver(menu, REQ_UP_ITEM);
        break;
      case 's':
        menu_driver(menu, REQ_DOWN_ITEM);
        break;
      case 'n':
        return SCREEN_GAME;
        break;
      case 'r':
        return SCREEN_RANKING;
        break;
      case 27:
        return SCREEN_EXIT_GAME;
        break;
      case 10:
        actual_item = current_item(menu);
        const char index = item_index(actual_item);
        switch(index) {
          case 0:
            return SCREEN_GAME;
            break;
          case 1:
            return SCREEN_RANKING;
            break;
          case 2:
            return SCREEN_EXIT_GAME;
            break;
        }
        break;
    }
  }
  return SCREEN_MENU;
}
//===================================================================


GameScreen MenuPausedManager(MENU *menu)
{
  char opt;
  const ITEM *actual_item;
  if(kbhit()) {
    opt = getch();
    switch(opt)
    {
      case 'w':
        menu_driver(menu, REQ_UP_ITEM);
        break;
      case 's':
        menu_driver(menu, REQ_DOWN_ITEM);
        break;
      case 'c':
        return SCREEN_GAME;
        break;
      case 'm':
        return SCREEN_MENU;
        break;
      case 27:
        return SCREEN_EXIT_GAME;
        break;

      case 10:
        actual_item = current_item(menu);
        const char index = item_index(actual_item);
        switch(index) {
          case 0:
            return SCREEN_GAME;
            break;
          case 1:
            return SCREEN_MENU;
            break;
          case 2:
            return SCREEN_EXIT_GAME;
            break;
        }
        break;
    }
  }
  return SCREEN_PAUSED;
}
//===================================================================
