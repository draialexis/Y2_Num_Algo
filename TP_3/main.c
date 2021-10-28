//
// Created by draia on 28/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFFER_SIZE 32768
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

//    char str[20];
//    char *endPtr;
//    printf("pour quitter ce programme, entrez 'q' en reponse a une requete\n");
//    printf("combien de coordonnees voulez-vous entrer?\n>");
//    scanf("%s", str);
//    n = strtol(str, &endPtr, 10);
//    cleanCheck(*endPtr);
//    arr = mkCoordArr(n);
//    printf("\n");
//    fill_X_Y(arr, n);
//    showCoordArr(arr, n);
//    printf("%d points, complexite: ____, nb d'ops attendu: %d\n",
//           n, 0);//TODO update
//    if (leastSqu(arr, n, &a, &b)) {
//        printf("y = %f x + %f\n", a, b);
//    } else {
//        printf("an error occurred\n");
//    }


//    3.2 S1
    n = 11;
    arr = mkCoordArr(n);
    arr[0] = (coord) {10, 9.14};
    arr[1] = (coord) {8, 8.14};
    arr[2] = (coord) {13, 8.74};
    arr[3] = (coord) {9, 8.77};
    arr[4] = (coord) {11, 9.26};
    arr[5] = (coord) {14, 8.1};
    arr[6] = (coord) {6, 6.13};
    arr[7] = (coord) {4, 3.1};
    arr[8] = (coord) {12, 9.13};
    arr[9] = (coord) {7, 7.26};
    arr[10] = (coord) {5, 4.74};
    showCoordArr(arr, n);
    if (leastSqu(arr, n, &a, &b)) {
        printf("y = %f x + %f\n", a, b);
        askPy(arr, a, b, n, 'r');
    } else {
        printf("an error occurred\n");
    }
//
//    3.2 S2
//    n = 11;
//    arr = mkCoordArr(n);
//    arr[0] = (coord) {10, 7.46};
//    arr[1] = (coord) {8, 6.77};
//    arr[2] = (coord) {13, 12.74};
//    arr[3] = (coord) {9, 7.11};
//    arr[4] = (coord) {11, 7.81};
//    arr[5] = (coord) {14, 8.84};
//    arr[6] = (coord) {6, 6.08};
//    arr[7] = (coord) {4, 5.39};
//    arr[8] = (coord) {12, 8.15};
//    arr[9] = (coord) {7, 6.42};
//    arr[10] = (coord) {5, 5.73};
//
//    3.2 S3
//    n = 11;
//    arr = mkCoordArr(n);
//    arr[0] = (coord) {8, 6.58};
//    arr[1] = (coord) {8, 5.76};
//    arr[2] = (coord) {8, 7.71};
//    arr[3] = (coord) {8, 8.84};
//    arr[4] = (coord) {8, 8.47};
//    arr[5] = (coord) {8, 7.04};
//    arr[6] = (coord) {8, 5.25};
//    arr[7] = (coord) {19, 12.5};
//    arr[8] = (coord) {8, 5.56};
//    arr[9] = (coord) {8, 7.91};
//    arr[10] = (coord) {8, 6.89};

    return 0;
}