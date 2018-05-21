#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

#include "inc/point.h"
#include "inc/pointvector.h"
#include "inc/angles.h"


typedef struct Line
{
  char name[50];

  int16_t lenght;

  int16_t angle;

  VectorPoint points;

  int16_t maxX;

  int16_t maxY;

  int16_t minX;

  int16_t minY;

}Line;
//===================================================================

/**
 * @brief Inserts a Point object at the end of Line.
 *
 * @param point A Point object.
 * @param line A Line object.
 */
void LineAppendPoint(const Point point, Line *line);


void LineCreate(const Point origin,
                const int16_t angle,
                const int16_t lenght,
                Line *line);

/**
 * @brief Free the memory used by line.
 * @param line A Line object.
 */
void LineDestroy(Line *line);


Point LineGetPoint(const uint16_t index, const Line *line);

void LineInsertPoint(const uint16_t index, const Point point, Line *line);

/**
 * @brief Creates a Line object.
 *
 * Creates a Line object using malloc().
 *
 * @param name The name of Line object.
 * @return A pointer to a Line struct.
 */
Line * NewLine(const char name[]);

/**
 * @brief Finds if a specific point has values greater or smaller than
 * the maximuns and minimuns stored in a Line struct.
 *
 * @param point
 * @param line
 *
 * @note Private Function.
 */
static void LineUpdateMaxMinPoints(const Point point, Line *line);

#endif // GEOMETRY_H
