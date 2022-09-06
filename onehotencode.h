#ifndef ONEHOTENCODE_DOT_H
#define ONEHOTENCODE_DOT_H

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b; })

#include <stdio.h>
#include <stdlib.h>
#include "dynamicArrays.h"

#ifndef VAR_ONEHOT
# define _DECL extern
# define _INIT(x)
#else
# define _DECL
# define _INIT(x) = x 

_DECL const int LENGTH _INIT(3);
_DECL const int ROW _INIT(3);
_DECL const int COLUMN _INIT(3);

int partition(int array[], int first, int last);
void quicksort(int array[], int first, int last);
int *onehotencode(int array[], size_t length);
void normalise(float array[LENGTH][ROW][COLUMN]);

#endif /* VAR_ONEHOT */
#endif /* ONEHOTENCODE_DOT_H */