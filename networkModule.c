// INCLUDE LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// INCLUDE PROJECT MODULES
#include "onehotencode.h"
#include "dynamicArrays.h"

struct Hidden_Layer {
    Dynamic_Array weight_matrix;
    Dynamic_Array output;
    Dynamic_Array input;
    char activation_function[10];
    size_t num_nodes;
};

float relu(float x)
{
    return max(0, x);
}

float softmax(float x)
{
    return 1.0/(1.0 + )
}

int main()
{
    printf("HELLO WORLD \n");
    return 0;
}