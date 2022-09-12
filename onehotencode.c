// INCLUDE LIBRARIES
#include <stdio.h>
#include <stdlib.h>

// INCLUDE PROJECT MODULES
#define VAR_ONEHOT
#include "onehotencode.h"
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
    Int_Dynamic_Array unique_categories = {.array = NULL, .size = 0, .used = 0};
    Int_Dynamic_Array *p_unique_categories = &unique_categories;

    // Sort array in ascending order using quicksort then extract unique values
    quicksort(array,0,length-1);
    int_initial_array(p_unique_categories, 10);
    for (size_t i=0; i<=length-2; i++)
    {
        if (array[i] != array[i+1])
        {
            num_categories++;
            int_insert_array(p_unique_categories, array[i]);
        }
    }
    num_categories++;
    int_insert_array(p_unique_categories, array[length-1]);

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

    int_free_array(p_unique_categories); free(p_original_array);
    if (p_unique_categories != NULL) {p_unique_categories = NULL; }
    if (p_original_array != NULL) {p_original_array = NULL;}

    return onehotencode_array;
}

void normalise(float array[LENGTH][ROW][COLUMN])
{
    // using min-max scaling
    // x_scaled = (x - x_min)/(x_max - x_min)
    // treat all entities as 1d arrays

    float *p1 = &array[0][0][0];
    float max = array[0][0][0], min = array[0][0][0];
    while (p1 != (&array[0][0][0]+LENGTH*ROW*COLUMN))
    {
        if (*p1 > max)
            max = *p1;
        if (*p1 < min)
            min = *p1;
        p1++;
    }

    for (int i = 0; i < LENGTH; i++) {
        for (int j = 0; j < ROW; j++) {
            for (int k = 0; k < COLUMN; k++)
                array[i][j][k] = (array[i][j][k]-min)/(max-min);
        }
    }
}
