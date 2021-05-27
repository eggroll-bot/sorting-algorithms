#include "bubble.h"
#include "gap_sequences.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "sorting_statistics.h"

#include <getopt.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define DEFAULT_ARRAY_LENGTH 100 // The number of array elements to generate.
#define DEFAULT_MAX_TO_PRINT 100 // The max number of elements to print.
#define DEFAULT_RANDOM_SEED	 1000 // The default random seed for generating array elements.
#define OPTIONS				 "habsSqtQn:p:r:" // Valid options for the program.

// An enum for sort flags.
typedef enum { F_ALL, F_BUBBLE, F_SHELL_CIURA, F_SHELL_PRATT, F_QUICK_RECURSIVE, F_QUICK_STACK, F_QUICK_QUEUE } flags;

// Description:
// Fills an array's elements with pseudorandom numbers based on a seed.
//
// Parameters:
// uint32_t *arr - The array to fill.
// uint32_t seed - The seed to use to generate pseudorandom numbers.
// uint32_t length - The length of the array.
//
// Returns:
// Nothing.
static void generate_random_array( uint32_t *arr, uint32_t seed, uint32_t length ) {
	srandom( seed );

	for ( uint32_t i = 0; i < length; i++ ) {
		arr[ i ] = random( );
	}
}

// Description:
// Prints the program's help message to stderr.
//
// Parameters:
// char *program_path - The path to the program.
//
// Returns:
// Nothing.
static void print_help( char *program_path ) {
	fprintf( stderr,
		"SYNOPSIS\n   Compares sorting algorithms against each other. Uses a random\n   seed to generate elements to sort.\n\nUSAGE\n   %s [-habsSqtQ] [-n length] [-p elements] [-r "
		"seed]\n\nOPTIONS\n   -h              Prints the help text.\n   -a              Enables all sorts.\n   -b              Enables bubble sort.\n   -s              Enables shell sort (Ciura gap "
		"sequence).\n   -S              Enables shell sort (Pratt gap sequence).\n   -q              Enables quicksort (recursive).\n   -t              Enables quicksort (stack).\n   -Q              "
		"Enables quicksort (queue).\n   -n length       Number of array elements to generate.\n   -p elements     Number of total elements to print.\n   -r seed         Random seed used to generate "
		"array elements.\n",
		program_path );
}

// Description:
// Prints a sort's data.
//
// Parameters:
// char *sort_name - The name of the sort used.
// SortingStatistics stats - Sorting statistics to print.
// uint32_t *sorted_array - The sorted array.
// uint32_t max_to_print - The max number of elements to print.
//
// Returns:
// Nothing.
static void print_sort( char *sort_name, SortingStatistics stats, uint32_t *sorted_array, uint32_t max_to_print ) {
	printf( "%s\n%" PRIu32 " elements, %" PRIu64 " moves, %" PRIu64 " compares\n", sort_name, stats.elements, stats.moves, stats.compares );

	if ( stats.max_ds_size > 0 ) {
		printf( "Max data structure size: %" PRIu32 "\n", stats.max_ds_size );
	}

	// Print sorted array.
	for ( uint32_t i = 0; i < max_to_print; i++ ) {
		printf( "   %10" PRIu32, sorted_array[ i ] );

		// Print a new line if the array index + 1 is a multiple of 5 (five elements per row max).
		if ( ( i + 1 ) % 5 == 0 ) {
			printf( "\n" );
		}
	}

	// Print a new line because the last row did not have five elements to print.
	if ( max_to_print % 5 != 0 ) {
		printf( "\n" );
	}
}

static bool run_and_print_sort( char *sort_name, SortingStatistics ( *sort_function )( uint32_t *, uint32_t ), uint32_t len, uint32_t random_seed, uint32_t max_to_print ) {
	uint32_t *arr = ( uint32_t * ) calloc( len, sizeof( uint32_t ) );

	if ( !arr ) {
		fprintf( stderr, "Failed to allocate array to sort.\n" );

		return false;
	}

	generate_random_array( arr, random_seed, len );
	SortingStatistics stats = sort_function( arr, len );
	print_sort( sort_name, stats, arr, max_to_print );
	free( arr );
	arr = NULL;

	return true;
}

