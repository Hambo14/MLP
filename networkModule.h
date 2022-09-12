#ifndef NETWORK_MODULE_DOT_H
#define NETWORK_MODULE_DOT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "onehotencode.h"
#include "dynamicArrays.h"

// Declare Hidden_Layer class

typedef struct Hidden_Layer_Tag {
    Double_Dynamic_Array weight_matrix;
    Double_Dynamic_Array biases;
    Double_Dynamic_Array output;
    char activation_function[10];
    size_t num_nodes;
    size_t input_size;
} Hidden_Layer;

#endif /* NETWORK_MODULE_DOT_H */