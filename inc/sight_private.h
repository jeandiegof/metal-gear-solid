#ifndef SIGHT_H
#define SIGHT_H

#include "sight_structs.h"

#include "inc/map_manager.h"

/**
 * @brief Creates a Sight object.
 *
 * Creates a Sight object using malloc().
 *
 * @return A pointer to a Sight struct.
 */
Sight *NewSight();
//===================================================================

/**
 * @brief Free the memory used by Sight.
 * @param sight[out] A Sight object.
 */
void DestroySight(Sight *sight);
//===================================================================

/**
 * @brief SightCreateBoundries
 * @param angle
 * @param length
 * @param enemy_origin
 * @param sight
 */
void SightCreateBoundries(const int16_t angle,
                          const int16_t length,
                          const Point *enemy_origin,
                          Sight *sight);
//===================================================================

void SightCreateInstantLines(const Map *map, Sight *sight);
//===================================================================

/**
 * @brief SightFill
 * @param sight
 */
void SightFill(const Point *enemy_origin, Sight *sight);
//===================================================================

#endif // SIGHT_H
