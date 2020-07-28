#ifndef STDS_STACK_H
#define STDS_STACK_H

#include "../../../include/stds.h"

#include "stds_data.h"

typedef struct stds_stack_t stds_stack_t;

extern stds_stack_t *Stds_StackCreate( size_t element_size );

extern void Stds_StackPush( struct stds_stack_t *s, void *data );

extern void *Stds_StackPop( struct stds_stack_t *s );

extern void Stds_StackClear( struct stds_stack_t *s );

extern void *Stds_StackPeek( struct stds_stack_t *s );

extern size_t Stds_StackSize( struct stds_stack_t *s );

extern bool Stds_StackIsEmpty( struct stds_stack_t *s );

extern void Stds_StackDestroy( struct stds_stack_t *s );

#endif // STDS_STACK_H