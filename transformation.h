#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <stdint.h>

#include "personages.h"


void RotateSight(const enum Angles angle, Sight *sight);


void Rotate45(const uint8_t scalar, Point *point, enum Angles *angle);


void TranslateE(Point *point, const uint8_t scalar);


void TranslateN(Point *point, const uint8_t scalar);


void TranslateS(Point *point, const uint8_t scalar);


void TranslateW(Point *point, const uint8_t scalar);





// ---- START Private Functions

void SetBoundryOffset(Sight *sight);

void FillAreaPoints(Sight *sight);

// ---- END Private Functions

#endif // MATRIXMATH_H
