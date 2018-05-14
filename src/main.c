#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <map_loader.h>

int main() {

  int map_matrix[MAP_HEIGHT][MAP_LENGTH] = {0};
  
  LoadMapFromFile(map_matrix);
  for (int i = 0; i < MAP_HEIGHT; ++i)
  {
    for (int j = 0; j < MAP_LENGTH; ++j)
    {
      printf("%c", map_matrix[i][j]);
    } 
  }

  printf("\n");
  return 0;
}