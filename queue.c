#include "queue.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

// Description:
// A struct for the Queue ADT.
//
// Members:
// uint32_t head - Index of the head of the queue.
// uint32_t tail - Index of the tail of the queue.
// uint32_t size - The number of elements in the queue.
// uint32_t capacity - Capacity of the queue.
// int64_t *items - Holds the items.
struct Queue {
	uint32_t head;
	uint32_t tail;
	uint32_t size;
	uint32_t capacity;
	int64_t *items;
};

// Description:
// Initializes a queue with a specified capacity.
//
// Parameters:
// uint32_t capacity - The max capacity of the queue.
//
// Returns:
// Queue * - A pointer to the newly initialized queue.
Queue *queue_create( uint32_t capacity ) {
	Queue *q = ( Queue * ) malloc( sizeof( Queue ) );

	if ( q ) { // Make sure the memory allocated successfully to the struct.
		q->head = q->size = q->tail = 0;
		q->capacity = capacity;
		q->items = ( int64_t * ) calloc( capacity, sizeof( int64_t ) );

		if ( !q->items ) { // q->items could not be allocated memory.
			free( q );
			q = NULL;
		}
	}

	return q;
}

// Description:
// Frees the memory given to a queue.
//
// Parameters:
// Queue **q - A pointer to a pointer to the queue to free the memory of.
//
// Returns:
// Nothing.
void queue_delete( Queue **q ) {
	if ( *q && ( *q )->items ) { // Make sure the queue wasn't already deleted.
		free( ( *q )->items );
		free( *q );
		*q = NULL;
	}
}

// Description:
// Checks if a queue is empty.
//
// Parameters:
// Queue *q - The queue to check.
//
// Returns:
// bool - Whether the queue is empty.
bool queue_empty( Queue *q ) {
	return q->size == 0;
}

// Description:
// Checks if a queue is full.
//
// Parameters:
// Queue *q - The queue to check.
//
// Returns:
// bool - Whether the queue is full.
bool queue_full( Queue *q ) {
	return q->size == q->capacity;
}

// Description:
// Checks the size of a queue.
//
// Parameters:
// Queue *q - The queue to check.
//
// Returns:
// uint32_t - The size of the queue.
uint32_t queue_size( Queue *q ) {
	return q->size;
}

// Description:
// Enquques an item to a queue.
//
// Parameters:
// Queue *q - The queue to enqueue to.
// int64_t x - The value to enqueue.
//
// Returns:
// bool - Whether the operation was successful.
bool queue_add( Queue *q, int64_t x ) {
	if ( queue_full( q ) ) {
		return false;
	}

	q->items[ q->tail ] = x;
	q->tail++;

	if ( q->tail == q->capacity ) { // Wrap back around to 0 if past the capacity.
		q->tail = 0;
	}

	q->size++;

	return true;
}

// Description:
// Dequeues an item from a queue.
//
// Parameters:
// Queue *q - The queue to dequeue from.
// int64_t *x - A pointer to a int64_t to set the dequeued value to.
//
// Returns:
// bool - Whether the operation was successful.
bool queue_remove( Queue *q, int64_t *x ) {
	if ( queue_empty( q ) ) {
		return false;
	}

	*x = q->items[ q->head ];
	q->head++;

	if ( q->head == q->capacity ) { // Wrap back around to 0 if past the capacity.
		q->head = 0;
	}

	q->size--;

	return true;
}
