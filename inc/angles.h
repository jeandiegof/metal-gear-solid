#ifndef ANGLES_H
#define ANGLES_H

#include <stdbool.h>

#include "inc/point.h"

#define ANGLE_0     0
#define	ANGLE_45   45
#define ANGLE_90   90
#define ANGLE_135 135
#define ANGLE_180 180
#define ANGLE_225 225
#define ANGLE_270 270
#define ANGLE_315 315


/**
 * @brief AngleCorrection
 * @param angle
 * @return
 */
int16_t AngleCorrection(const int16_t input_angle);

/**
 * @brief Creates a directional vector to describes a parametric equation for
 * some line angle.
 *
 * If angle is not valid, set directional vector to ANGLE_0 direction.
 *
 * @param angle[in|out]
 * @return Directional vector pointing at @p angle.
 */
Point AngleGetDirectionVector(const int16_t angle);

/**
 * @brief AngleIsValid
 * @param angle
 * @return
 */
bool AngleIsValid(const int16_t angle);

#endif // ANGLES_H
