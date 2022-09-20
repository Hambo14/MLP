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
    } else if (strcmp(activ_func, SOFTMAX) == 0) {
        for (int i = 0; i < layer->num_nodes; i++) {
            layer->output.array[i] = softmax(layer->output.array[i]+layer->biases.array[i]);
        }
    }
}

void forward_propagation(Hidden_Layer *(layers)[], Double_Dynamic_Array input, size_t input_size, size_t num_layers)
{
    initiate_layer(layers[0], layers[0]->num_nodes, input_size);
    randomise_weights_biases(layers[0]);
    for (int i = 1; i < num_layers; i++)
    {
        initiate_layer(layers[i], layers[i]->num_nodes, layers[i-1]->num_nodes);
        randomise_weights_biases((layers[i]));
    }

    calculate_output(layers[0], &input, layers[0]->activation_function);
    for (int i = 0; i < (num_layers - 1); i++)
    {
        calculate_output(layers[i+1], &layers[i]->output, layers[i+1]->activation_function);
    }
}

int main()
{
    srand(time(NULL));
    Hidden_Layer layer1 = {.activation_function = "relu", .num_nodes = 10};
    Hidden_Layer layer2 = {.activation_function = "softmax", .num_nodes = 10};
    Hidden_Layer layer3 = {.activation_function = "relu", .num_nodes = 10};
    Hidden_Layer layer4 = {.activation_function = "relu", .num_nodes = 3};

    Hidden_Layer layers[4] = {layer1, layer2, layer3, layer4};
    Hidden_Layer *p_layers[4];
    for (int i = 0; i < 4; i++) {p_layers[i] = (&layers)[0];}

    size_t layer_num = 4;

    double test_input[9] = {0.4324,0.6832,0.4259,0.5283,0.5328,0.4292,0.0528,0.9832,0.2376};
    Double_Dynamic_Array test;
    double_initial_array(&test,9);
    size_t size_input = 9;
    for (int i = 0; i < size_input; i++) {
        double_insert_array(&test, test_input[i]);
    }

    forward_propagation(p_layers, test, 9, 4);
    calculate_output(p_layers[0], &test, p_layers[0]->activation_function);

    for (int i = 0; i < layer1.num_nodes; i++)
        printf("%f ", p_layers[0]->output.array[i]);
    printf("\n");

    calculate_output(p_layers[1], &p_layers[0]->output, p_layers[1]->activation_function);

    for (int i = 0; i < layer1.num_nodes; i++)
        printf("%f ", p_layers[0]->output.array[i]);
    printf("\n");

    printf("%zu \n", p_layers[1]->input_size);

    double_free_array(&test);
    for (int i = 0; i < 4; i++) {free_hidden_layer(&(layers[i]));}

    return 0;
}

