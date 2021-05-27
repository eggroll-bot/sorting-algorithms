#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Description:
// A struct for the Stack ADT.
//
// Members:
// uint32_t top - Index of the next empty slot in the stack.
// uint32_t capacity - Capacity of the stack.
// int64_t *items - Holds the items.
struct Stack {
	uint32_t top;
	uint32_t capacity;
	int64_t *items;
};

// Description:
// Initializes a stack with a specified capacity.
//
// Parameters:
// uint32_t capacity - The max capacity of the stack.
//
// Returns:
// Stack * - A pointer to the newly initialized stack.
Stack *stack_create( uint32_t capacity ) {
	Stack *s = ( Stack * ) malloc( sizeof( Stack ) );

	if ( s ) { // Make sure the memory allocated successfully to the struct.
		s->top = 0;
		s->capacity = capacity;
		s->items = ( int64_t * ) calloc( capacity, sizeof( int64_t ) );

		if ( !s->items ) { // s->items could not be allocated memory.
			free( s );
			s = NULL;
		}
	}

	return s;
}

// Description:
// Frees the memory given to a stack.
//
// Parameters:
// Stack **s - A pointer to a pointer to the stack to free the memory of.
//
// Returns:
// Nothing.
void stack_delete( Stack **s ) {
	if ( *s && ( *s )->items ) { // Make sure the stack wasn't already deleted.
		free( ( *s )->items );
		free( *s );
		*s = NULL;
	}
}

// Description:
// Checks if a stack is empty.
//
// Parameters:
// Stack *s - The stack to check.
//
// Returns:
// bool - Whether the stack is empty.
bool stack_empty( Stack *s ) {
	return s->top == 0;
}

// Description:
// Checks if a stack is full.
//
// Parameters:
// Stack *s - The stack to check.
//
// Returns:
// bool - Whether the stack is full.
bool stack_full( Stack *s ) {
	return s->top == s->capacity;
}

// Description:
// Checks the size of a stack.
//
// Parameters:
// Stack *s - The stack to check.
//
// Returns:
// uint32_t - The size of the stack.
uint32_t stack_size( Stack *s ) {
	return s->top;
}

// Description:
// Pushes a value to a stack.
//
// Parameters:
// Stack *s - The stack to push to.
// int64_t x - The value to push to the stack.
//
// Returns:
// bool - Whether the operation was successful.
bool stack_push( Stack *s, int64_t x ) {
	if ( stack_full( s ) ) {
		return false;
	}

	s->items[ s->top ] = x;
	s->top++;

	return true;
}

// Description:
// Pops a value from a stack.
//
// Parameters:
// Stack *s - The stack to pop from.
// int64_t *x - A pointer to a int64_t to set the popped value to.
//
// Returns:
// bool - Whether the operation was successful.
bool stack_pop( Stack *s, int64_t *x ) {
	if ( stack_empty( s ) ) {
		return false;
	}

	*x = s->items[ s->top - 1 ];
	s->top--;

	return true;
}
