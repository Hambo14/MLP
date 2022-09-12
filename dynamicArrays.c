#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicArrays.h"

/* Implementation of a dynamic array class for all dynamic array uses */

// INTEGER ARRAYS
void int_initial_array(Int_Dynamic_Array *a, size_t initial_size)
{
    a->array = malloc(initial_size*sizeof(int));
    if (a->array == NULL)
    {
        printf("Memory allocation failed");
        return;
    }
    a->used = 0;
    a->size = initial_size;
}

void int_insert_array(Int_Dynamic_Array *a, int element)
{
    if (a->used == a->size) 
    {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void int_free_array(Int_Dynamic_Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

// DOUBLE ARRAYS: IDK IF THIS IS THE MOST EFFECTIVE METHOD OF DOING THIS
// BUT IDC BECAUSE IM NOT A SMART PROGRAMMER
void double_initial_array(Double_Dynamic_Array *a, size_t initial_size)
{
    a->array = malloc(initial_size*sizeof(double));
    if (a->array == NULL)
    {
        printf("Memory allocation failed");
        return;
    }
    a->used = 0;
    a->size = initial_size;
}

void double_insert_array(Double_Dynamic_Array *a, double element)
{
    if (a->used == a->size) 
    {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(double));
    }
    a->array[a->used++] = element;
}

void double_free_array(Double_Dynamic_Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

// DUPLICATE AN INTEGER ARRAY
int * intdup(int const * src, size_t len)
{
   int * p = malloc(len * sizeof(int));
   if (!p) 
   {
        printf("Memory allocation failed");
        exit(-1);
   }
   memcpy(p, src, len * sizeof(int));
   return p;
}




