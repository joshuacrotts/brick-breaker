#ifndef STDS_QUEUE_H
#define STDS_QUEUE_H

#include "../../../include/stds.h"

#include "stds_data.h"

typedef struct stds_queue_t      stds_queue_t;
typedef struct stds_queue_node_t stds_queue_node_t;

/**
 *
 */
struct stds_queue_node_t {
  void *data;
  void *next;
};

extern struct stds_queue_t *Stds_QueueCreate( size_t element_size );

extern void Stds_QueueAdd( struct stds_queue_t *q, void *data );

extern void *Stds_QueuePoll( struct stds_queue_t *q );

extern void Stds_QueueClear( struct stds_queue_t *q );

extern struct stds_queue_node_t *Stds_QueueIterator( struct stds_queue_t *q );

extern void *Stds_QueuePeek( struct stds_queue_t *q );

extern size_t Stds_QueueSize( struct stds_queue_t *q );

extern bool Stds_QueueIsEmpty( struct stds_queue_t *q );

extern void Stds_QueueDestroy( struct stds_queue_t *q );

#endif // STDS_QUEUE_H