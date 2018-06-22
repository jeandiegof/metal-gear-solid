#ifndef VECTOR_LINE_H
#define VECTOR_LINE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "inc/line.h"

#define VECTOR_LINE_DEFAULT_CAPACITY 4

/**
 * @brief Definition of VectorInt type.
 *
 * This is a dynamic vector. Initial capcaity is determined by the macro
 * @p VECTOR_POINT_DEFAULT_CAPACITY.
 */
typedef struct VectorLine
{
  /** Number of slots used so far. */
  uint16_t length;

  /** Total quantity of slots available.*/
  uint16_t capacity;

  /** Array of Lines */
  Line **data;

} VectorLine;


/**
 * @brief Inserts value at the end of the vector.
 *
 * If the underlying data array is full, then calling this function
 * should cause @p vector->data to expand to accept this value.
 *
 * Increments @p vector->size.
 *
 * @param value[in]
 * @param vector[out]
 */
void VectorLineAppend(const Line *value, VectorLine *vector);
//===================================================================


void VectorLineAppendVector(const VectorLine *input, VectorLine *output);
//===================================================================

/**
 * @brief Frees the memory allocated for the VectorLine.
 *
 * Freeing the VectorLine struct is left to client code (so it can
 * use any sort of pointer, be it stack or heap, and then clean up.
 *
 * @param vector[out] A pointer to the VectorLine that should be destroyed.
 */
void DestroyVectorLine(VectorLine *vector);
//===================================================================

/**
 * @brief Initiate VectorInt struct.
 *
 * It sets @p vector->size to 0, capacity to @p VECTOR_POINT_DEFAULT_CAPACITY and
 * allocates an appropriate amount of memory (@p vector->capacity * sizeof(int))
 * for the underlying data array.
 *
 * @return A pointer to the VectorLine created.
 */
VectorLine *NewVectorLine();
//===================================================================

/**
 * @brief Inserts @p value at the given @p index.
 *
 * If the index is greater than the @p vector->size, this function should
 * expand the vector until it is big enough to contain the @p index and set
 * the value at that @p index. It should zero-fill all values in between.
 * @p vector->size should be incremented accordingly.
 *
 * @param index[in]
 * @param value[in]
 * @param vector[out]
 */
void VectorLineInsert(const uint16_t index,
                      const Line *value,
                      VectorLine *vector);
//===================================================================

/**
 * @brief Returns the number of points in the vector.
 * @param vector[in]
 * @return The number of slots used so far in the vector.
 */
uint16_t VectorLineGetSize(const VectorLine *vector);
//===================================================================

/**
 * @brief Returns a reference to a Line inside VectorLine at @p index position.
 *
 * Should be used when the client wants to modify Line's value.
 * If Line's value will NOT be modified, VectorLineValue() should be
 * used instead.
 *
 * This function will throw an error message and exit the code if
 * @p index >= @p vector->size || @p index < 0.
 *
 * @param index[in]
 * @param vector[in]
 * @return The address of some Line inside VectorLine.
 */
Line *VectorLineGetLine(const int index, const VectorLine *vector);
//===================================================================

/**
 * @brief VectorLineRemoveLastPoint
 * @param vector
 */
void VectorLineRemoveLastLine(VectorLine *vector);
//===================================================================

/**
 * @brief VectorLineReset
 * @param vector
 */
void VectorLineReset(VectorLine *vector);
//===================================================================

#endif // VECTOR_LINE_H
