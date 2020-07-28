#include "../include/stds_heap.h"

static int32_t Stds_GetLeft( stds_heap_t * );
static int32_t Stds_GetRight( stds_heap_t * );

/**
 *
 */
struct stds_heap_t {
  size_t element_size;
  size_t logical_size;
  size_t capacity;
  void * current_element;
  void **data;
};

/**
 *
 */
void
Stds_HeapCreate( struct stds_heap_t *h ) {}

/**
 *
 */
void
Stds_HeapInsert( struct stds_heap_t *h, void *data ) {}

/**
 *
 */
void *
Stds_HeapExtractRoot( struct stds_heap_t *h ) {
  return NULL;
}

/**
 *
 */
void
Stds_HeapClear( struct stds_heap_t *h ) {}

/**
 *
 */
static int32_t
Stds_HeapGetLeft( stds_heap_t *h ) {
  return -1;
}

/**
 *
 */
static int32_t
Stds_HeapGetRight( stds_heap_t *h ) {
  return -1;
}