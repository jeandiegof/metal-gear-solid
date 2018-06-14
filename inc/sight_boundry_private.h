#ifndef SIGHT_PRIVATE_H
#define SIGHT_PRIVATE_H

#include "inc/sight_structs.h"

/**
 * @brief Creates a SightBoundry object.
 *
 * Creates a SightBoundry object using malloc().
 *
 * @return A pointer to a SightBoundry struct.
 */
SightBoundry *NewSightBoundry();
//===================================================================

/**
 * @brief Free the memory used by SightBoundry.
 * @param sight[out] A SightBoundry object.
 */
void DestroySightBoundry(SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundryGrow
 * @param boundry
 */
void SightBoundryGrow(SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundryCreate
 * @param angle
 * @param length
 * @param enemy_origin
 * @param boundry
 */
void SightBoundryCreate(const int16_t angle,
                        const int16_t length,
                        const Point *ref_point,
                        SightBoundry *boundry);
//===================================================================

/**
 * @brief SightBoundryShrink
 * @param boundry
 */
void SightBoundryShrink(SightBoundry *boundry);
//===================================================================

#endif // SIGHT_PRIVATE_H
