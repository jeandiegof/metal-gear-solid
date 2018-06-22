#ifndef RANKING_H
#define RANKING_H

#include <stdint.h>
#include <ncursesw/panel.h>
#include "inc/window.h"

#define MAX_PLAYER_NAME              10
#define WINDOW_RANKING_LINES         15   
#define WINDOW_RANKING_COLUMNS       MAX_PLAYER_NAME+30
#define TITLE_OFFSET                 14

typedef struct RankingEntry {
  char name[MAX_PLAYER_NAME+1];
  uint16_t score;
} RankingEntry;

typedef enum FileState {
  OPENING_ERROR,
  WRITING_ERROR,
  READING_ERROR,
  EVERYTHING_OK
} FileState;

FileState AddRankingOnFile(RankingEntry *entry, uint8_t entries);
FileState LoadRankingFromFile(RankingEntry *entry, uint8_t *ranking_entries);
void AddEntryOnRanking(RankingEntry *entry_list, RankingEntry this_entry, uint8_t *index);
void DebugRanking(RankingEntry *entry, uint8_t ranking_entries);
void SortRanking(RankingEntry *entry, uint8_t entries);
void ScreenRankingInit(WINDOW **window, PANEL **panel);
void ScreenRankingUpdate(RankingEntry *entry, WINDOW **window);
#endif // RANKING_H