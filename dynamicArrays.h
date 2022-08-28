#ifndef DYNAMIC_ARRAYS_DOT_H
#define DYNAMIC_ARRAYS_DOT_H

#include <stdio.h>
#include <stdlib.h>

// Declare Array class
typedef struct Array;

// Declare functions that create initial array, insert values to array 
// and free array from the heap
void initial_array(Array *a, size_t initial_size);
void insert_array(Array *a, int element);
void free_array(Array *a);

#endif /* DYNAMIC_ARRAYS_DOT_H */
