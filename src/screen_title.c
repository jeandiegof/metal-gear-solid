#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <stdlib.h>
#include "inc/screen_game_over.h"

void ScreenTitleInit(WINDOW **window, PANEL **panel) {
  *window = CreateNewWindow(WINDOW_GAME_OVER_LINES, WINDOW_GAME_OVER_COLUMNS,
                            0, 0);
  *panel = CreateNewPanel(*window);

  uint8_t start_line = 5;
  uint8_t start_column = (WINDOW_GAME_OVER_COLUMNS-64)/2;

  mvwprintw(*window, start_line, start_column,   " __  __ ______ _______       _         _____ ______          _____  ");
  mvwprintw(*window, ++start_line, start_column, "|  \\/  |  ____|__   __|/\\   | |       / ____|  ____|   /\\   |  __ \\ ");
  mvwprintw(*window, ++start_line, start_column, "| \\  / | |__     | |  /  \\  | |      | |  __| |__     /  \\  | |__) |");
  mvwprintw(*window, ++start_line, start_column, "| |\\/| |  __|    | | / /\\ \\ | |      | | |_ |  __|   / /\\ \\ |  _  / ");
  mvwprintw(*window, ++start_line, start_column, "| |  | | |____   | |/ ____ \\| |____  | |__| | |____ / ____ \\| | \\ \\ ");
  mvwprintw(*window, ++start_line, start_column, "|_|  |_|______|  |_/_/_  _\\_\\______|  \\_____|______/_/    \\_\\_|  \\_\\");
  mvwprintw(*window, ++start_line, start_column, "                 / ____|/ __ \\| |    |_   _|  __ \\                  ");
  mvwprintw(*window, ++start_line, start_column, "                | (___ | |  | | |      | | | |  | |                 ");
  mvwprintw(*window, ++start_line, start_column, "                 \\___ \\| |  | | |      | | | |  | |                 ");
  mvwprintw(*window, ++start_line, start_column, "                 ____) | |__| | |____ _| |_| |__| |                 ");
  mvwprintw(*window, ++start_line, start_column, "                |_____/ \\____/|______|_____|_____/                  ");                                                         
}
