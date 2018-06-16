#include <ncursesw/ncurses.h>
#include <locale.h>

#include "inc/window.h"

static void InitWindowColors();

void InitWindow()
{
  // Enable the use of unicodes.
	setlocale(LC_ALL, "en_US.utf8");

  // Configure window to use colors.
  InitWindowColors();

  // Don't echo any keypresses
  noecho();

  // Don't display a cursor
  curs_set(FALSE);
}

static void InitWindowColors()
{
  // Init the window.
  initscr();

  // Enable the use of colors.
  start_color();

  // Enable the use of number -1 as transparent color.
  use_default_colors();

  // Define color pairs.
  init_pair(1, COLOR_RED, -1);
  init_pair(2, COLOR_BLUE, -1);
  init_pair(3, -1, COLOR_YELLOW);
}

WINDOW *CreateNewWindow(uint16_t lines, uint16_t columns,
                      uint16_t start_x, uint16_t start_y) {
  WINDOW *window;
  window = newwin(lines, columns, start_x, start_y);
  box(window, 0, 0);

  return window;
}

PANEL *CreateNewPanel(WINDOW *window) {
  PANEL *panel;
  panel = new_panel(window);
  update_panels();
  return panel;
}
