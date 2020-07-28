#include "../include/stds_queue.h"
#include "../include/stds_stack.h"
#include "../include/stds_vector.h"

// int
// main(int32_targc, char *argv[] ) {
//   stds_queue_t *q;
//   q = Stds_QueueCreate( sizeof( int32_t ) );

//   Stds_QueueAdd( q, ( void * ) 331233 );
//   Stds_QueueAdd( q, ( void * ) 231 );
//   Stds_QueueAdd( q, ( void * ) 3123 );
//   Stds_QueueAdd( q, ( void * ) 3241 );

//   stds_queue_node_t *n;
//   n = Stds_QueueIterator( q );

//   while ( n != NULL ) {
//     Stds_Print( "%d\n", ( ( int32_t * ) ( n->data ) ) );
//     n = n->next;
//   }

//   stds_queue_node_t *r;
//   r = Stds_QueuePoll( q );

//   n = Stds_QueueIterator( q );

//   while ( n != NULL ) {
//     Stds_Print( "%d\n", ( ( int32_t * ) ( n->data ) ) );
//     n = n->next;
//   }
// }