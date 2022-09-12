// INCLUDE LIBRARIES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <immintrin.h>
#include <time.h>

// INCLUDE PROJECT MODULES
#include "onehotencode.h"
#include "dynamicArrays.h"
#include "networkModule.h"

double relu(double x)
{
    return max(0, x);
}

double softmax(double x)
{
    return 1.0/(1.0 + exp(x));
}

// RETURNS RANDOM DOUBLE BETWEEN 0 AND 1
double random_double()
{
    return (((double) rand() / (RAND_MAX / 2)) - 1);
}

void randomise_weights_biases(Hidden_Layer *layer)
{
    // ROW MAJOR ORDER
    for (int i = 0; i < layer->num_nodes; i++)
    {
        for (int j = 0; j < layer->input_size; j++)
        {
            layer->weight_matrix.array[i*layer->input_size + j] = random_double();
        }
    }

    for (int i = 0; i < layer->num_nodes; i++)
        double_insert_array(&layer->biases,random_double());
}

void initiate_layer(Hidden_Layer *layer, int num_nodes, int input_size)
{
    layer->num_nodes = num_nodes;
    layer->input_size = input_size;
    double_initial_array(&layer->output, num_nodes);
    double_initial_array(&layer->weight_matrix, num_nodes*input_size);
    double_initial_array(&layer->biases, num_nodes);

    for (int i = 0; i < layer->num_nodes; i++)
    {
        double_insert_array(&layer->output, 0);
    }
}

void free_hidden_layer(Hidden_Layer *layer)
{
    double_free_array(&layer->output); double_free_array(&layer->weight_matrix); double_free_array(&layer->biases);
}

void calculate_output(Hidden_Layer *layer, Double_Dynamic_Array *input, char activ_func[10])
{
    for (int i = 0; i < layer->input_size; i++) 
    {
        for(int j = 0; j < layer->num_nodes; j++)
        {
            layer->output.array[j] = 0;
            for(int k = 0; k < layer->input_size; k++)
            {
                layer->output.array[j] += input->array[k] * layer->weight_matrix.array[k*layer->num_nodes + j];
            }
        } 
    }

    char RELU[10] = "relu";
    char SOFTMAX[10] = "softmax";
    if (strcmp(activ_func, RELU) == 0) {
        for (int i = 0; i < layer->num_nodes; i++) {
            layer->output.array[i] = relu(layer->output.array[i]+layer->biases.array[i]);
    }
    } else if (strcmp(activ_func, SOFTMAX)) {
        for (int i = 0; i < layer->num_nodes; i++) {
            layer->output.array[i] = softmax(layer->output.array[i]+layer->biases.array[i]);
        }
    }
}

/*
double *calculate_output(Hidden_Layer *layer)
{

    return rres;
}
*/

int main()
{
    srand(time(NULL));
    Hidden_Layer layer1; Double_Dynamic_Array input;
    double test_input[9] = {0.033,0.235,0.195,0.358,0.066,0.752,0.845,0.836,0.156};
    initiate_layer(&layer1, 10, 9); double_initial_array(&input, 9);
    for (int i = 0; i < layer1.input_size; i++)
        double_insert_array(&input, test_input[i]);
    randomise_weights_biases(&layer1);
    calculate_output(&layer1, &input, "relu");

    for (int i = 0; i < layer1.num_nodes; i++)
        printf("%f ", layer1.output.array[i]);
    printf("\n");

    free_hidden_layer(&layer1); double_free_array(&input);
       
    return 0;
}