// Description:
// The entry point of the program.
//
// Parameters:
// int argc - Argument count.
// char **argv - Array of argument strings.
//
// Returns:
// int - The exit status of the program (0 = success, otherwise error).
int main( int argc, char **argv ) {
	int32_t opt = 0;
	Set args = set_empty( );
	uint32_t array_length = DEFAULT_ARRAY_LENGTH;
	uint32_t max_to_print = DEFAULT_MAX_TO_PRINT;
	uint32_t random_seed = DEFAULT_RANDOM_SEED;

	while ( ( opt = getopt( argc, argv, OPTIONS ) ) != -1 ) { // Process each option specified.
		switch ( opt ) {
		case 'h': print_help( *argv ); return 0; // Print help.
		case 'a': args = set_insert( args, F_ALL ); break; // All sorts.
		case 'b': args = set_insert( args, F_BUBBLE ); break; // Bubble sort.
		case 's': args = set_insert( args, F_SHELL_CIURA ); break; // Shell sort (Ciura gap sequence).
		case 'S': args = set_insert( args, F_SHELL_PRATT ); break; // Shell sort (Pratt gap sequence).
		case 'q': args = set_insert( args, F_QUICK_RECURSIVE ); break; // Quicksort (recursive).
		case 't': args = set_insert( args, F_QUICK_STACK ); break; // Quicksort (stack).
		case 'Q': args = set_insert( args, F_QUICK_QUEUE ); break; // Quicksort (queue).
		case 'n': array_length = strtoul( optarg, NULL, 10 ); break; // Array length.
		case 'p': max_to_print = strtoul( optarg, NULL, 10 ); break; // Max elements to print.
		case 'r': random_seed = strtoul( optarg, NULL, 10 ); break; // Random seed.
		default: print_help( *argv ); return 1; // Invalid flag.
		}
	}

	if ( args == set_empty( ) ) { // No sorts entered.
		fprintf( stderr, "Select at least one sort to perform.\n" );
		print_help( *argv );

		return 1;
	}

	if ( array_length == 0 ) { //
		fprintf( stderr, "Invalid array length.\n" );

		return 1;
	}

	// Set max_to_print to the number of elements to print.
	max_to_print = max_to_print < array_length ? max_to_print : array_length;

	// Bubble sort.
	if ( set_member( args, F_BUBBLE ) || set_member( args, F_ALL ) ) {
		if ( !run_and_print_sort( "Bubble Sort", bubble_sort, array_length, random_seed, max_to_print ) ) {
			return 1;
		}
	}

	// Shell sort (Ciura gap sequence).
	if ( set_member( args, F_SHELL_CIURA ) || set_member( args, F_ALL ) ) {
		shell_set_gap_sequence( ciura_gap_seq, CIURA_GAP_SEQ_SIZE );

		if ( !run_and_print_sort( "Shell Sort (Ciura Gap Sequence)", shell_sort, array_length, random_seed, max_to_print ) ) {
			return 1;
		}
	}

	// Shell sort (Pratt gap sequence).
	if ( set_member( args, F_SHELL_PRATT ) || set_member( args, F_ALL ) ) {
		shell_set_gap_sequence( pratt_gap_seq, PRATT_GAP_SEQ_SIZE );

		if ( !run_and_print_sort( "Shell Sort (Pratt Gap Sequence)", shell_sort, array_length, random_seed, max_to_print ) ) {
			return 1;
		}
	}

	// Quicksort (recursive).
	if ( set_member( args, F_QUICK_RECURSIVE ) || set_member( args, F_ALL ) ) {
		if ( !run_and_print_sort( "Quicksort (Recursive)", quicksort_recursive, array_length, random_seed, max_to_print ) ) {
			return 1;
		}
	}

	// Quicksort (stack).
	if ( set_member( args, F_QUICK_STACK ) || set_member( args, F_ALL ) ) {
		if ( !run_and_print_sort( "Quicksort (Stack)", quicksort_stack, array_length, random_seed, max_to_print ) ) {
			return 1;
		}
	}

	// Quicksort (queue).
	if ( set_member( args, F_QUICK_QUEUE ) || set_member( args, F_ALL ) ) {
		if ( !run_and_print_sort( "Quicksort (Queue)", quicksort_queue, array_length, random_seed, max_to_print ) ) {
			return 1;
		}
	}

	return 0;
}
