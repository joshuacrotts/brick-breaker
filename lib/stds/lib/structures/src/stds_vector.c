#include "../include/stds_vector.h"

static void Stds_VectorCheckResize( stds_vector_t *, enum SHIFT_DIRECTION );
static void Stds_VectorShift( stds_vector_t *, size_t, enum SHIFT_DIRECTION );

/**
 * Vector structure. Acts the same as a vector in C++ or an ArrayList in Java.
 */
struct stds_vector_t {
  size_t element_size;
  size_t logical_size;
  size_t capacity;
  void **data;
};

/**
 * Creates an ArrayList/C++ vector with the specified type. To get the
 * size, pass in sizeof(T). For instance, sizeof(int32_t).
 *
 * @param size_t size of elements in arraylist.
 *
 * @return void.
 */
stds_vector_t *
Stds_VectorCreate( size_t element_size ) {
  stds_vector_t *v;
  v = malloc( sizeof( stds_vector_t ) );

  if ( v == NULL ) {
    fprintf( stderr, "Error: could not allocate memory for stds_vector_t!\n" );
    exit( EXIT_FAILURE );
  }

  memset( v, 0, sizeof( stds_vector_t ) );
  Stds_VectorClear( v );

  return v;
}

/**
 * Adds an element to the end of a vector. The data must be casted
 * to a void pointer prior to addition. Example:
 *
 * Stds_VectorAppend( v, (void *) 5 );
 *
 * @param stds_vector_t * pointer to vector.
 * @param void * pointer to data (should be casted).
 *
 * @return void.
 */
void
Stds_VectorAppend( stds_vector_t *v, void *data ) {
  Stds_VectorCheckResize( v, RIGHT );
  v->data[v->logical_size] = data;
  v->logical_size++;
}

/**
 * Inserts an element at a specified index.
 *
 * @param stds_vector_t * pointer to vector.
 * @param size_t index of to-be-inserted element.
 * @param void * pointer to data (should be casted).
 *
 * @return void.
 */
void
Stds_VectorInsert( stds_vector_t *v, ssize_t index, void *data ) {
  if ( index < 0 || index >= v->logical_size ) {
    fprintf( stderr, "Failed to insert, index out of bounds error: %zu.\n", index );
    exit( EXIT_FAILURE );
  }
  v->logical_size++;

  /* Check size, then up-shift the elements. */
  Stds_VectorCheckResize( v, RIGHT );
  Stds_VectorShift( v, index, RIGHT );
  v->data[index] = data;
}

/**
 * Returns the data at a specified index.
 *
 * @param const stds_vector_t * pointer to vector.
 * @param size_t index of to-be-received element.
 *
 * @return void.
 */
void *
Stds_VectorGet( const stds_vector_t *v, ssize_t index ) {
  if ( index < 0 || index >= v->logical_size || Stds_VectorIsEmpty( v ) ) {
    fprintf( stderr, "Failed to get element, index out of bounds error: %zu.\n", index );
    exit( EXIT_FAILURE );
  }
  return v->data[index];
}

/**
 * Swaps two elements in a vector.
 * 
 * @param size_t first index to swap.
 * @param size_t second index to swap.
 * 
 * @return void.
 */
inline void 
Stds_VectorSwap( stds_vector_t *v, size_t first, size_t second ) {
  void *tmp = v->data[first];
  v->data[first] = v->data[second];
  v->data[second] = tmp;
}


/**
 * Removes an element from a vector.
 *
 * @param stds_vector_t * pointer to vector.
 * @param size_t index of to-be-removed element.
 *
 * @return void.
 */
void
Stds_VectorRemove( stds_vector_t *v, ssize_t index ) {
  if ( index < 0 || index >= v->logical_size || Stds_VectorIsEmpty( v ) ) {
    fprintf( stderr, "Failed to remove, index out of bounds error: %zu.\n", index );
    exit( EXIT_FAILURE );
  }
  void *removed_data = Stds_VectorGet( v, index );
  v->logical_size--;

  /* Down-shift the elements, then check for capacity problems. */
  Stds_VectorShift( v, index, LEFT );
  Stds_VectorCheckResize( v, LEFT );
}

/**
 * Checks to see if the vector is empty.
 *
 * @param const stds_vector_t * pointer to vector.
 *
 * @return bool true if empty, false otherwise.
 */
bool
Stds_VectorIsEmpty( const stds_vector_t *v ) {
  return v->logical_size == 0;
}

/**
 * Returns the amount of elements current in the vector.
 *
 * @param const stds_vector_t * pointer to vector.
 *
 * @return logical size of vector.
 */
size_t
Stds_VectorSize( const stds_vector_t *v ) {
  return v->logical_size;
}

/**
 * Clears the vector data. The data pointer is reallocated after
 * being freed.
 *
 * @param stds_vector_t * pointer to vector.
 *
 * @return void.
 */
void
Stds_VectorClear( stds_vector_t *v ) {
  free( v->data );

  v->capacity     = STDS_STATIC_MIN_CAP;
  v->logical_size = 0;
  v->data         = malloc( sizeof( v->element_size ) * v->capacity );

  if ( v->data == NULL ) {
    fprintf( stderr, "Error: could not allocate memory for the data void** in stds_vector_t!\n" );
    exit( EXIT_FAILURE );
  }
}

/**
 * Frees the memory allocated by the vector.
 *
 * @param stds_vector_t * pointer to vector.
 *
 * @return void.
 */
void
Stds_VectorDestroy( stds_vector_t *v ) {
  free( v->data );
  free( v );
}

/**
 * Checks to see if the vector needs to be resized. Both cases are
 * handled here (upsizing and downsizing).
 *
 * @param stds_vector_t * pointer to vector.
 * @param enum SHIFT_DIRECTION refers to the last action just performed.
 *        insertions and appends are RIGHT, removals are LEFT.
 *
 * @return void.
 */
static void
Stds_VectorCheckResize( stds_vector_t *v, enum SHIFT_DIRECTION direction ) {
  /* If we need to grow, then the logical size is the same as the capacity. */
  if ( v->logical_size == v->capacity && direction == RIGHT ) {
    v->capacity <<= 1;
    v->data = realloc( v->data, sizeof( v->element_size ) * v->capacity );
  }

  /* If we need to shrink, then the logical size is the same as the capacity / 2. */
  else if ( v->logical_size == ( v->capacity >> 1 ) && direction == LEFT ) {
    v->capacity >>= 1;
    v->data = realloc( v->data, sizeof( v->element_size ) * v->capacity );
  }
}

/**
 * Shifts the vector elements to the right or left by 1.
 *
 * @param stds_vector_t * pointer to vector.
 * @param size_t index to offset to or from.
 * @param enum SHIFT_DIRECTION {LEFT, RIGHT} direction to shift.
 *
 * @return void.
 */
static void
Stds_VectorShift( stds_vector_t *v, size_t offset_index, enum SHIFT_DIRECTION direction ) {
  switch ( direction ) {
  case LEFT:
    for ( uint32_t i = offset_index; i < v->logical_size; i++ ) {
      v->data[i] = v->data[i + 1];
    }
    break;
  case RIGHT:
    for ( uint32_t i = v->logical_size; i >= offset_index; i-- ) {
      v->data[i] = v->data[i - 1];
    }
    break;
  }
}