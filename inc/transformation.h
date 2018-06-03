#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include "inc/enemy.h"

typedef enum Translation
{
  kEast,
  kNorth,
  kSouth,
  kWest
}Translation;

void Rotate45(const Point *origin_point, Line *line);


void Rotate180(const Point *origin_point, Line *line);


void RotateEnemy(const uint16_t rotation_angle, Enemy *enemy);


void TranslateE(const uint16_t scalar, Point *point);


void TranslateN(const uint16_t scalar, Point *point);


void TranslateS(const uint16_t scalar, Point *point);


void TranslateW(const uint16_t scalar, Point *point);


void TranslatePoint(const Translation direction,
                    const uint16_t scalar,
                    Point *point);


void TranslateLine(const Translation direction,
                   const uint16_t scalar,
                   Line *line);


void TranslateRectangle(const Translation direction,
                        const uint16_t scalar,
                        Rectangle *rectangle);


void TranslateEnemy(const Translation direction,
                    const uint16_t scalar,
                    Enemy *enemy);


#endif // MATRIXMATH_H
