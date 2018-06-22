#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <stdlib.h>
#include "inc/screen_menu.h"
#include "inc/keyboard_manager.h"

void ScreenMenuInit (MENU **menu, WINDOW **window, PANEL **panel) {
  char *choices[] = {
                    " Novo Jogo  (n)",
                    " Ranking    (r)",
                    " Sair       (S)",
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
  
  //*window = CreateNewWindow(10, 20, 17, 30);
  *window = newwin(10, 20, 17, 30);
  set_menu_win(*menu, *window);
  set_menu_sub(*menu, derwin(*window, MAX_CHOICES, MARK_SIZE+MAX_CHOICE_SIZE, 3, 15));
  set_menu_mark(*menu, " -> ");

  //mvwaddch(*window, 2, 0, ACS_LTEE);
  //mvwhline(*window, 2, 1, ACS_HLINE, 38);
  //mvwaddch(*window, 2, 39, ACS_RTEE);
  //mvwprintw(*window, 1, 12, "METAL GEAR SOLID");  

  refresh();
  post_menu(*menu);

  *panel = CreateNewPanel(*window);
}

Screen MenuManager(MENU **menu) {
  char opt;
  const ITEM *actual_item;
  if(kbhit()) {
    opt = getch();
    switch(opt) {
      case 'w':
        menu_driver(*menu, REQ_UP_ITEM);
        break;
      case 's':
        menu_driver(*menu, REQ_DOWN_ITEM);
        break;
      case 'n':
        return SCREEN_GAME;
        break;
      case 'r':
        return SCREEN_RANKING;
        break;
      case 'S':
        return SCREEN_EXIT_GAME;
        break;
      case 10:
        actual_item = current_item(*menu);
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