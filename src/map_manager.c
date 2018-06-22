#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include "inc/map_manager.h"

int16_t LoadMapFromFile(Map *map) {
  FILE *fp;
  fp = fopen("mapa.txt", "r");
  if (fp == NULL) {
    printw("Error opening file!");
    return -1;
  }

  int16_t c;
  for (int16_t i = 0; i < MAX_HEIGHT; ++i) {
    for (int16_t j = 0; j < MAX_LENGTH+LINE_ENDING_CHARS; ++j) {
      if((c = fgetc(fp)) == EOF) {
        break;
      }
      if(c != '\n' && c != '\t') {
        map->matrix[i][j] = c;
      }
    }
    if(c == EOF) break;
  }
  fclose(fp);

  // for (int16_t i = 0; i < MAX_HEIGHT; ++i) {
  //   for (int16_t j = 0; j < MAX_LENGTH; ++j) {
  //     printw("%c", map->matrix[i][j]);
  //   }
  //   printw("\n");
  // }
  return 0;
}

void LoadObjectsFromMap(Map *map) {
  map->object.enemy_free_index = 0;
  map->object.hostage_free_index = 0;

  for (int16_t i = 0; i < MAX_HEIGHT; ++i)
  {
    for (int16_t j = 0; j < MAX_LENGTH; ++j)
    {
      switch(map->matrix[i][j]) {
        case 'o':
          map->object.hero.x = j;
          map->object.hero.y = i;
          map->object.hero_origin = map->object.hero;
          break;
        case '@':
          map->object.enemy[map->object.enemy_free_index].x = j;
          map->object.enemy[map->object.enemy_free_index].y = i;
          map->object.enemy_free_index++;
          break;
        case '%':
          map->object.power_up.x = j;
          map->object.power_up.y = i;
          break;
        case '0':
          map->object.hostage[map->object.hostage_free_index].x = j;
          map->object.hostage[map->object.hostage_free_index].y = i;
          map->object.hostage_free_index++;
          break;
        case 'K':
          map->object.key.x = j;
          map->object.key.y = i;
          break;
        case 'x':
          map->object.exit.x = j;
          map->object.exit.y = i;
          // hides the key
          map->matrix[i][j] = '#';
          break;
      }
    }
  }
}