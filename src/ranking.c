#include "inc/ranking.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncursesw/ncurses.h>

static void RankingSort(Ranking *rank);
//===================================================================


void RankingAddEntry(const RankingEntry *entry, Ranking *rank)
{
  if(rank->entries == RANKING_MAX_PLAYER_NUMBER)
  {
    RankingSort(rank);
    if(entry->score >= rank->entry[rank->entries-1].score)
    {
      rank->entry[rank->entries-1] = *entry;
      RankingSort(rank);
    }
  }
  else
  {
    rank->entry[rank->entries] = *entry;
    RankingSort(rank);
    rank->entries++;
  }
} 
//===================================================================


FileState RankingLoadFromFile(Ranking *rank)
{
  FILE *fp = fopen("ranking", "rb");

  if(fp == NULL)
  {
    fp = fopen("ranking", "wb");
    if(fp == NULL)
    {
      return CREATED_FILE_FAILL;
    }
    fflush(fp);
    fclose(fp);
    return CREATED_FILE;
  }

  if(!fread(rank, sizeof(Ranking), 1, fp))
  {
    return READING_ERROR;
  }

  RankingSort(rank);

  fclose(fp);

  return EVERYTHING_OK;
}
//===================================================================


FileState RankingaSaveOnFile(Ranking *rank)
{
  FILE *fp = fopen("ranking", "wb");

  if(fp == NULL)
  {
    return OPENING_ERROR;
  }

  if(fwrite(rank, sizeof(Ranking), 1, fp) != 1)
  {
    return WRITING_ERROR;
  }

  fflush(fp);
  fclose(fp);

  return EVERYTHING_OK;
}
//===================================================================


static void RankingSort(Ranking *rank)
{
  RankingEntry temp_entry;

  bool again;
  do
  {
    again = 0;
    for (int i = 0; i < (rank->entries-1); ++i)
    {
      if(rank->entry[i+1].score > rank->entry[i].score)
      {
        temp_entry = rank->entry[i];
        rank->entry[i] = rank->entry[i+1];
        rank->entry[i+1] = temp_entry;
        again = 1;
      }
    }
  } while (again);
}
//===================================================================
