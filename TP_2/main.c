//
// Created by draia on 14/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFFER_SIZE 8192
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
    char *eqNewt = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(eqNewt, "%c", '\0');
    char *eqLagr = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(eqLagr, "%c", '\0');

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
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//
//    points = 4;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-5, -2};
//    arr[1] = (coord) {-1, 6};
//    arr[2] = (coord) {0, 1};
//    arr[3] = (coord) {2, 3};
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
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
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");

//    points = 6;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-2, -1};
//    arr[1] = (coord) {1, 2};
//    arr[2] = (coord) {4, 59};
//    arr[3] = (coord) {-1, 4};
//    arr[4] = (coord) {3, 24};
//    arr[5] = (coord) {-4, -53};
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//
    points = 20;
    arr = mkCoordArr(points);
    arr[0] = (coord) {0, 0.99987};
    arr[1] = (coord) {2, 0.99997};
    arr[2] = (coord) {4, 1.00000};
    arr[3] = (coord) {6, 0.99997};
    arr[4] = (coord) {8, 0.99988};
    arr[5] = (coord) {10, 0.99973};
    arr[6] = (coord) {12, 0.99953};
    arr[7] = (coord) {14, 0.99927};
    arr[8] = (coord) {16, 0.99897};
    arr[9] = (coord) {18, 0.99846};
    arr[10] = (coord) {20, 0.99805};
    arr[11] = (coord) {22, 0.99751};//0.999751
    arr[12] = (coord) {24, 0.99705};
    arr[13] = (coord) {26, 0.99650};
    arr[14] = (coord) {28, 0.99664};
    arr[15] = (coord) {30, 0.99533};
    arr[16] = (coord) {32, 0.99472};
    arr[17] = (coord) {34, 0.99472};
    arr[18] = (coord) {36, 0.99333};
    arr[19] = (coord) {38, 0.99326};
    showCoordArr(arr, points);
    eqNewt = findPolyNewt(arr, points);
    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
    askPy(arr, eqNewt, points, "Newton");
    showCoordArr(arr, points);
    eqLagr = findPolyLagr(arr, points);
    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
    askPy(arr, eqLagr, points, "Lagrange");
//
//    points = 11;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {10, 9.14};
//    arr[1] = (coord) {8, 8.14};
//    arr[2] = (coord) {13, 8.74};
//    arr[3] = (coord) {9, 8.77};
//    arr[4] = (coord) {11, 9.26};
//    arr[5] = (coord) {14, 8.1};
//    arr[6] = (coord) {6, 6.13};
//    arr[7] = (coord) {4, 3.1};
//    arr[8] = (coord) {12, 9.13};
//    arr[9] = (coord) {7, 7.26};
//    arr[10] = (coord) {5, 4.74};
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");

    free(arr);
    return 0;
}

