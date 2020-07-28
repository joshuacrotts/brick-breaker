#ifndef STDS_HEAP_H
#define STDS_HEAP_H

#include "../../../include/stds.h"

#include "stds_data.h"

typedef struct stds_heap_t stds_heap_t;

extern void Stds_HeapCreate( struct stds_heap_t *s );

extern void Stds_HeapInsert( struct stds_heap_t *s, void *data );

extern void *Stds_HeapExtractRoot( struct stds_heap_t *s );

extern void Stds_HeapClear( struct stds_heap_t *s );

#endif // STDS_HEAP_H