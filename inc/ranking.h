#ifndef RANKING_H
#define RANKING_H

#include <ncursesw/panel.h>
#include <stdbool.h>
#include <stdint.h>

#include "inc/game_enums.h"
#include "inc/window.h"


#define RANKING_MAX_PLAYER_NUMBER  10
#define MAX_PLAYER_NAME_LENGTH     10

typedef struct RankingEntry
{
  char name[MAX_PLAYER_NAME_LENGTH+1];
  uint16_t score;
} RankingEntry;

typedef struct Ranking
{
  RankingEntry entry[RANKING_MAX_PLAYER_NUMBER];
  uint8_t entries;
}Ranking;


void RankingAddEntry(const RankingEntry *entry, Ranking *rank);
//===================================================================

FileState RankingaSaveOnFile(Ranking *rank);
//===================================================================

FileState RankingLoadFromFile(Ranking *rank);
//===================================================================

#endif // RANKING_H
