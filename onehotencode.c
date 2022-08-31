#include <stdio.h>
#include <stdlib.h>
#include "dynamicArrays.h"

// This file will hold all the preprocessing functions for the MLP such as
// onehotencoding and normalisation of data.

/* Partition an array for quick sorting algorithm */
int partition(int array[], int first, int last) 
{
    int pivot_value = array[first], leftmark = first + 1, rightmark = last, done = 0;

    while (done != 1)
    {
        while (leftmark <= rightmark && array[leftmark] <= pivot_value)
        {
            leftmark++;
        }

        while (array[rightmark] >= pivot_value && rightmark >= leftmark)
        {
            rightmark--;
        }

        if (rightmark < leftmark)
        {
            done = 1;
        } 
        else 
        {
            int temp = array[leftmark];
            array[leftmark] = array[rightmark];
            array[rightmark] = temp;
        }
    }

    int temp = array[first];
    array[first] = array[rightmark];
    array[rightmark] = temp;

    return rightmark;
}

/* quicksort algorithm to find unique categories in array for onehotencode */
void quicksort(int array[], int first, int last)
{
    if (first < last)
    {
        int splitpoint = partition(array,first,last);
        quicksort(array,first,splitpoint-1);
        quicksort(array,splitpoint+1,last);
    }
}

int *onehotencode(int array[], size_t length) 
{
    int *p_original_array = intdup(array, length);
    int num_categories = 0;

    // Declare a dynamic array to append unique categories
    Dynamic_Array unique_categories = {.array = NULL, .size = 0, .used = 0};
    Dynamic_Array *p_unique_categories = &unique_categories;

    // Sort array in ascending order using quicksort then extract unique values
    quicksort(array,0,length-1);
    initial_array(p_unique_categories, 10);
    for (size_t i=0; i<=length-2; i++)
    {
        if (array[i] != array[i+1])
        {
            num_categories++;
            insert_array(p_unique_categories, array[i]);
        }
    }
    if (array[length-2] != array[length-1]) // if statement here to avoid checking inequality every iteration of i
    {
        num_categories++;
        insert_array(p_unique_categories, array[length-1]);
    }

    // create 2d array on the heap for onehotencoding
    int *onehotencode_array = calloc(length*num_categories,sizeof(int));

    // now onehotencode
    for (int i = 0; i < (int) length; i++)
    {
        for (int j = 0; j < num_categories; j++)
        {
            if (p_original_array[i] == unique_categories.array[j])
            {
                onehotencode_array[i * num_categories + j] = 1;
            }
        }
    }

    free_array(p_unique_categories); free(p_original_array);
    if (p_unique_categories != NULL) {p_unique_categories = NULL; }
    if (p_original_array != NULL) {p_original_array = NULL;}

    return onehotencode_array;
}

int main()
{
    int test_array[5] = {1,2,3,2,2};
    size_t size_array = sizeof(test_array) / sizeof(test_array[0]);
   
    int *test_onehotencode = onehotencode(test_array, size_array);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 3; j++)
            printf("%i ", test_onehotencode[i * 3 + j]);
        printf("\n");
    }
    
    free(test_onehotencode);
    test_onehotencode = NULL;
    return 0;
}
