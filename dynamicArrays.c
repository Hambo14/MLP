#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynamicArrays.h"

/* Implementation of a dynamic array class for all dynamic array uses */

void initial_array(Dynamic_Array *a, size_t initial_size)
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

void insert_array(Dynamic_Array *a, int element)
{
    if (a->used == a->size) 
    {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void free_array(Dynamic_Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

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




