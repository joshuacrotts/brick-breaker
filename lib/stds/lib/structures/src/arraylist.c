/**
 * arraylist_t implementation
 * (c) 2011 @marekweb
 *
 * Uses dynamic extensible arrays.
 */

#include "../include/arraylist.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

// Initial capacity of the arraylist
#define ARRAYLIST_INITIAL_CAPACITY 4

/**
 * Macro to shift a section of memory by an offset, used when inserting or removing items.
 */
#define arraylist_memshift( s, offset, length )                                                    \
  memmove( ( s ) + ( offset ), ( s ), ( length ) * sizeof( s ) );

/**
 * Create a new, empty arraylist.
 */
arraylist_t *
arraylist_create() {
  arraylist_t *new_list = malloc( sizeof( arraylist_t ) );
  new_list->size        = 0;
  // Allocate the array
  new_list->body = malloc( sizeof( void * ) * ARRAYLIST_INITIAL_CAPACITY );
  assert( new_list->body );
  new_list->capacity = ARRAYLIST_INITIAL_CAPACITY;
  return new_list;
}

/**
 * Allocate sufficient array capacity for at least `size` elements.
 */
void
arraylist_allocate( arraylist_t *l, unsigned int size ) {
  assert( size > 0 );
  if ( size > l->capacity ) {
    unsigned int new_capacity = l->capacity;
    while ( new_capacity < size ) {
      new_capacity *= 2;
    }
    l->body = realloc( l->body, sizeof( void * ) * new_capacity );
    assert( l->body );
    l->capacity = new_capacity;
  }
}

/**
 * Return the number of items contained in the list.
 */
inline unsigned int
arraylist_size( arraylist_t *l ) {
  return l->size;
}

/**
 * Add item at the end of the list.
 */
void
arraylist_add( arraylist_t *l, void *item ) {
  arraylist_allocate( l, l->size + 1 );
  l->body[l->size++] = item;
}

/**
 * Pop (remove and return) an item off the end of the list.
 */
void *
arraylist_pop( arraylist_t *l ) {
  assert( l->size > 0 );
  return l->body[--l->size];
}

/**
 * Return item located at index.
 */
void *
arraylist_get( arraylist_t *l, unsigned int index ) {
  assert( index < l->size );
  return l->body[index];
}

/**
 * Replace item at index with given value.
 */
void
arraylist_set( arraylist_t *l, unsigned int index, void *value ) {
  assert( index < l->size );
  l->body[index] = value;
}

/**
 * Insert item at index, shifting the following items by one spot.
 */
void
arraylist_insert( arraylist_t *l, unsigned int index, void *value ) {
  // Reallocate, if needed
  arraylist_allocate( l, l->size + 1 );

  // Move data to create a spot for the new value
  arraylist_memshift( l->body + index, 1, l->size - index );
  l->body[index] = value;
  l->size++;
}

/**
 * Remove the item at index, shifting the following items back by one spot.
 */
void *
arraylist_remove( arraylist_t *l, unsigned int index ) {
  void *value = l->body[index];
  arraylist_memshift( l->body + index + 1, -1, l->size - index );
  l->size--;
  return value;
}

/**
 * Clear list of all items.
 */
void
arraylist_clear( arraylist_t *l ) {
  l->size = 0;
}

/**
 * Return a slice of the list (of given length starting at index) as a new arraylist.
 */
arraylist_t *
arraylist_slice( arraylist_t *l, unsigned int index, unsigned int length ) {
  assert( index + length <= l->size );
  arraylist_t *new_list = arraylist_create();
  arraylist_allocate( new_list, length );
  memmove( new_list->body, l->body + index, length * sizeof( void * ) );
  new_list->size = length;
  return new_list;
}

/**
 * Return a slice of the list (from index to the end) as a new arraylist.
 */
arraylist_t *
arraylist_slice_end( arraylist_t *l, unsigned int index ) {
  return arraylist_slice( l, index, l->size - index );
}

/**
 * Return a copy of the arraylist.
 */
arraylist_t *
arraylist_copy( arraylist_t *l ) {
  return arraylist_slice_end( l, 0 );
}

/**
 * Append a list onto another, in-place.
 */
void
arraylist_join( arraylist_t *l, arraylist_t *source ) {
  arraylist_splice( l, source, l->size );
}

/**
 * Insert a list into another at the given index, in-place.
 */
void
arraylist_splice( arraylist_t *l, arraylist_t *source, unsigned int index ) {
  // Reallocate, if needed
  arraylist_allocate( l, l->size + source->size );

  // Move data to the right
  arraylist_memshift( l->body + index, source->size, l->size - index );

  // Copy the data over
  memmove( l->body + index, source->body, source->size * sizeof( void * ) );
  l->size += source->size;
}

void
arraylist_destroy( arraylist_t *l ) {
  free( l->body );
  free( l );
}
