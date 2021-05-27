#ifndef __SORTING_STATISTICS_H__
#define __SORTING_STATISTICS_H__

#include <stdint.h>

typedef struct SortingStatistics SortingStatistics;

struct SortingStatistics {
	uint32_t elements; // Number of elements processed.
	uint64_t moves; // Number of moves done by the sort.
	uint64_t compares; // Number of compares done by the sort.
	uint32_t max_ds_size; // The max size of the backing data structure of the sorting algorithm. (only used by quicksort)
};

SortingStatistics sorting_statistics_create( uint32_t elements );

#endif
