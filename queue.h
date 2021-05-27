#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdbool.h>
#include <stdint.h>

typedef struct Queue Queue;

Queue *queue_create( uint32_t capacity );

void queue_delete( Queue **q );

bool queue_empty( Queue *q );

bool queue_full( Queue *q );

uint32_t queue_size( Queue *q );

bool queue_add( Queue *q, int64_t x );

bool queue_remove( Queue *q, int64_t *x );

#endif
