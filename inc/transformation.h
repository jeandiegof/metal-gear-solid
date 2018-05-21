#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <stdint.h>

#include "inc/personages.h"


void RotateSight(const int16_t angle, Sight *sight);


void Rotate45(const Point center_point, Line *line);
//void Rotate45(const uint8_t scalar, Point *point, int16_t *angle);


Point TranslateE(const int16_t scalar, Point *point);


Point TranslateN(const int16_t scalar, Point *point);


Point TranslateS(const int16_t scalar, Point *point);


Point TranslateW(const int16_t scalar, Point *point);





// ---- START Private Functions

void SetBoundryOffset(Sight *sight);

void FillAreaPoints(Sight *sight);

// ---- END Private Functions

#endif // MATRIXMATH_H
