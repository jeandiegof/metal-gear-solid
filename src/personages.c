/*
 * TODO: Recognize all points inside sight area.
 * Store those points for some erase function erase those points before
 * plotting them in new position.
 *
 * TODO: Enemy detection logic.
 * Implement a function to detec if a point is inside sight's area or in
 * the same spot as the enemy. The return should be a boolean type.
*/

#include <stdlib.h>
#include <string.h>

#include "inc/personages.h"

#define SIGHT_LENGHT_MIN_SIZE 1
#define SIGHT_LENGHT_MAX_SIZE 5

/**
 * @brief Creates a Sight object.
 *
 * Creates a Sight object using malloc().
 *
 * @return A pointer to a Sight struct.
 */
static Sight *NewSight();

static void DestroySight(Sight *sight);
/**
 * @brief Validates sight's lenght.
 *
 * Checks if sight's lenght is within the range set by the macros in the
 * begining of this file. If not, set the value of sight lenght so it don't
 * violates the range.
 *
 * @param sight_lenght[in]
 * @param sight[out]
 */
static void SightLenghtPolicy(const uint8_t sight_lenght, Sight *sight);

/**
 * @brief SightCreateBoundryLines
 *
 * @param origin[in]
 */
static void SightCreateBoundries(const Point *origin, Sight *sight);




Enemy *NewEnemy(const Point *origin, const uint8_t sight_lenght)
{
  // Create Enemy object.
  Enemy *enemy = malloc(sizeof(Enemy));

	// Init enemy position.
  enemy->icon.point = *origin;

  // Init enemy image.
  strcpy(enemy->icon.img, U_ENEMY);

  // Create Enemy's Sight object.
  enemy->sight = NewSight();

  // Set Boundries with characters for an angle = 0°.
  strcpy(enemy->sight->bound1_img, U_DOTLINE_NE);
  strcpy(enemy->sight->bound2_img, U_DOTLINE_NW);

  // Validates sight's lenght.
  SightLenghtPolicy(sight_lenght, enemy->sight);

  // Create a Line object for both sight's boundries.
  SightCreateBoundries(&(enemy->icon.point), enemy->sight);

  return enemy;
}

void DestroyEnemy(Enemy *enemy)
{
  DestroySight(enemy->sight);
  free(enemy);
}

static Sight *NewSight()
{
  Sight *sight = malloc(sizeof(Sight));

  // Create Sight's Boundry 1 object;
  sight->bound1 = NewLine();

  // Create Sight's Boundry 2 object;
  sight->bound2 = NewLine();

  sight->angle = ANGLE_0;

  sight->bound1->angle = ANGLE_45;

  sight->bound2->angle = ANGLE_315;

  sight->lenght = 0;

  return sight;
}

static void DestroySight(Sight *sight)
{
  DestroyLine(sight->bound1);
  DestroyLine(sight->bound2);
  free(sight);
}

static void SightLenghtPolicy(const uint8_t sight_lenght, Sight *sight)
{
  if(sight_lenght >= SIGHT_LENGHT_MAX_SIZE)

    sight->lenght = SIGHT_LENGHT_MAX_SIZE;

  else if(sight_lenght <= SIGHT_LENGHT_MIN_SIZE)

    sight->lenght = SIGHT_LENGHT_MIN_SIZE;

  else

    sight->lenght = sight_lenght;
}


static void SightCreateBoundries(const Point *origin, Sight *sight)
{
  // Auxiliar variable to place points in the proper position.
  Point aux_point;

  // Set X coordinate for both boundries.
  aux_point.x = origin->x + 1;

  // Set Y for Boundry 1.
  aux_point.y = origin->y - 1;

  // Create Line object for Boundry 1.
  LineCreate(&aux_point,
             sight->bound1->angle,
             sight->lenght,
             sight->bound1);

  // Set Y for Boundry 2.
  aux_point.y = origin->y + 1;

  // Create Line object for Boundry 2.
  LineCreate(&aux_point,
             sight->bound2->angle,
             sight->lenght,
             sight->bound2);
}
