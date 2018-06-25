#ifndef MAP_LOADER_H
#define MAP_LOADER_H

#include "inc/point.h"

#define MAX_LENGTH          80
#define MAX_HEIGHT          25
#define LINE_ENDING_CHARS   2
#define MAX_ENEMIES         10
#define MAX_HOSTAGES        10
//#define MAP_OFFSET_X        1
//#define MAP_OFFSET_Y        6

typedef struct MapObjects {
  Point hero;
  Point hero_origin;
  Point enemy[MAX_ENEMIES];
  uint8_t enemy_free_index;
  Point power_up;
  Point hostage[MAX_HOSTAGES];
  uint8_t hostage_free_index;
  Point key;
  Point exit;
} MapObjects;

typedef struct Map {
  int16_t matrix[MAX_HEIGHT][MAX_LENGTH];
  MapObjects object;
} Map;

int16_t MapLoadFromFile(Map *map);
void MapLoadObjects(Map *map);
void MapInit(Map *map);
void MapReset(Map *map);
#endif // MAP_LOADER_H
