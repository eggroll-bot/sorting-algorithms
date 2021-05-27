#include "bubble.h"

#include "sorting_statistics.h"

#include <stdbool.h>
#include <stdint.h>

// Description:
// Uses bubble sort to sort an array.
//
// Parameters:
// uint32_t *arr - The array to sort.
// uint32_t len - The length of the array to sort.
//
// Returns:
// SortingStatistics - The statistics for the sort.
SortingStatistics bubble_sort( uint32_t *arr, uint32_t len ) {
	SortingStatistics stats = sorting_statistics_create( len );
	uint32_t pass_size = len;
	bool swapped = true;

	while ( swapped ) { // Continue until there is nothing else to check.
		swapped = false;

		for ( uint32_t i = 1; i < pass_size; i++ ) {
			if ( arr[ i ] < arr[ i - 1 ] ) { // Compare to previous element.
				// Swap arr[i] and arr[i - 1].
				uint32_t old_arr_i = arr[ i ];
				arr[ i ] = arr[ i - 1 ];
				arr[ i - 1 ] = old_arr_i;
				stats.moves += 3;
				swapped = true;
			}

			stats.compares++;
		}

		pass_size -= 1; // Last element is sorted, so we can ignore it in the future.
	}

	return stats;
}
