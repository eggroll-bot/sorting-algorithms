#include "sorting_statistics.h"

#include <stdint.h>

// Description:
// Initializes a SortingStatistics struct with a specified number of elements being sorted.
//
// Parameters:
// uint32_t elements - The number of elements being sorted.
//
// Returns:
// SortingStatistics - An initialized SortingStatistics struct.
SortingStatistics sorting_statistics_create( uint32_t elements ) {
	SortingStatistics stats;
	stats.elements = elements;
	stats.moves = 0;
	stats.compares = 0;
	stats.max_ds_size = 0;

	return stats;
}
