#include <stdio.h>
#include <stdlib.h>

#include "inc/map_loader.h"

void LoadMapFromFile(int map_matrix[MAP_HEIGHT][MAP_LENGTH]) {
  FILE *fp;
  fp = fopen("mapa.txt", "r");
  if (fp == NULL) {
    printf("Error opening file!");
  }
  
  int c;
  for (int i = 0; i < MAP_HEIGHT; ++i) {
    for (int j = 0; j <= MAP_LENGTH; ++j) {
      c = fgetc(fp);
      if(feof(fp)) break;
      map_matrix[i][j] = (c == 13) ? '\n' : c;
    }
  }
  fclose(fp);
}
