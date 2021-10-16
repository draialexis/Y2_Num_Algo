//
// Created by draia on 14/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPSILON 0.00000000000022737367544323206000
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG FAIL_OUT;

#include "toolbox.h"
#include "newton.h"
#include "lagrange.h"

int main() {
    int points;
    coord *arr;

    char str[30];
    char *endPtr;
    printf("to exit at any point, press 'q' and enter\n");
    printf("how many datapoints?\n>");
    scanf("%s", str);
    points = strtol(str, &endPtr, 10);
    cleanCheck(*endPtr);
    arr = mkCoordArr(points);
    printf("\n");
    fill_X_Y(arr, points);
    showCoordArr(arr, points);
    findPolyNewt(arr, points);

//    points = 4;
//    arr = mkCoordArr(points);
//    arr[0].x = -5;
//    arr[1].x = -1;
//    arr[2].x = 0;
//    arr[3].x = 2;
//    arr[0].y = -2;
//    arr[1].y = 6;
//    arr[2].y = 1;
//    arr[3].y = 3;
//    showCoordArr(arr, points);
//    findPolyNewt(arr, points);
//
//    points = 6;
//    arr = mkCoordArr(points);
//    arr[0].x = -2;
//    arr[1].x = 1;
//    arr[2].x = 4;
//    arr[3].x = -1;
//    arr[4].x = 3;
//    arr[5].x = -4;
//    arr[0].y = -1;
//    arr[1].y = 2;
//    arr[2].y = 59;
//    arr[3].y = 4;
//    arr[4].y = 24;
//    arr[5].y = -53;
//    showCoordArr(arr, points);
//    findPolyNewt(arr, points);

    return 0;
}

