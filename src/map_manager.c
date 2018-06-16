#include <stdio.h>
#include <stdlib.h>
#include <ncursesw/ncurses.h>
#include "inc/map_manager.h"

int16_t LoadMapFromFile(Map *map) {
  FILE *fp;
  fp = fopen("mapa.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!");
    return -1;
  }

  int c;
  for (int i = 0; i < MAX_HEIGHT; ++i) {
    for (int j = 0; j < MAX_LENGTH+LINE_ENDING_CHARS; ++j) {
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

  for (int i = 0; i < MAX_HEIGHT; ++i) {
    for (int j = 0; j < MAX_LENGTH; ++j) {
      printf("%c", map->matrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}