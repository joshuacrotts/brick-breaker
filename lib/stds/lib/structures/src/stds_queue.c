#include "../include/stds_queue.h"

/**
 *
 */
struct stds_queue_t {
  size_t             element_size;
  size_t             logical_size;
  stds_queue_node_t *head;
  stds_queue_node_t *tail;
};

/**
 * Creates a queue with the specified type. To get the
 * size, pass in sizeof(T). For instance, sizeof(int32_t).
 *
 * @param size_t size of each individual element.
 *
 * @return void.
 */
stds_queue_t *
Stds_QueueCreate( size_t element_size ) {
  stds_queue_t *q;
  q = malloc( sizeof( stds_queue_t ) );
  memset( q, 0, sizeof( stds_queue_t ) );
  q->element_size = element_size;

  Stds_QueueClear( q );

  return q;
}

/**
 *
 */
void
Stds_QueueAdd( struct stds_queue_t *q, void *data ) {
  stds_queue_node_t *n;
  n = malloc( sizeof( stds_queue_node_t ) );
  memset( n, 0, sizeof( stds_queue_node_t ) );
  n->data = data;
  n->next = NULL;

  /* If there is no head, then we assign it to the head. */
  if ( Stds_QueueIsEmpty( q ) ) {
    q->head = n;
  }

  q->tail->next = n;
  q->tail       = n;
  q->logical_size++;
}

/**
 * Removes the first element in the queue.
 *
 * @param stds_queue_t * pointer to queue.
 *
 * @return first element in queue.
 */
void *
Stds_QueuePoll( struct stds_queue_t *q ) {
  if ( Stds_QueueIsEmpty( q ) ) {
    fprintf( stderr, "Error! Cannot poll on an empty queue.\n" );
    exit( EXIT_FAILURE );
  }

  stds_queue_node_t *n = q->head;
  q->head              = q->head->next;
  return n->data;
}

/**
 *
 */
inline stds_queue_node_t *
Stds_QueueIterator( struct stds_queue_t *q ) {
  return q->head;
}

/**
 * Clears all associated data with the queue. All pointers
 * are reset and memory is re-allocated.
 *
 * @param stds_queue_t * pointer to queue to clear.
 *
 * @return void.
 */
void
Stds_QueueClear( struct stds_queue_t *q ) {
  /* First, go through the pointers and clear them out. */
  stds_queue_node_t *n = q->head;
  stds_queue_node_t *next;

  /* Then, free the memory associated with the list. */
  while ( n != NULL ) {
    next = n->next;
    free( n );
    n = next;
  }

  /* Now, reset the actual associated data. */
  q->logical_size = 0;
  q->head         = malloc( sizeof( stds_queue_node_t ) );
  q->tail         = malloc( sizeof( stds_queue_node_t ) );

  q->tail = q->head;
  q->head = q->tail;

  q->head->next = NULL;
  q->tail->next = NULL;
}

/**
 * Returns the first element in the queue.
 *
 * @param stds_queue_t * pointer to queue.
 *
 * @return first element in queue.
 */
inline void *
Stds_QueuePeek( struct stds_queue_t *q ) {
  if ( Stds_QueueIsEmpty( q ) ) {
    fprintf( stderr, "Error! Cannot peek on an empty queue.\n" );
    exit( EXIT_FAILURE );
  }

  return q->head->data;
}

/**
 * Returns the size of the queue.
 *
 * @param stds_queue_t * pointer to queue.
 *
 * @return logical size.
 */
inline size_t
Stds_QueueSize( struct stds_queue_t *q ) {
  return q->logical_size;
}

/**
 * Determines if the queue is empty or not.
 *
 * @param stds_queue_t * pointer to queue.
 *
 * @return true if logical size is 0, false otherwise.
 */
inline bool
Stds_QueueIsEmpty( struct stds_queue_t *q ) {
  return q->logical_size == 0;
}

/**
 * Frees all associated memory with the queue.
 *
 * @param stds_queue_t * pointer to queue.
 *
 * @return void.
 */
void
Stds_QueueDestroy( struct stds_queue_t *q ) {
  stds_queue_node_t *n = q->head;
  while ( n != NULL ) {
    n = q->head->next;
    free( q->head );
  }
  free( q );
}