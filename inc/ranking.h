#ifndef RANKING_H
#define RANKING_H

#include <stdint.h>

#define MAX_PLAYER_NAME     10

typedef struct RankingEntry {
  char name[MAX_PLAYER_NAME+1];
  uint16_t score;
} RankingEntry;

typedef enum FileState {
  OPENING_ERROR,
  WRITING_ERROR,
  READING_ERROR,
  OH_GOD_EVERYTHING_WENT_GREAT,
} FileState;

FileState AddEntriesOnRanking(RankingEntry *entry, uint8_t entries);
FileState LoadRankingFromFile(RankingEntry *entry, uint8_t *ranking_entries);
void DebugRanking(RankingEntry *entry, uint8_t ranking_entries);
void SortRanking(RankingEntry *entry, uint8_t entries);
#endif // RANKING_H