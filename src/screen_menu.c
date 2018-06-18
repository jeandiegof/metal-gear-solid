#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <stdlib.h>
#include "inc/screen_menu.h"

void ScreenMenuInit (MENU **menu, WINDOW **window, PANEL **panel) {
  char *choices[] = {
                    " Novo Jogo  (n)",
                    " Ranking    (r)",
                    " Sair       (s)",
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

  *menu = new_menu((ITEM **)items);
  
  *window = CreateNewWindow(15, 40, 3, 20);
  set_menu_win(*menu, *window);
  set_menu_sub(*menu, derwin(*window, MAX_CHOICES, MARK_SIZE+MAX_CHOICE_SIZE, 5, 9));
  set_menu_mark(*menu, " -> ");

  mvwaddch(*window, 2, 0, ACS_LTEE);
  mvwhline(*window, 2, 1, ACS_HLINE, 38);
  mvwaddch(*window, 2, 39, ACS_RTEE);
  mvwprintw(*window, 1, 12, "METAL GEAR SOLID");

  refresh();
  post_menu(*menu);

  *panel = CreateNewPanel(*window);
}