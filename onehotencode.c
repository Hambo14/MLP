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
    //int original_array = *p_original_array;
    int num_categories = 0;

    // Declare a dynamic array to append unique categories
    Dynamic_Array unique_categories;
    Dynamic_Array *p_unique_categories = &unique_categories;

    // Sort array in ascending order using quicksort then extract unique values
    quicksort(array,0,length-1);
    initial_array(p_unique_categories, 10);
    for (int i=0; i<=length-3; i++)
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

    //  Create new array of just categories on the stack
    /*
    int categories[num_categories];
    for (int i=0; i < num_categories; i++)
    {
        categories[i] = unique_categories.array[i];
    }

    // free the array on the heap
    free_array(p_unique_categories);
    if (p_unique_categories != NULL)
    {
        p_unique_categories = NULL;
    }
    */

    // create 2d array on the heap for onehotecoding
    int *onehotencode_array = calloc(length*num_categories,sizeof(int));

    // now onehotencode
    for (int i=0; i < num_categories; i++)
    {
        for (int j=0; j < length; j++)
        {
            if (p_original_array[i] == unique_categories.array[j]) 
            {
                onehotencode_array[i*length + num_categories] = 1;
            }
        }
    }

    free_array(p_unique_categories);
    if (p_unique_categories != NULL)
    {
        p_unique_categories = NULL;
    }

    if (p_original_array != NULL)
    {
        free(p_original_array);
        p_original_array = NULL;
    }

    return onehotencode_array; // *(*(onehotencode_array + i) + j)
}

int main()
{
    int test_array[5] = {1,2,3,2,2};
    //int *p_test = &test_array;
    size_t size_array = sizeof(test_array) / sizeof(test_array[0]);
    int *p_test_array = &(test_array[0]);
    int *testing = onehotencode(p_test_array, size_array);
    for (int i=0; i<3; i++) {
        for (int j=0; j<5; j++) {
            printf("%i,",testing[i*5 + j]);
        }
        printf("\n");
    }

    return 0;
}
