#include "inc/game_init.h"

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>


void GameInitScreenGameComplete(Game *game)
{
  game->window.game_complete = CreateNewWindow(WINDOW_GAME_COMPLETE_LINES, WINDOW_GAME_COMPLETE_COLUMNS,
                            0, 0);
  game->panel.game_complete = CreateNewPanel(game->window.game_complete);

  uint8_t start_line = (WINDOW_GAME_COMPLETE_LINES-12)/2;
  uint8_t start_column = (WINDOW_GAME_COMPLETE_COLUMNS-57)/2;

  mvwprintw(game->window.game_complete, start_line, start_column,   "               _____          __  __ ______              ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "              / ____|   /\\   |  \\/  |  ____|             ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "             | |  __   /  \\  | \\  / | |__                ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "             | | |_ | / /\\ \\ | |\\/| |  __|               ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "             | |__| |/ ____ \\| |  | | |____              ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "  _____ ____  \\_____/_/___ \\_\\_|  |_|______|_____ ______ ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, " / ____/ __ \\|  \\/  |  __ \\| |    |  ____|__   __|  ____|");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "| |   | |  | | \\  / | |__) | |    | |__     | |  | |__   ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "| |   | |  | | |\\/| |  ___/| |    |  __|    | |  |  __|  ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, "| |___| |__| | |  | | |    | |____| |____   | |  | |____ ");
  mvwprintw(game->window.game_complete, ++start_line, start_column, " \\_____\\____/|_|  |_|_|    |______|______|  |_|  |______|");
}
//===================================================================


void GameInitScreenGameOver(Game *game)
{
  game->window.game_over = CreateNewWindow(WINDOW_GAME_OVER_LINES,
                                           WINDOW_GAME_OVER_COLUMNS,
                                           0, 0);
  game->panel.game_over = CreateNewPanel(game->window.game_over);

  uint8_t start_line = (WINDOW_GAME_OVER_LINES-7)/2;
  uint8_t start_column = (WINDOW_GAME_OVER_COLUMNS-64)/2;
  mvwprintw(game->window.game_over, start_line, start_column, "  _____          __  __ ______    ______      ________ _____  _ ");
  mvwprintw(game->window.game_over, ++start_line, start_column, " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\| |");
  mvwprintw(game->window.game_over, ++start_line, start_column, "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) | |");
  mvwprintw(game->window.game_over, ++start_line, start_column, "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _  /| |");
  mvwprintw(game->window.game_over, ++start_line, start_column, "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\|_|");
  mvwprintw(game->window.game_over, ++start_line, start_column, " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_(_)");
}
//===================================================================


void GameInitScreenMap(Game *game)
{
  game->window.map = CreateNewWindow(WINDOW_GAME_MAP_LINES+WINDOW_OFFSET,
                                     WINDOW_GAME_MAP_COLUMNS+WINDOW_OFFSET,
                                     5, 0);
  game->panel.map = CreateNewPanel(game->window.map);
}
//===================================================================


void GameInitScreenRanking(Game *game)
{
  game->window.ranking = CreateNewWindow(WINDOW_RANKING_LINES,
                                         WINDOW_RANKING_COLUMNS,
                                         WINDOW_RANKING_START_ROW,
                                         WINDOW_RANKING_START_COLUMN);
  game->panel.ranking = CreateNewPanel(game->window.ranking);

  mvwhline(game->window.ranking, 2, 1, ACS_HLINE, 38);

  mvwprintw(game->window.ranking, 1, 17, "RANKING");
  mvwprintw(game->window.ranking, 3, 12, "NAME");
  mvwprintw(game->window.ranking, 3, 25, "SCORE");
}
//===================================================================


void GameInitScreenStatus(Game *game)
{
  game->window.status = CreateNewWindow(WINDOW_GAME_STATUS_LINES+WINDOW_OFFSET,
                                        WINDOW_GAME_STATUS_COLUMNS+WINDOW_OFFSET,
                                        0, 0);
  game->panel.status = CreateNewPanel(game->window.status);
}
//===================================================================


void GameInitScreenTitle(Game *game)
{

  game->window.title = CreateNewWindow(WINDOW_GAME_TITLE_LINES, WINDOW_GAME_TITLE_COLUMNS,
                            0, 0);
  game->panel.title = CreateNewPanel(game->window.title);

  uint8_t start_line = 5;
  uint8_t start_column = (WINDOW_GAME_TITLE_COLUMNS-66)/2;

  mvwprintw(game->window.title, start_line, start_column,   " __  __ ______ _______       _         _____ ______          _____  ");
  mvwprintw(game->window.title, ++start_line, start_column, "|  \\/  |  ____|__   __|/\\   | |       / ____|  ____|   /\\   |  __ \\ ");
  mvwprintw(game->window.title, ++start_line, start_column, "| \\  / | |__     | |  /  \\  | |      | |  __| |__     /  \\  | |__) |");
  mvwprintw(game->window.title, ++start_line, start_column, "| |\\/| |  __|    | | / /\\ \\ | |      | | |_ |  __|   / /\\ \\ |  _  / ");
  mvwprintw(game->window.title, ++start_line, start_column, "| |  | | |____   | |/ ____ \\| |____  | |__| | |____ / ____ \\| | \\ \\ ");
  mvwprintw(game->window.title, ++start_line, start_column, "|_|  |_|______|  |_/_/_  _\\_\\______|  \\_____|______/_/    \\_\\_|  \\_\\");
  mvwprintw(game->window.title, ++start_line, start_column, "                 / ____|/ __ \\| |    |_   _|  __ \\                  ");
  mvwprintw(game->window.title, ++start_line, start_column, "                | (___ | |  | | |      | | | |  | |                 ");
  mvwprintw(game->window.title, ++start_line, start_column, "                 \\___ \\| |  | | |      | | | |  | |                 ");
  mvwprintw(game->window.title, ++start_line, start_column, "                 ____) | |__| | |____ _| |_| |__| |                 ");
  mvwprintw(game->window.title, ++start_line, start_column, "                |_____/ \\____/|______|_____|_____/                  ");
}
//===================================================================
