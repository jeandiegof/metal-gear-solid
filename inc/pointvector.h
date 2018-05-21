#ifndef VECTORPOINT_H
#define VECTORPOINT_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "inc/point.h"

/**
 * @brief Definition of VectorInt type.
 */
typedef struct VectorPoint{
  uint16_t size;      /**< Number of slots used so far. */
  uint16_t capacity;  /**< Total quantity of slots available.*/
  Point *data;     /**< Array of integers for data. */
} VectorPoint;



/**
 * @brief Inserts value at the end of the vector.
 *
 * If the underlying data array is full, then calling this function
 * should cause #vector->data to expand to accept this value.
 *
 * Increments #vector->size.
 *
 * @param value[in]
 * @param vector[out]
 */

void VectorPointAppend(const Point value, VectorPoint *vector);

/**
 * @brief Frees the memory allocated for the data array.
 *
 * Freeing the VectorInt struct is left to client code (so it can
 * use any sort of pointer, be it stack or heap, and then clean up.
 *
 * @param vector[out]
 */

void VectorPointFree(VectorPoint *vector);

/**
 * @brief Initiate VectorInt struct.
 *
 * It sets #vector->size to 0, capacity to VECTORINT_DEFAULT_CAPACITY and
 * allocates an appropriate amount of memory (#vector->capacity * sizeof(int))
 * for the underlying data array.
 *
 * @param vector[out]
 */

void VectorPointInit(VectorPoint *vector);

/**
 * @brief Inserts #value at the given #index.
 *
 * If the index is greater than the #vector->size, this function should
 * expand the vector until it is big enough to contain the index and set
 * the value at that index. It should zero-fill all values in between.
 * #vector->size should be incremented accordingly.
 *
 * @param index[in]
 * @param value[in]
 * @param vector[out]
 */

void VectorPointInsert(const uint16_t index, const Point point, VectorPoint *vector);


uint16_t VectorPointSize(const VectorPoint *vector);

/**
 * @brief Returns a value out of a vector at the given index.
 *
 * If the index is below 0 or greater than #vector->size - 1,
 * this function should complain about the index being out of bounds.
 *
 * @param index[in]
 * @param vector[in]
 * @return Point at #index value.
 */

Point VectorPointValue(const int index, const VectorPoint *vector);

// ---- START Private Functions.

/**
 * @brief Doubles the underlying data array capacity
 * if #vector->size >= #vector->capacity.
 *
 *  Changing the size of the array is expensive, so in order to minimize
 * the number of times it's resized, the capacity is doubled each time.
 *
 * @param vector[out]
 */

void VectorPointResizeIfFull(VectorPoint *vector);

// ---- END Private Functions.

#endif // VECTORPOINT_H
