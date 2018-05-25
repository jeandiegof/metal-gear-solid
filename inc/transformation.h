#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <stdint.h>

#include "inc/personages.h"


void RotateSight(const int16_t angle, Sight *sight);


void Rotate45(const Point *origin_point, Line *line);


void Rotate180(const Point *origin_point, Line *line);


void TranslateE(const int16_t scalar, Point *point);


void TranslateN(const int16_t scalar, Point *point);


void TranslateS(const int16_t scalar, Point *point);


void TranslateW(const int16_t scalar, Point *point);





// ---- START Private Functions

void SetBoundryOffset(Sight *sight);

void FillAreaPoints(Sight *sight);

// ---- END Private Functions

#endif // MATRIXMATH_H
