#ifndef GAME_UPDATE_H
#define GAME_UPDATE_H

#include "inc/game_enums.h"
#include "inc/game_structs.h"


void GameUpdateScreen();
//===================================================================

void GameUpdateScreenGame(Game *game);
//===================================================================

void GameUpdateScreenMap(Game *game);
//===================================================================

void GameUpdateScreenRanking(Game *game);
//===================================================================

void GameUpdateScreenStatus(Game *game);
//===================================================================



#endif // GAME_UPDATE_H
