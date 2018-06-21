#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include "inc/hero.h"
#include "inc/keyboard_manager.h"

static GameState EvaluatePosition(Map **map, Hero **hero, Point p);
static Point PointToCheck (Hero **hero, Direction direction);

Hero NewHero(uint8_t life, uint8_t ammo, Point *origin) {
  Hero hero;

  hero.speed = 0; // TODO: implement hero speed;
  hero.life = life;
  hero.ammo = ammo;
  hero.hostages = 0;
  hero.key = 0;
  hero.base.point = *origin;
  hero.score = 0;

  return hero;
}

void ResetHero(Hero *hero, Point *origin) {
  hero->speed = 0;
  hero->life = 3;
  hero->ammo = 5;
  hero->hostages = 0;
  hero->key = 0;
  hero->base.point = *origin;
  hero->score = 0;
}

Screen MoveHero(Map *map, Hero *hero, Direction direction) {
  Point p = PointToCheck(&hero, direction);
  mvprintw(5, 20, "%03d %03d", p.x, p.y);
  refresh();
  GameState game_state = EvaluatePosition(&map, &hero, p);

  switch(game_state) {
    case MOVEMENT_FORBIDDEN:
      break;
    case GAME_COMPLETE:
      hero->score += 50*hero->life;
      hero->score += 10*hero->ammo;
      return SCREEN_GAME_COMPLETE;
      // FALLTHROUGH
    case MOVEMENT_ALLOWED:
      map->matrix[p.y][p.x] = 'o';
      hero->base.point.x = p.x;
      hero->base.point.y = p.y;
      break;
    case GAME_OVER:
      hero->life = 0;
      return SCREEN_GAME_OVER;
      break; 
    case RUNNING:
    case PAUSED:
      break;
  }
  return SCREEN_GAME;
}

Screen HeroManager(Map *map, Hero *hero) {
  char opt;
  Screen next_screen = SCREEN_GAME;
  if(kbhit()) {
    opt = getch();
    switch(opt) {
      case 'w':
        next_screen = MoveHero(map, hero, UP);
        break;
      case 's':
        next_screen = MoveHero(map, hero, DOWN);
        break;
      case 'a':
        next_screen = MoveHero(map, hero, LEFT);
        break;
      case 'd':
        next_screen = MoveHero(map, hero, RIGHT);
        break;
    }
  }
  return next_screen;
}

static Point PointToCheck (Hero **hero, Direction direction) {
  Point p;
  p.x = (*hero)->base.point.x;
  p.y = (*hero)->base.point.y;

  switch (direction) {
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

static GameState EvaluatePosition(Map **map, Hero **hero, Point p) {
  Point actual;
  actual.x = (*hero)->base.point.x;
  actual.y = (*hero)->base.point.y;

  switch ((*map)->matrix[p.y][p.x]) {
    case '#':
      return MOVEMENT_FORBIDDEN;
      break;
    case '@':
      (*map)->matrix[actual.y][actual.x] = ' ';
      if (--(*hero)->life == 0) {
        return GAME_OVER;
      } else {
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
      (*hero)->score += 100;
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;
    case 'K':
      (*hero)->key = 1;
      (*map)->matrix[(*map)->object.exit.y][(*map)->object.exit.x] = 'x';
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;
    case 'x':
      if((*hero)->key) {
        (*map)->matrix[actual.y][actual.x] = ' ';
        return GAME_COMPLETE;
      } else {
        return MOVEMENT_FORBIDDEN;
      }
      break;
    case ' ':
      (*map)->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;
    default:
      return MOVEMENT_FORBIDDEN;
  }
}