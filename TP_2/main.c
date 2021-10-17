//
// Created by draia on 14/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFFER_SIZE 16384
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

//    char str[30];
//    char *endPtr;
//    printf("to exit at any point, press 'q' and enter\n");
//    printf("how many datapoints?\n>");
//    scanf("%s", str);
//    points = strtol(str, &endPtr, 10);
//    cleanCheck(*endPtr);
//    arr = mkCoordArr(points);
//    printf("\n");
//    fill_X_Y(arr, points);
//    showCoordArr(arr, points);
//    char * eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    char * eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");

//    points = 4;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-5, -2};
//    arr[1] = (coord) {-1, 6};
//    arr[2] = (coord) {0, 1};
//    arr[3] = (coord) {2, 3};
//    showCoordArr(arr, points);
//    char * eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    char * eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//
//    points = 5;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-1, -1.5};
//    arr[1] = (coord) {-0.5, 0};
//    arr[2] = (coord) {0, 0.25};
//    arr[3] = (coord) {0.5, 0};
//    arr[4] = (coord) {1, 0};
//    showCoordArr(arr, points);
//    char * eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    char * eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");

    points = 6;
    arr = mkCoordArr(points);
    arr[0] = (coord) {-2, -1};
    arr[1] = (coord) {1, 2};
    arr[2] = (coord) {4, 59};
    arr[3] = (coord) {-1, 4};
    arr[4] = (coord) {3, 24};
    arr[5] = (coord) {-4, -53};
    showCoordArr(arr, points);
    char * eqNewt = findPolyNewt(arr, points);
    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
    askPy(arr, eqNewt, points, "Newton");
    showCoordArr(arr, points);
    char * eqLagr = findPolyLagr(arr, points);
    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
    askPy(arr, eqLagr, points, "Lagrange");

    return 0;
}

