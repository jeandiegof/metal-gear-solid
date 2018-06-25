#ifndef DART_STRUCT_H
#define DART_STRUCT_H

#include <stdint.h>
#include <stdbool.h>

#include "inc/point.h"
#include "inc/game_enums.h"

#define DARTS_MAX_NUMBER_ON_MAP 10

typedef struct Dart
{
  Point point;

  Point erased_sight_point;
  bool erase_sight;

  Direction direction;

  bool active;

  uint8_t steps;
} Dart;

#endif // DART_STRUCT_H
