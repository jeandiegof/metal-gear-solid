#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "inc/point.h"

#define MAX_LENGTH          80
#define MAX_HEIGHT          25
#define LINE_ENDING_CHARS   2
#define MAX_ENEMIES         20

typedef struct Map {
  int16_t matrix[MAX_HEIGHT][MAX_LENGTH];
  Point hero;
  Point enemy;
  Point power_up;
  Point hostage;
  Point key;
  Point exit;
} Map;

int16_t LoadMapFromFile(Map *map);

#endif // MAP_LOADER_H