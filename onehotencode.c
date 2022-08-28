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

int onehotencode(int array[]) 
{
    int* p_array = array;
    int length = (int) ( sizeof(*p_array) / sizeof(array[0]));

    // Sort array in ascending order using quicksort then extract unique values
    for (int i=0; i<length; i++)
    {
        if (array[i] == array[i+1])
        {

        }
    }

    return 0;
}

int main()
{
    int test_array[5] = {1,2,3,2,2};
    quicksort(test_array, 0, 4);

    int i;
    for (i=0; i < 5; i++)
    {
        printf(" %d", test_array[i]);
    }

    return 0;
}
