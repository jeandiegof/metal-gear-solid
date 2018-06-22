#ifndef VECTOR_ENEMY_H
#define VECTOR_ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "inc/enemy.h"

#define VECTOR_ENEMY_DEFAULT_CAPACITY 4

/**
 * @brief Definition of VectorInt type.
 *
 * This is a dynamic vector. Initial capcaity is determined by the macro
 * @p VECTOR_POINT_DEFAULT_CAPACITY.
 */
typedef struct VectorEnemy
{
  /** Number of slots used so far. */
  uint16_t length;

  /** Total quantity of slots available.*/
  uint16_t capacity;

  /** Array of Enemys */
  Enemy **data;

} VectorEnemy;


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
void VectorEnemyAppend(Enemy *value, VectorEnemy *vector);
//===================================================================

/**
 * @brief Frees the memory allocated for the VectorEnemy.
 *
 * Freeing the VectorEnemy struct is left to client code (so it can
 * use any sort of pointer, be it stack or heap, and then clean up.
 *
 * @param vector[out] A pointer to the VectorEnemy that should be destroyed.
 */
void DestroyVectorEnemy(VectorEnemy *vector);
//===================================================================

/**
 * @brief Initiate VectorInt struct.
 *
 * It sets @p vector->size to 0, capacity to @p VECTOR_POINT_DEFAULT_CAPACITY and
 * allocates an appropriate amount of memory (@p vector->capacity * sizeof(int))
 * for the underlying data array.
 *
 * @return A pointer to the VectorEnemy created.
 */
VectorEnemy *NewVectorEnemy();
//===================================================================

/**
 * @brief Returns a reference to a Enemy inside VectorEnemy at @p index position.
 *
 * Should be used when the client wants to modify Enemy's value.
 * If Enemy's value will NOT be modified, VectorEnemyValue() should be
 * used instead.
 *
 * This function will throw an error message and exit the code if
 * @p index >= @p vector->size || @p index < 0.
 *
 * @param index[in]
 * @param vector[in]
 * @return The address of some Enemy inside VectorEnemy.
 */
Enemy *VectorEnemyGetByIndex(const int index, const VectorEnemy *vector);
//===================================================================

Enemy *VectorEnemyGetByPoint(const Point *point, const VectorEnemy *vector);
//===================================================================

/**
 * @brief VectorEnemyRemoveLastPoint
 * @param vector
 */
void VectorEnemyRemoveLastEnemy(VectorEnemy *vector);
//===================================================================

/**
 * @brief VectorEnemyReset
 * @param vector
 */
void VectorEnemyReset(VectorEnemy *vector);
//===================================================================

#endif // VECTOR_ENEMY_H
