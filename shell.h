#ifndef __SHELL_H__
#define __SHELL_H__

#include "sorting_statistics.h"

#include <stdint.h>

void shell_set_gap_sequence( const uint32_t *gs, uint32_t gs_len );

SortingStatistics shell_sort( uint32_t *arr, uint32_t len );

#endif
