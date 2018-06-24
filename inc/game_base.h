#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "inc/game_structs.h"

Game *NewGame();
//===================================================================

void DestroyGame(Game *game);
//===================================================================

void GameCheckScreenMode(Game *game);
//===================================================================

void GameActiveScreenMode(Game *game);
//===================================================================
#endif // GAME_BASE_H
