#include "inc/vector_enemy.h"

/**
 * @brief Increase the underlying data array capacity
 * if @p vector->size >= @p vector->capacity.
 *
 * This function expand data array capacity by allocating a number of slots
 * equal to VECTOR_POINT_DEFAULT_CAPACITY.
 *
 * @code
 *  vector->capacity += VECTOR_POINT_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Point) * vector->capacity);
 * @endcode
 *
 * @param vector[out]
 */
static void VectorEnemyResizeIfFull(VectorEnemy *vector);
//===================================================================


void VectorEnemyAppend(Enemy *value, VectorEnemy *vector)
{
  // make sure there's room to expand into
  VectorEnemyResizeIfFull(vector);

  // append the value and increment vector->size
  vector->data[vector->length] = value;

  vector->length++;
}
//===================================================================


void DestroyVectorEnemy(VectorEnemy *vector)
{
  for(uint16_t i = 0; i < vector->length; i++)
  {
    DestroyEnemy(vector->data[i]);
  }
  free(vector->data);
}
//===================================================================


VectorEnemy *NewVectorEnemy()
{
  // Create VectorEnemy.
  VectorEnemy *vector = malloc(sizeof(VectorEnemy));

  // Initialize size and capacity
  vector->length = 0;
  vector->capacity = VECTOR_ENEMY_DEFAULT_CAPACITY;

  // Allocate memory for vector->data
  vector->data = malloc(sizeof(Enemy) * vector->capacity);

  return vector;
}
//===================================================================


Enemy *VectorEnemyGetByIndex(const int index, const VectorEnemy *vector)
{
  if (index >= vector->length || index < 0)
  {
    printf("\n\nIndex %d out of bounds for VectorEnemy of size %d\n\n\n",
         index, vector->length);
    exit(1);
  }
  return vector->data[index];
}
//===================================================================


Enemy *VectorEnemyGetByPoint(const Point *point, const VectorEnemy *vector)
{
  Enemy *aux_enemy;

  for(uint16_t i = 0; i < vector->length; i++)
  {
    aux_enemy = VectorEnemyGetByIndex(i, vector);
    if(point->x == aux_enemy->icon.point.x &&
       point->y == aux_enemy->icon.point.y)
    {
      return aux_enemy;
    }
  }

  return NULL;
}
//===================================================================


void VectorEnemyRemoveLastEnemy(VectorEnemy *vector)
{
  if( vector->length <= 0 )
    return;

  DestroyEnemy(vector->data[vector->length-1]);

  vector->length--;
}
//===================================================================


void VectorEnemyReset(VectorEnemy *vector)
{
  for(uint16_t i = 0; i < vector->length; i++)
  {
    DestroyEnemy(vector->data[i]);
  }
  vector->length = 0;
}
//===================================================================




// ---- START Private Functions.

static void VectorEnemyResizeIfFull(VectorEnemy *vector)
{
  if (vector->length >= vector->capacity)
  {
    vector->capacity += VECTOR_ENEMY_DEFAULT_CAPACITY;
    vector->data = realloc(vector->data, sizeof(Enemy) * vector->capacity);
  }
}
//===================================================================

// ---- END Private Functions.
