#include <stdio.h>
#include <stdlib.h>
#include "dynamicArrays.h"

typedef struct {
    int *array;
    size_t used;
    size_t size;
} Array;

void initial_array(Array *a, size_t initial_size)
{
    a->array = malloc(initial_size*sizeof(int));
    a->used = 0;
    a->size = initial_size;
}

void insert_array(Array *a, int element)
{
    if (a->used == a->size) 
    {
        a->size *= 2;
        a->array = realloc(a->array, a->size * sizeof(int));
    }
    a->array[a->used++] = element;
}

void free_array(Array *a)
{
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

int main()
{

    return 0;
}



