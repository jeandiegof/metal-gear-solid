#include <ncursesw/ncurses.h>
#include "inc/keyboard_manager.h"

uint8_t kbhit () {
  int ch = getch();
  if (ch != ERR) {
    ungetch(ch);
    return 1;
  } else {
    return 0;
  }
}
