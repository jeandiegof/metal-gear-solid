#include <ncursesw/ncurses.h>
#include "inc/hero.h"
#include "inc/map_manager.h"
#include "inc/game_base.h"

static GameState EvaluatePosition(Map **map, Hero **hero, Point p);
static Point PointToCheck (Hero **hero, Direction direction);

void MoveHero(Map *map, Hero *hero, Direction direction) {
  Point p = PointToCheck(&hero, direction);
  mvprintw(5, 20, "%d %d", p.x, p.y);
  refresh();
  GameState move = EvaluatePosition(&map, &hero, p);

  switch(move) {
    case MOVEMENT_FORBIDDEN:
      break;
    case MOVEMENT_ALLOWED:
      map->matrix[p.y-6][p.x-1] = 'o';
      break;
    case GAME_OVER:
      break; 
    case GAME_COMPLETE:
      break;
    case RUNNING:
    case PAUSED:
      break;
  }
}

static Point PointToCheck (Hero **hero, Direction direction) {
  Point p;
  p.x = (*hero)->base.point.x;
  p.y = (*hero)->base.point.y;

  switch (direction) {
    case UP:
      if(--p.y < MAP_OFFSET_Y) {
        p.y = 0;
      }
      break;
    case DOWN:
      if(++p.y > MAX_HEIGHT + MAP_OFFSET_Y) {
        p.y = 25;
      }
      break;
    case LEFT:
      if(--p.x < MAP_OFFSET_X) {
        p.x = 0;
      }
      break;
    case RIGHT:
      if(++p.x > MAX_LENGTH + MAP_OFFSET_X) {
        p.x = 80;
      }
      break;
  }
  return p;
}

static GameState EvaluatePosition(Map **map, Hero **hero, Point p) {
  Point actual;
  actual.x = (*hero)->base.point.x-MAP_OFFSET_X;
  actual.y = (*hero)->base.point.y-MAP_OFFSET_Y;

  p.y -= MAP_OFFSET_Y; // offset due to the position of the map on screen;
  p.x -= MAP_OFFSET_X; // the same. And what if I just dont sum?

  switch ((*map)->matrix[p.y][p.x]) {
    case '#':
      return MOVEMENT_FORBIDDEN;
      break;
    case '@':
      if (--(*hero)->life == 0) {
        return GAME_OVER;
      } else {
        (*map)->matrix[actual.y][actual.x] = ' ';
        return MOVEMENT_ALLOWED;
      }
      break;
    case '%':
      (*hero)->ammo += 2;
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;
    case '0':
      (*hero)->hostages++;
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;
    case 'K':
      (*hero)->key = 1;
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;
    case 'x':
      if((*hero)->key) {
        return GAME_COMPLETE;
      } else {
        return MOVEMENT_FORBIDDEN;
      }
      break;
    case ' ':
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
    default:
      return MOVEMENT_FORBIDDEN;
  }
}