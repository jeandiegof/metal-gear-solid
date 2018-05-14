#ifndef MATRIXMATH_H
#define MATRIXMATH_H

#include <stdint.h>

#include "personages.h"


void rotateSight(saSight *sight,enum eAngles inputAngle);


void rotate45(saPoint *point, enum eAngles *angle, uint8_t scalar);


void translateE(saPoint *point, const uint8_t scalar);


void translateN(saPoint *point, const uint8_t scalar);


void translateS(saPoint *point, const uint8_t scalar);


void translateW(saPoint *point, const uint8_t scalar);





// ---- START Private Functions

void setBoundryOffset(saSight *sight);

void fillAreaPoints(saSight *sight);

// ---- END Private Functions

#endif // MATRIXMATH_H
