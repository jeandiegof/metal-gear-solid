#ifndef SCREEN_GAME_H
#define SCREEN_GAME_H

#include "inc/window.h"
#include "inc/game_structs.h"
#include "inc/ranking.h"

#define WINDOW_OFFSET                 2

#define WINDOW_GAME_STATUS_LINES      3
#define WINDOW_GAME_STATUS_COLUMNS   80

#define WINDOW_GAME_MAP_LINES        25
#define WINDOW_GAME_MAP_COLUMNS      80

#define WINDOW_GAME_OVER_LINES       33
#define WINDOW_GAME_OVER_COLUMNS     83

#define WINDOW_GAME_TITLE_LINES      33
#define WINDOW_GAME_TITLE_COLUMNS    83

#define WINDOW_GAME_COMPLETE_LINES   33
#define WINDOW_GAME_COMPLETE_COLUMNS 83

#define WINDOW_RANKING_LINES         17
#define WINDOW_RANKING_COLUMNS       MAX_PLAYER_NAME_LENGTH + 30
#define WINDOW_RANKING_START_COLUMN  22
#define WINDOW_RANKING_START_ROW      5
#define TITLE_OFFSET                 14



void GameInitScreenGameComplete(Game *game);
//===================================================================

void GameInitScreenGameOver(Game *game);
//===================================================================

void GameInitScreenMap(Game *game);
//===================================================================

void GameInitScreenRanking(Game *game);
//===================================================================

void GameInitScreenStatus(Game *game);
//===================================================================

void GameInitScreenTitle(Game *game);
//===================================================================


#endif // SCREEN_GAME_H
