#include "quick.h"

#include "queue.h"
#include "sorting_statistics.h"
#include "stack.h"

#include <stdint.h>

// Description:
// Sets the max_size if current_size is larger than the current max_size.
//
// Parameters:
// uint32_t current_size - The current size.
// uint32_t *max_size - The pointer to the current max size.
//
// Returns:
// Nothing.
static void set_max_size( uint32_t current_size, uint32_t *max_size ) {
	if ( current_size > *max_size ) {
		*max_size = current_size;
	}
}

// Description:
// Places elements less than the pivot to the left side of the array and elements
// greater than or equal to the pivot onto the right side of the array.
//
// Parameters:
// uint32_t *arr - The array to sort.
// int64_t lo - Starting point.
// int64_t hi - Ending point.
// SortingStatistics *stats - A pointer to a SortingStatistics struct that will hold the stats of the sort.
//
// Returns:
// int64_t - The division of the array.
static int64_t partition( uint32_t *arr, int64_t lo, int64_t hi, SortingStatistics *stats ) {
	uint32_t pivot = arr[ lo + ( ( hi - lo ) / 2 ) ];
	int64_t i = lo - 1;
	int64_t j = hi + 1;

	while ( i < j ) {
		i += 1;

		while ( ++stats->compares && arr[ i ] < pivot ) {
			i += 1;
		}

		j -= 1;

		while ( ++stats->compares && arr[ j ] > pivot ) {
			j -= 1;
		}

		if ( i < j ) {
			// Swap arr[i] and arr[j].
			uint32_t old_arr_i = arr[ i ];
			arr[ i ] = arr[ j ];
			arr[ j ] = old_arr_i;
			stats->moves += 3;
		}
	}

	return j;
}

// Description:
// Helper function for recursive quicksort.
//
// Parameters:
// uint32_t *arr - The array to sort.
// uint32_t len - The length of the array to sort.
// int64_t lo - Starting point.
// int64_t hi - Ending point.
// SortingStatistics *stats - A pointer to the SortingStatistics struct that holds the sorting statistics.
//
// Returns:
// Nothing.
static void quicksort_recursive_internal( uint32_t *arr, uint32_t len, int64_t lo, int64_t hi, SortingStatistics *stats ) {
	if ( lo < hi ) {
		int64_t p = partition( arr, lo, hi, stats );
		quicksort_recursive_internal( arr, len, lo, p - 1, stats );
		quicksort_recursive_internal( arr, len, p + 1, hi, stats );
	}
}

// Description:
// Uses quicksort to sort an array recursively.
//
// Parameters:
// uint32_t *arr - The array to sort.
// uint32_t len - The length of the array to sort.
//
// Returns:
// SortingStatistics - The statistics for the sort.
SortingStatistics quicksort_recursive( uint32_t *arr, uint32_t len ) {
	SortingStatistics stats = sorting_statistics_create( len );
	quicksort_recursive_internal( arr, len, 0, len - 1, &stats );

	return stats;
}

// Description:
// Uses quicksort to sort an array using a stack.
//
// Parameters:
// uint32_t *arr - The array to sort.
// uint32_t len - The length of the array to sort.
//
// Returns:
// SortingStatistics - The statistics for the sort.
SortingStatistics quicksort_stack( uint32_t *arr, uint32_t len ) {
	SortingStatistics stats = sorting_statistics_create( len );
	int64_t lo = 0;
	int64_t hi = len - 1;
	Stack *stack = stack_create( len );
	stack_push( stack, lo );
	stack_push( stack, hi );
	set_max_size( stack_size( stack ), &stats.max_ds_size );

	while ( !stack_empty( stack ) ) {
		stack_pop( stack, &hi );
		stack_pop( stack, &lo );
		int64_t p = partition( arr, lo, hi, &stats );

		if ( lo < p ) {
			stack_push( stack, lo );
			stack_push( stack, p );
		}

		if ( hi > p + 1 ) {
			stack_push( stack, p + 1 );
			stack_push( stack, hi );
		}

		set_max_size( stack_size( stack ), &stats.max_ds_size );
	}

	stack_delete( &stack );

	return stats;
}

// Description:
// Uses quicksort to sort an array using a queue.
//
// Parameters:
// uint32_t *arr - The array to sort.
// uint32_t len - The length of the array to sort.
//
// Returns:
// Nothing.
SortingStatistics quicksort_queue( uint32_t *arr, uint32_t len ) {
	SortingStatistics stats = sorting_statistics_create( len );
	int64_t lo = 0;
	int64_t hi = len - 1;
	Queue *queue = queue_create( len );
	queue_add( queue, lo );
	queue_add( queue, hi );
	set_max_size( queue_size( queue ), &stats.max_ds_size );

	while ( !queue_empty( queue ) ) {
		queue_remove( queue, &lo );
		queue_remove( queue, &hi );
		int64_t p = partition( arr, lo, hi, &stats );

		if ( lo < p ) {
			queue_add( queue, lo );
			queue_add( queue, p );
		}

		if ( hi > p + 1 ) {
			queue_add( queue, p + 1 );
			queue_add( queue, hi );
		}

		set_max_size( queue_size( queue ), &stats.max_ds_size );
	}

	queue_delete( &queue );

	return stats;
}
