#ifndef __QUICK_H__
#define __QUICK_H__

#include "sorting_statistics.h"

#include <stdint.h>

SortingStatistics quicksort_stack( uint32_t *arr, uint32_t len );

SortingStatistics quicksort_queue( uint32_t *arr, uint32_t len );

#endif
