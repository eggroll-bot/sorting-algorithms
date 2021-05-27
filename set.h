#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t Set;

Set set_empty( );

bool set_member( Set s, uint8_t x );

Set set_insert( Set s, uint8_t x );

#endif
