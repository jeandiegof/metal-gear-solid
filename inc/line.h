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
 *
 * The code below provides a simple application to print a line in the
 * terminal using "inc/display.h" and rotating it with "inc/transformation.h":
 * @code
 *  #include "inc/line.h"
 *  #include "inc/transformation.h"
 *  #include "inc/display.h"
 *
 *  int main()
 *  {
 *    Line *line = NewLine();
 *
 *    Point origin = {40,10};
 *
 *    // The parameter 4, is the length of the line in pixels.
 *    LineCreate(&origin, ANGLE_0, 4, line);
 *
 *    // Rotations occurs around a center of rotation, in the funtions below,
 *    // the center is the origin point of line, which is located at index 0.
 *
 *    Rotate45(LineGetPointRef(0,line), line);
 *
 *    Rotate180(LineGetPointRef(0,line), line);
 *
 *    ShowLine(line, ".");
 *
 *    DestroyLine(line);
 *  }
 * @endcode
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

#include "inc/point.h"
#include "inc/vector_point.h"
#include "inc/angles.h"

/**
 * @brief Line is a basic geometric object, intended to manage the mathematical
 * representation of a line in the terminal.
 */
typedef struct Line
{
  int16_t length;

  int16_t angle;

  VectorPoint *points;

  Point direction_vector;

  Point max;
  Point min;

}Line;
//===================================================================

/**
 * @brief Free the memory used by Line.
 * @param line[out] A Line object.
 */
void DestroyLine(Line *line);
//===================================================================

/**
 * @brief Inserts a Point object at the end of Line.
 *
 * @param point[in] A Point object that will be appended to some Line.
 * @param line[out] A Line object.
 */
void LineAppendPoint(const Point *point, Line *line);
//===================================================================

/**
 * @brief LineCopy
 * @param in_line
 * @param out_line
 */
void LineCopy(const Line *in_line, Line *out_line);
//===================================================================

/**
 * @brief Creates the points that constitute a Line object.
 *
 * This function creates a *line that starts at the @p origin with size equals
 * to @p length. The inclination of the line is determined by @p angle.
 *
 * @param origin[in] Position to the first Point of the Line.
 * @param angle[in] Angle of the Line.
 * @param length[in] Line's length in pixels.
 * @param line[out] A pointer to a Line.
 *
 * @todo Handle a situation where a line with pre-existing points is a parameter.
 * Now, the function expects an empty *line. Unexpected behavior can occur if
 * a line with pre-existing points is used.
 */
void LineCreate(const Point *origin,
                const int16_t angle,
                const int16_t input_length,
                Line *line);
//===================================================================

/**
 * @brief LineGetLastPoint
 * @param line[out]
 * @return
 */
Point LineGetLastPoint(const Line *line);
//===================================================================

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
Point LineGetPoint(const uint16_t index, const Line *line);
//===================================================================

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
//===================================================================

/**
 * @brief
 *
 * @param index
 * @param point
 * @param line
 */
void LineInsertPoint(const uint16_t index, const Point *point, Line *line);
//===================================================================

/**
 * @brief LineRemoveLastPoint
 * @param line
 */
void LineRemoveLastPoint(Line *line);

/**
 * @brief LineRemoveAllPoints
 * @param line
 */
void LineReset(Line *line);
//===================================================================

/**
 * @brief LineSetAngle
 */
void LineSetAngle(const int16_t angle, Line *line);
//===================================================================

/**
 * @brief LineSetLength
 * @param length
 * @param line
 */
void LineSetLength(const int16_t length, Line *line);
//===================================================================

/**
 * @brief Creates a Line object.
 *
 * Creates a Line object using malloc().
 *
 * @return A pointer to a Line struct.
 */
Line *NewLine();
//===================================================================


#endif // GEOMETRY_H
