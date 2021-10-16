//
// Created by draia on 14/10/2021.
//

#include <stdio.h>
#include <stdlib.h>

#define EPSILON 0.00000000000022737367544323206000
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "toolbox.h"
#include "newton.h"
#include "lagrange.h"

int main() {
    char str[30];
    char *endPtr;
    int n;
    printf("how many datapoints?");
    scanf("%s", str);
    n = strtol(str, &endPtr, 10);
    cleanCheck(*endPtr);
    coord *arr = mkCoordArr(n);

    fill_X_Y(arr, n);

    showCoordArr(arr, n);

    return 0;
}

