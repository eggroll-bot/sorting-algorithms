#ifndef __SHELL_H__
#define __SHELL_H__

#include "sorting_statistics.h"

#include <stdint.h>

SortingStatistics shell_sort( uint32_t *arr, uint32_t len, uint32_t *gap_seq, uint32_t gap_seq_len );

#endif
