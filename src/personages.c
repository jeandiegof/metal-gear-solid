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

// ----- START Static Functions Prototypes

/**
 * @brief Creates a SightBoundry object.
 *
 * Creates a SightBoundry object using malloc().
 *
 * @return A pointer to a SightBoundry struct.
 */
static SightBoundry *NewSightBoundry();
//===================================================================

/**
 * @brief Free the memory used by SightBoundry.
 * @param sight[out] A SightBoundry object.
 */
static void DestroySightBoundry(SightBoundry *boundry);
//===================================================================

/**
 * @brief Creates a Sight object.
 *
 * Creates a Sight object using malloc().
 *
 * @return A pointer to a Sight struct.
 */
static Sight *NewSight();
//===================================================================

/**
 * @brief Free the memory used by Sight.
 * @param sight[out] A Sight object.
 */
static void DestroySight(Sight *sight);
//===================================================================

/**
 * @brief SightBoundryCreateDirectionalLine
 * @param origin
 * @param boundry
 */
static void SightBoundryCreateDirectionalLine(const Point *origin,
                                              SightBoundry *boundry);
//===================================================================

static void SightBoundryCreateOffsetLine(SightBoundry *boundry);
//===================================================================

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
//===================================================================

/**
 * @brief SightCreateBoundryLines
 *
 * @param origin[in]
 */
static void SightCreateBoundries(const Point *origin, Sight *sight);
//===================================================================

// ----- END Static Functions Prototypes




// ----- START Global Functions Definitions

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

  // Validates sight's lenght.
  SightLenghtPolicy(sight_lenght, enemy->sight);

  // Create a Line object for both sight's boundries.
  SightCreateBoundries(&(enemy->icon.point), enemy->sight);

  return enemy;
}
//===================================================================

void DestroyEnemy(Enemy *enemy)
{
  DestroySight(enemy->sight);
  free(enemy);
}
//===================================================================

// ----- END Global Functions Definitions




// ----- START Static Functions Definitions

static SightBoundry *NewSightBoundry()
{
   // Create SightBoundry object.
  SightBoundry *boundry = malloc(sizeof(SightBoundry));

  boundry->directional_line = NewLine();

  boundry->offset_line = NewLine();

  boundry->limit = NewLine();

  return boundry;
}
//===================================================================

static void DestroySightBoundry(SightBoundry *boundry)
{
  DestroyLine(boundry->directional_line);
  DestroyLine(boundry->offset_line);
  DestroyLine(boundry->limit);
  free(boundry);
}
//===================================================================

static Sight *NewSight()
{
  // Create Sight object.
  Sight *sight = malloc(sizeof(Sight));

   sight->angle = ANGLE_0;

  // Create Sight's Boundry 1 object.
  sight->bound1 = NewSightBoundry();
  sight->bound1->angle = ANGLE_45;

  // Create Sight's Boundry 2 object.
  sight->bound2 = NewSightBoundry();
  sight->bound2->angle = ANGLE_315;

  // Set Boundries with characters for a sight angle = 0°.
  strcpy(sight->bound1->img, U_DOTLINE_NE);
  strcpy(sight->bound2->img, U_DOTLINE_NW);

  sight->lenght = 0;

  return sight;
}
//===================================================================

static void DestroySight(Sight *sight)
{
  DestroySightBoundry(sight->bound1);
  DestroySightBoundry(sight->bound2);
  free(sight);
}
//===================================================================

static void SightBoundryCreateDirectionalLine(const Point *origin,
                                              SightBoundry *boundry)
{
  LineCreate(origin,
             boundry->angle,
             boundry->lenght,
             boundry->directional_line);
}
//===================================================================

static void SightBoundryCreateOffsetLine(SightBoundry *boundry)
{
  LineCopy(boundry->directional_line, boundry->offset_line);

  Point *aux_point;

  for(uint16_t i = 1; i < boundry->lenght; i++)
  {
    aux_point = LineGetPointRef(i, boundry->offset_line);
    aux_point->x += i;
    LineInsertPoint(i, aux_point, boundry->offset_line);
  }
}
//===================================================================

static void SightLenghtPolicy(const uint8_t sight_lenght, Sight *sight)
{
  if(sight_lenght >= SIGHT_LENGHT_MAX_SIZE)
  {
    sight->lenght = SIGHT_LENGHT_MAX_SIZE;
  }
  else if(sight_lenght <= SIGHT_LENGHT_MIN_SIZE)
  {
    sight->lenght = SIGHT_LENGHT_MIN_SIZE;
  }
  else
  {
    sight->lenght = sight_lenght;
  }

  sight->bound1->lenght= sight->lenght;
  sight->bound2->lenght= sight->lenght;
}
//===================================================================

static void SightCreateBoundries(const Point *origin, Sight *sight)
{
  // Auxiliar variable to place boundry in the proper origin position.
  Point aux_point;

  // Set X coordinate for both boundries.
  aux_point.x = origin->x + 1;

  // Set origin y for Boundry 1.
  aux_point.y = origin->y - 1;

  // Create directional_line object for Boundry 1.
  SightBoundryCreateDirectionalLine(&aux_point, sight->bound1);

  // Create offset_line object for Boundry 1.
  SightBoundryCreateOffsetLine(sight->bound1);

  // Set origin y for Boundry 2.
  aux_point.y = origin->y + 1;

  // Create directional_line object for Boundry 2.
  SightBoundryCreateDirectionalLine(&aux_point, sight->bound2);

  // Create offset_line object for Boundry 2.
  SightBoundryCreateOffsetLine(sight->bound2);
}
//===================================================================

// ----- END Static Functions Definitions
