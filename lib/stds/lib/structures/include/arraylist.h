#ifndef ARRAYLIST_H
#define ARRAYLIST_H

typedef struct arraylist_t arraylist_t;

void arraylist_destroy( arraylist_t *l );
void arraylist_splice( arraylist_t *l, arraylist_t *source, unsigned int index );
void arraylist_join( arraylist_t *l, arraylist_t *source );
void arraylist_clear( arraylist_t *l );
void arraylist_insert( arraylist_t *l, unsigned int index, void *value );
void arraylist_set( arraylist_t *l, unsigned int index, void *value );
void arraylist_add( arraylist_t *l, void *item );
void arraylist_allocate( arraylist_t *l, unsigned int size );

void *arraylist_get( arraylist_t *l, unsigned int index );
void *arraylist_remove( arraylist_t *l, unsigned int index );
void *arraylist_pop( arraylist_t *l );

unsigned int arraylist_size( arraylist_t *l );

arraylist_t *arraylist_copy( arraylist_t *l );
arraylist_t *arraylist_slice_end( arraylist_t *l, unsigned int index );
arraylist_t *arraylist_slice( arraylist_t *l, unsigned int index, unsigned int length );
arraylist_t *arraylist_create();

struct arraylist_t {
  unsigned int size;     // Count of items currently in list
  unsigned int capacity; // Allocated memory size, in items
  void **      body;     // Pointer to allocated memory for items (of size capacity * sizeof(void*))
};
#endif