#ifndef DART_H
#define DART_H

#include "inc/point.h"
#include "hero.h"

typedef struct Dart {
  Point position;
  Direction direction;
  uint8_t is_started;
  uint8_t steps;
} Dart;

void DartInit(Dart *dart, Hero *hero, Direction direction);
Point DartPointToCheck(Dart dart);
GameState DartEvaluatePosition(Map *map, Dart *dart, Point p);

#endif // DART_H