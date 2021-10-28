//
// Created by draia on 28/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPSILON 0.00000000000000022204460492503131
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "toolbox.h"
#include "regression.h"
#include "exp_adjust.h"
#include "pow_adjust.h"

int main() {
    double a, b;
    int n;
    coord *arr;

    n = 3;
    arr = mkCoordArr(n);
    arr[0] = (coord) {3,7};
    arr[1] = (coord) {4, 9};
    arr[2] = (coord) {5, 8};

    leastSqu(arr, n, &a, &b);

    printf("y = %f x + %f\n", a, b);

    return 0;
}