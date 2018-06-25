#include <ncursesw/ncurses.h>
#include <stdlib.h>
#include "inc/hero.h"
#include "inc/manager_keyboard.h"

static GameState EvaluatePosition(Map *map, Hero *hero, Point p);
//===================================================================

static Point PointToCheck (Hero *hero, Direction direction);
//===================================================================


Hero *NewHero(uint8_t life, uint8_t ammo, Point *origin)
{
  Hero *hero = malloc(sizeof(Hero));

  hero->speed = 0; // TODO: implement hero speed;
  hero->life = life;
  hero->ammo = ammo;
  hero->hostages = 0;
  hero->key = 0;
  hero->base.point = *origin;
  hero->score = 0;

  return hero;
}
//===================================================================


void DestroyHero(Hero *hero)
{
  free(hero);
}
//===================================================================

GameScreen HeroDetectedSignal(Map *map, Hero *hero)
{
  // IF is hero holding the key THEN close the exit and drops the key in
  // the detected point.
  if(hero->key == 1)
  {
    // Close exit.
    map->matrix[map->object.exit.y][map->object.exit.x] = '#';
    // Drop key.
    map->object.key = hero->base.point;
    // Print key.
    map->matrix[hero->base.point.y][hero->base.point.x] = 'K';
    // Hero doesn't hold the anymore.
    hero->key = 0;
  }

  // Objetc is placed in the initial point.
  hero->base.point = map->object.hero_origin;
  // Print object in initial point.
  map->matrix[map->object.hero_origin.y][map->object.hero_origin.x] = 'o';

  // Loss one life counter.
  hero->life--;

  // IF hero is dead THEN game_over ELSE continue playing.
  if(hero->life <= 0)
    return SCREEN_GAME_OVER;
  else
    return SCREEN_GAME;
}
//===================================================================

void HeroReset(Hero *hero, Point *origin)
{
  hero->speed = 0;
  hero->life = 3;
  hero->ammo = 5;
  hero->hostages = 0;
  hero->key = 0;
  hero->base.point = *origin;
  hero->score = 0;
}
//===================================================================


GameScreen HeroMove(Map *map, Hero *hero, Direction direction)
{
  Point p = PointToCheck(hero, direction);
  GameState game_state = EvaluatePosition(map, hero, p);

  switch(game_state)
  {
    case MOVEMENT_FORBIDDEN:
      break;

    case GAME_COMPLETE:
      hero->score += 50*hero->life;
      hero->score += 10*hero->ammo;
      return SCREEN_GAME_COMPLETE;
      break;

    case MOVEMENT_ALLOWED:
      map->matrix[p.y][p.x] = 'o';
      hero->base.point = p;
      return SCREEN_GAME;
      break;

    case GAME_OVER:
      hero->life = 0;
      return SCREEN_GAME_OVER;
      break;

    case ENEMY_FOUND:
      return HeroDetectedSignal(map, hero);
      break;

    case RUNNING:
    case PAUSED:
      break;
  }
  return SCREEN_GAME;
}
//===================================================================


GameScreen HeroManager(const char option, Map *map, Hero *hero)
{
  GameScreen next_screen = SCREEN_GAME;

  switch(option)
  {
    case 'w':
      next_screen = HeroMove(map, hero, UP);
      hero->last_direction = UP;
      break;

    case 's':
      next_screen = HeroMove(map, hero, DOWN);
      hero->last_direction = DOWN;
      break;

    case 'a':
      next_screen = HeroMove(map, hero, LEFT);
      hero->last_direction = LEFT;
      break;

    case 'd':
      next_screen = HeroMove(map, hero, RIGHT);
      hero->last_direction = RIGHT;
      break;

    default:
      break;
  }

  return next_screen;
}
//===================================================================


static Point PointToCheck(Hero *hero, Direction direction)
{
  Point p;
  p.x = hero->base.point.x;
  p.y = hero->base.point.y;

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
//===================================================================


static GameState EvaluatePosition(Map *map, Hero *hero, Point p)
{
  Point actual;
  actual.x = hero->base.point.x;
  actual.y = hero->base.point.y;

  switch (map->matrix[p.y][p.x]) {
    case '#':
    case 'Z':
      return MOVEMENT_FORBIDDEN;
      break;

    case '@':
    case '.':
      map->matrix[actual.y][actual.x] = ' ';
      return ENEMY_FOUND;
      break;

    case '%':
      hero->ammo += 2;
      map->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;

    case '0':
      hero->hostages++;
      hero->score += 100;
      map->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;

    case 'K':
      hero->key = 1;
      map->matrix[map->object.exit.y][map->object.exit.x] = 'x';
      map->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;

    case 'x':
      if(hero->key)
      {
        map->matrix[actual.y][actual.x] = ' ';
        return GAME_COMPLETE;
      }
      else
      {
        return MOVEMENT_FORBIDDEN;
      }
      break;

    case ' ':
      map->matrix[actual.y][actual.x] = ' ';
      return MOVEMENT_ALLOWED;
      break;

    default:
      return MOVEMENT_FORBIDDEN;
  }
}
//===================================================================
