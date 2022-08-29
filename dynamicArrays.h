#ifndef DYNAMIC_ARRAYS_DOT_H
#define DYNAMIC_ARRAYS_DOT_H

#include <stdio.h>
#include <stdlib.h>

// Declare Array class

typedef struct Dynamic_Array_Tag {
    int *array;
    size_t used;
    size_t size;
} Dynamic_Array;

// Declare functions that create initial array, insert values to array 
// and free array from the heap
void initial_array(Dynamic_Array *a, size_t initial_size);
void insert_array(Dynamic_Array *a, int element);
void free_array(Dynamic_Array *a);
int *intdup(int const * src, size_t len);

#endif /* DYNAMIC_ARRAYS_DOT_H */
