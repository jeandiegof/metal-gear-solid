#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <stdint.h>

#include "inc/rectangle.h"
#include "inc/vector_line.h"

typedef enum Translation
{
  kEast,
  kNorth,
  kSouth,
  kWest,
  kStop
}Translation;


/**
 * @brief TranslatePoint
 * @param direction
 * @param scalar
 * @param point
 */
void TranslatePoint(const Translation direction,
                    const uint16_t scalar,
                    Point *point);

/**
 * @brief TranslateLine
 * @param direction
 * @param scalar
 * @param line
 */
void TranslateLine(const Translation direction,
                   const uint16_t scalar,
                   Line *line);


void TranslateVectorLine(const Translation direction,
                         const uint16_t scalar,
                         VectorLine *vector);

/**
 * @brief TranslateRectangle
 * @param direction
 * @param scalar
 * @param rectangle
 */
void TranslateRectangle(const Translation direction,
                        const uint16_t scalar,
                        Rectangle *rectangle);




#endif // MATRIXMATH_H
