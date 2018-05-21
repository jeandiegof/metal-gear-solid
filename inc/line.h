/**
 * @file line.h
 * @author Carlo Fornari and Jean Fontena
 * @date 21 may 2018
 *
 * @brief Code to define a Line object for terminal application enviorment.
 *
 * This file has a struct and functions to help a client to implement a Line
 * object in a terminal.
 *
 * The functions in this file don't perform any sort of graphical operation.
 * They only manipulate the mathematical representation in an integer cartesian
 * coordinate system, i.e., xy coordinates in terminal.
 *
 * Line is allocated on the heap. The task to free the memory is left to the
 * client. The memory is freed by calling DestroyLine().
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

#include "inc/point.h"
#include "inc/pointvector.h"
#include "inc/angles.h"

/**
  * @brief Line is a basic geometric object, intended to manage the mathematical
  * representation of a line in the terminal.
  */

typedef struct Line
{
  char name[50];

  int16_t lenght;

  int16_t angle;

  VectorPoint *points;

  int16_t maxX;

  int16_t maxY;

  int16_t minX;

  int16_t minY;

}Line;
//===================================================================

/**
 * @brief Inserts a Point object at the end of Line.
 *
 * @param point[in] A Point object that will be appended to some Line.
 * @param line[out] A Line object.
 */

void LineAppendPoint(const Point *point, Line *line);

/**
 * @brief Creates the points that constitute a Line object.
 *
 * This function creates a *line that starts at the @p origin with size equals
 * to @p lenght. The inclination of the line is determined by @p angle.
 *
 * @param origin[in] Position to the first Point of the Line.
 * @param angle[in] Angle of the Line.
 * @param lenght[in] Line's lenght in pixels.
 * @param line[out] A pointer to a Line.
 *
 * @todo Handle a situation where a line with pre-existing points is a parameter.
 * Now, the function expects an empty *line. Unexpected behavior can occur if
 * a line with pre-existing points is used.
 */
void LineCreate(const Point *origin,
                const int16_t angle,
                const int16_t lenght,
                Line *line);

/**
 * @brief Free the memory used by Line.
 * @param line[out] A Line object.
 */

void DestroyLine(Line *line);

/**
 * @brief Returns a Point inside Line at @p index position.
 *
 * Should be used when the client just wants Point's value.
 * If Point's value will be modified, LineGetPointRef() should be
 * used instead.
 *
 * @param index[in]
 * @param line[in] A Line object.
 * @return The value of some Point inside Line.
 */

const Point LineGetPoint(const uint16_t index, const Line *line);

/**
 * @brief Returns a reference for a Point inside Line at @p index position.
 *
 * Should be used when the client wants to modify Point's value.
 * If Point's value will NOT be modified, LineGetPoint() should be
 * used instead.
 *
 * @param index[in]
 * @param line[out]
 * @return The address of some Point inside Line.
 */

Point *LineGetPointRef(const uint16_t index, const Line *line);

/**
 * @brief
 *
 * @param index
 * @param point
 * @param line
 */

void LineInsertPoint(const uint16_t index, const Point *point, Line *line);

/**
 * @brief Creates a Line object.
 *
 * Creates a Line object using malloc().
 *
 * @param name[in] The name of Line object.
 * @return A pointer to a Line struct.
 */
Line *NewLine(const char name[]);

/**
 * @brief Finds if a specific point has values greater or smaller than
 * the maximuns and minimuns stored in a Line struct.
 *
 * @param point[in]
 * @param line[out]
 *
 * @note Private Function.
 */
static void LineUpdateMaxMinPoints(const Point *point, Line *line);

#endif // GEOMETRY_H
