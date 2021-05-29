#include "set.h"

#include <stdbool.h>
#include <stdint.h>

#define SET_CAPACITY 32 // The max capacity of a set.

// Description:
// Returns an empty set.
//
// Parameters:
// Nothing.
//
// Returns:
// Set - An empty set.
Set set_empty( ) {
	return 0;
}

// Description:
// Checks whether a value is a member of a set.
//
// Parameters:
// Set s - The set to check.
// uint8_t x - The value to check for.
//
// Returns:
// bool - Whether the value is a member of the set.
bool set_member( Set s, uint8_t x ) {
	return s & ( 1 << x );
}

// Description:
// Inserts a value into a set.
//
// Parameters:
// Set s - The set to insert a value into.
// uint8_t x - The value to insert into the set.
//
// Returns:
// Set - A set with the value inserted.
Set set_insert( Set s, uint8_t x ) {
	return s | ( 1 << x ); // Set bit for value to 1.
}
