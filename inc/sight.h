#ifndef SIGHT_H
#define SIGHT_H

#include "sight_structs.h"

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

/**
 * @brief SightGrow
 * @param sight
 */
void SightGrow(Sight *sight);
//===================================================================

/**
 * @brief SightGrowBoundry1
 * @param sight
 */
void SightGrowBoundry1(Sight *sight);
//===================================================================

/**
 * @brief SightGrowBoundry2
 * @param sight
 */
void SightGrowBoundry2(Sight *sight);
//===================================================================

/**
 * @brief SightShrink
 * @param sight
 */
void SightShrink(Sight *sight);
//===================================================================

/**
 * @brief SightShrinkBoundry1
 * @param sight
 */
void SightShrinkBoundry1(Sight *sight);
//===================================================================

/**
 * @brief SightShrinkBoundry2
 * @param sight
 */
void SightShrinkBoundry2(Sight *sight);
//===================================================================

#endif // SIGHT_H
