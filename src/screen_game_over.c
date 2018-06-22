#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <stdlib.h>
#include "inc/screen_game_over.h"

void ScreenGameOverInit(WINDOW **window, PANEL **panel) {
  *window = CreateNewWindow(WINDOW_GAME_OVER_LINES, WINDOW_GAME_OVER_COLUMNS,
                            0, 0);
  *panel = CreateNewPanel(*window);

  uint8_t start_line = (WINDOW_GAME_OVER_LINES-7)/2;
  uint8_t start_column = (WINDOW_GAME_OVER_COLUMNS-64)/2;
  mvwprintw(*window, start_line, start_column, "  _____          __  __ ______    ______      ________ _____  _ ");
  mvwprintw(*window, ++start_line, start_column, " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\| |");
  mvwprintw(*window, ++start_line, start_column, "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) | |");
  mvwprintw(*window, ++start_line, start_column, "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /| |");
  mvwprintw(*window, ++start_line, start_column, "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\|_|");
  mvwprintw(*window, ++start_line, start_column, " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_(_)");
}


