#ifndef __SORTING_STATISTICS_H__
#define __SORTING_STATISTICS_H__

#include <stdint.h>

typedef struct SortingStatistics SortingStatistics;

struct SortingStatistics {
	uint32_t elements;
	uint64_t moves;
	uint64_t compares;
};

#endif
