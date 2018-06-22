#include "inc/dart.h"
#include "inc/keyboard_manager.h"

void DartInit(Dart *dart, Hero *hero, Direction direction) {
  if(dart->is_started || hero->ammo == 0) {
    return;
  }

  hero->ammo--;
  dart->steps = 0;
  dart->is_started = 1;
  dart->position = hero->base.point;
  dart->direction = direction;

  switch(dart->direction) {
    case UP:
      if(--dart->position.y < 0) {
        dart->position.y = 0;
      }
      break;
    case DOWN:
      if(++dart->position.y > 25) {
        dart->position.y = 25;
      }
      break;
    case LEFT:
      if(--dart->position.x < 0) {
        dart->position.x = 0;
      }
      break;
    case RIGHT:
      if(++dart->position.x > 80) {
        dart->position.x = 80;
      }
      break;
  }
  mvprintw(5, 10, "%03d %03d", dart->position.x, dart->position.y);
  refresh();
}

Point DartPointToCheck(Dart dart) {
  Point p = dart.position;

  switch(dart.direction) {
    case UP:
      if(--p.y < 0) {
        p.y = 0;
      }
      break;
    case DOWN:
      if(++p.y > 25) {
        p.y = 25;
      }
      break;
    case LEFT:
      if(--p.x < 0) {
        p.x = 0;
      }
      break;
    case RIGHT:
      if(++p.x > 80) {
        p.x = 80;
      }
      break;
  }
  return p;
}

GameState DartEvaluatePosition(Map *map, Dart *dart, Point p) {
  switch(map->matrix[p.y][p.x]) {
    case ' ':
    case '.':
      if(dart->is_started) {
        map->matrix[dart->position.y][dart->position.x] = ' ';
        map->matrix[p.y][p.x] = '-';
        dart->position = p;
        if(++dart->steps == 12) {
          dart->steps = 0;
          dart->is_started = 0;
          map->matrix[dart->position.y][dart->position.x] = ' ';
        }
      }
      return MOVEMENT_ALLOWED;
      break;
    case '#':
    case '%':
    case '0':
    case 'K':
      if(dart->is_started) {
        map->matrix[dart->position.y][dart->position.x] = ' ';
        dart->steps = 0;
        dart->is_started = 0;
      }
    case '@':
      if(dart->is_started) {
        map->matrix[dart->position.y][dart->position.x] = ' ';
        // remove the following line if EnemyHitSignal already handle enemy position on matrix
        map->matrix[p.y][p.x] = ' ';
        dart->steps = 0;
        dart->is_started = 0;
      }
      return ENEMY_FOUND;
      break;
    break;
  }
}