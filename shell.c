#include "shell.h"

#include "sorting_statistics.h"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

const uint32_t *gap_seq = NULL;
uint32_t gap_seq_len = 0;

// Description:
// Sets the gap sequence for the next shell sort to use.
//
// Parameters:
// uint32_t *gap_seq - The gap sequence to use.
// uint32_t gap_seq_len - The length of the gap sequence.
//
// Returns:
// Nothing.
void shell_set_gap_sequence( const uint32_t *gs, uint32_t gs_len ) {
	gap_seq = gs;
	gap_seq_len = gs_len;
}

// Description:
// Uses shell sort to sort an array.
//
// Parameters:
// uint32_t *arr - The array to sort.
// uint32_t len - The length of the array to sort.
//
// Returns:
// SortingStatistics - The statistics for the sort.
SortingStatistics shell_sort( uint32_t *arr, uint32_t len ) {
	assert( gap_seq && gap_seq_len );
	SortingStatistics stats = sorting_statistics_create( len );

	for ( uint32_t gap_index = 0; gap_index < gap_seq_len; gap_index++ ) {
		uint32_t gap = gap_seq[ gap_index ];

		for ( uint32_t i = gap; i < len; i++ ) {
			uint32_t j = i;
			uint32_t temp = arr[ i ];

			while ( j >= gap && ++stats.compares && temp < arr[ j - gap ] ) {
				// Move arr[j] to arr[j - gap]
				arr[ j ] = arr[ j - gap ];
				stats.moves++;
				j -= gap;
			}

			arr[ j ] = temp;
			stats.moves += 2;
		}
	}

	return stats;
}
