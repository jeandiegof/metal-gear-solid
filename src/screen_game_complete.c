#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <stdlib.h>
#include "inc/screen_game_complete.h"

void ScreenGameCompleteInit(WINDOW **window, PANEL **panel) {
  *window = CreateNewWindow(WINDOW_GAME_COMPLETE_LINES, WINDOW_GAME_COMPLETE_COLUMNS,
                            0, 0);
  *panel = CreateNewPanel(*window);

  uint8_t start_line = (WINDOW_GAME_COMPLETE_LINES-12)/2;
  uint8_t start_column = (WINDOW_GAME_COMPLETE_COLUMNS-57)/2;
  
  mvwprintw(*window, start_line, start_column,   "               _____          __  __ ______              ");
  mvwprintw(*window, ++start_line, start_column, "              / ____|   /\\   |  \\/  |  ____|             ");
  mvwprintw(*window, ++start_line, start_column, "             | |  __   /  \\  | \\  / | |__                ");
  mvwprintw(*window, ++start_line, start_column, "             | | |_ | / /\\ \\ | |\\/| |  __|               ");
  mvwprintw(*window, ++start_line, start_column, "             | |__| |/ ____ \\| |  | | |____              ");
  mvwprintw(*window, ++start_line, start_column, "  _____ ____  \\_____/_/___ \\_\\_|  |_|______|_____ ______ ");
  mvwprintw(*window, ++start_line, start_column, " / ____/ __ \\|  \\/  |  __ \\| |    |  ____|__   __|  ____|");
  mvwprintw(*window, ++start_line, start_column, "| |   | |  | | \\  / | |__) | |    | |__     | |  | |__   ");
  mvwprintw(*window, ++start_line, start_column, "| |   | |  | | |\\/| |  ___/| |    |  __|    | |  |  __|  ");
  mvwprintw(*window, ++start_line, start_column, "| |___| |__| | |  | | |    | |____| |____   | |  | |____ ");
  mvwprintw(*window, ++start_line, start_column, " \\_____\\____/|_|  |_|_|    |______|______|  |_|  |______|");
}