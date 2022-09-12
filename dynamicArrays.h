#ifndef DYNAMIC_ARRAYS_DOT_H
#define DYNAMIC_ARRAYS_DOT_H

#include <stdio.h>
#include <stdlib.h>

// Declare Array class

typedef struct Int_Dynamic_Array_Tag {
    int *array;
    size_t used;
    size_t size;
} Int_Dynamic_Array;

typedef struct Double_Dynamic_Array_Tag {
    double *array;
    size_t used;
    size_t size;
} Double_Dynamic_Array;

// Declare functions that create initial array, insert values to array 
// and free array from the heap
void int_initial_array(Int_Dynamic_Array *a, size_t initial_size);
void int_insert_array(Int_Dynamic_Array *a, int element);
void int_free_array(Int_Dynamic_Array *a);
void double_initial_array(Double_Dynamic_Array *a, size_t initial_size);
void double_insert_array(Double_Dynamic_Array *a, double element);
void double_free_array(Double_Dynamic_Array *a);
int *intdup(int const * src, size_t len);

#endif /* DYNAMIC_ARRAYS_DOT_H */
