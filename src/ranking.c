#include <stdlib.h>
#include <stdio.h>
#include <ncursesw/ncurses.h>
#include "inc/ranking.h"

void ScreenRankingInit(WINDOW **window, PANEL **panel) {
  *window = CreateNewWindow(WINDOW_RANKING_LINES, WINDOW_RANKING_COLUMNS,
                            5, 20);
  *panel = CreateNewPanel(*window);

  mvwaddch(*window, 2, 0, ACS_LTEE);
  mvwhline(*window, 2, 1, ACS_HLINE, 38);
  mvwaddch(*window, 2, WINDOW_RANKING_COLUMNS-1, ACS_RTEE);
  mvwprintw(*window, 1, 17, "RANKING");
}

void ScreenRankingUpdate(RankingEntry *entry, WINDOW **window) {
  uint8_t ranking_entries = 0;
  LoadRankingFromFile(entry, &ranking_entries);
  for (int i = 0; i < ranking_entries; ++i)
  {
    mvwprintw(*window, i+3, 5, "Name: %s", entry[i].name);
    mvwprintw(*window, i+3, 22, "Score: %05d", entry[i].score);
  }
}

void SortRanking(RankingEntry *entry, uint8_t entries) {
  RankingEntry tmp;
  uint8_t again;

  do {
    again = 0;
    for (int i = 0; i < (entries-1); ++i)
    {
      if(entry[i+1].score > entry[i].score) {
        tmp = entry[i];
        entry[i] = entry[i+1];
        entry[i+1] = tmp;
        again = 1;
      }
    }
  } while (again);
}

FileState AddEntriesOnRanking(RankingEntry *entry, uint8_t entries) {
  SortRanking(entry, entries);
  FILE *fp = fopen("ranking.txt", "wb");
  if(fp == NULL) {
    return OPENING_ERROR;
  }
  if(fwrite(entry, sizeof(RankingEntry), entries, fp) != entries) {
    return WRITING_ERROR;
  } else {
    return OK;
  }
  fclose(fp);
}

FileState LoadRankingFromFile(RankingEntry *entry, uint8_t *ranking_entries) {
  FILE *fp = fopen("ranking.txt", "rb");
  *ranking_entries = 0;
  for (int i = 0; i < 10; ++i)
  {
    if(fread(&entry[i], sizeof(RankingEntry), 1, fp)) {
      *ranking_entries += 1;
    } else {
      return (i != 0) ? OK : READING_ERROR;
    }
  }
  fclose(fp);
  return OK;
}

void DebugRanking(RankingEntry *entry, uint8_t ranking_entries) {
  for (int i = 0; i < ranking_entries; ++i)
  {
    printw("Name: %s     Score: %d\n", entry[i].name, entry[i].score);
    refresh();
  }
}