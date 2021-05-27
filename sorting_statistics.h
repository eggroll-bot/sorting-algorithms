#ifndef __SORTING_STATISTICS_H__
#define __SORTING_STATISTICS_H__

#include <stdint.h>

typedef struct SortingStatistics SortingStatistics;

struct SortingStatistics {
	uint32_t elements; // Number of elements processed.
	uint64_t moves; // Number of moves done by the sort.
	uint64_t compares; // Number of compares done by the sort.
};

#endif
