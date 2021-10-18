//
// Created by draia on 14/10/2021.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#define BUFFER_SIZE 32768
#define EPSILON 0.00000000000000022204460492503131
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG FAIL_OUT;

#include "toolbox.h"
#include "newton.h"
#include "lagrange.h"

int main() {
    srand(time(NULL));
    int points;
    coord *arr;
    char *eqNewt = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(eqNewt, "%c", '\0');
    char *eqLagr = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(eqLagr, "%c", '\0');

    char str[30];
    char *endPtr;
    printf("pour quitter ce programme, entrez 'q' en reponse a une requete\n");
    printf("combien de coordonnees voulez-vous entrer?\n>");
    scanf("%s", str);
    points = strtol(str, &endPtr, 10);
    cleanCheck(*endPtr);
    arr = mkCoordArr(points);
    printf("\n");
    fill_X_Y(arr, points);
    showCoordArr(arr, points);
    printf("%d points, %d degres, complexite: 4n^2-3n-1, nb d'ops attendu: %d\n",
           points - 1, points, ((4 * points * points) - (3 * points) - 1));
    eqLagr = findPolyLagr(arr, points);
    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\nP(x) = %s\n",
           eqLagr);
    askPy(arr, eqLagr, points, "Lagrange");
    showCoordArr(arr, points);
    printf("%d points, %d degres, complexite: (5n^2-n-4)/2, nb d'ops attendu: %d\n",
           points - 1, points, ((5 * points * points) - (points) - 4) / 2);
    eqNewt = findPolyNewt(arr, points);
    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\nP(x) = %s\n",
           eqNewt);
    askPy(arr, eqNewt, points, "Newton");


//    points = 4;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-5, -2};
//    arr[1] = (coord) {-1, 6};
//    arr[2] = (coord) {0, 1};
//    arr[3] = (coord) {2, 3};
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


//    points = 5;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-1, -1.5};
//    arr[1] = (coord) {-0.5, 0};
//    arr[2] = (coord) {0, 0.25};
//    arr[3] = (coord) {0.5, 0};
//    arr[4] = (coord) {1, 0};
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


//    points = 6;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {-2, -1};
//    arr[1] = (coord) {1, 2};
//    arr[2] = (coord) {4, 59};
//    arr[3] = (coord) {-1, 4};
//    arr[4] = (coord) {3, 24};
//    arr[5] = (coord) {-4, -53};
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


//    points = 20;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {0, 0.99987};
//    arr[1] = (coord) {2, 0.99997};
//    arr[2] = (coord) {4, 1.00000};
//    arr[3] = (coord) {6, 0.99997};
//    arr[4] = (coord) {8, 0.99988};
//    arr[5] = (coord) {10, 0.99973};
//    arr[6] = (coord) {12, 0.99953};
//    arr[7] = (coord) {14, 0.99927};
//    arr[8] = (coord) {16, 0.99897};
//    arr[9] = (coord) {18, 0.99846};
//    arr[10] = (coord) {20, 0.99805};
//    arr[11] = (coord) {22, 0.99751};//0.999751
//    arr[12] = (coord) {24, 0.99705};
//    arr[13] = (coord) {26, 0.99650};
//    arr[14] = (coord) {28, 0.99664};
//    arr[15] = (coord) {30, 0.99533};
//    arr[16] = (coord) {32, 0.99472};
//    arr[17] = (coord) {34, 0.99472};
//    arr[18] = (coord) {36, 0.99333};
//    arr[19] = (coord) {38, 0.99326};
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


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
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


//    points = 11;
//    arr = mkCoordArr(points);
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
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


//    points = 11;
////this one causes the program to fail out
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {8, 6.58};
//    arr[1] = (coord) {8, 5.76};
//    arr[2] = (coord) {8, 8.74};
//    arr[3] = (coord) {8, 8.77};
//    arr[4] = (coord) {8, 9.26};
//    arr[5] = (coord) {8, 8.1};
//    arr[6] = (coord) {8, 6.13};
//    arr[7] = (coord) {19, 3.1};
//    arr[8] = (coord) {8, 9.13};
//    arr[9] = (coord) {8, 7.26};
//    arr[10] = (coord) {8, 4.74};
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


//    points = 21;
//    arr = mkCoordArr(points);
//    arr[0] = (coord) {752, 85};
//    arr[1] = (coord) {855, 83};
//    arr[2] = (coord) {871, 162};
//    arr[3] = (coord) {734, 79};
//    arr[4] = (coord) {610, 81};
//    arr[5] = (coord) {582, 83};
//    arr[6] = (coord) {921, 281};
//    arr[7] = (coord) {492, 81};
//    arr[8] = (coord) {569, 81};
//    arr[9] = (coord) {462, 80};
//    arr[10] = (coord) {907, 243};
//    arr[11] = (coord) {643, 84};
//    arr[12] = (coord) {862, 84};
//    arr[13] = (coord) {524, 82};
//    arr[14] = (coord) {679, 80};
//    arr[15] = (coord) {902, 226};
//    arr[16] = (coord) {918, 260};
//    arr[17] = (coord) {828, 82};
//    arr[18] = (coord) {875, 186};
//    arr[19] = (coord) {809, 77};
//    arr[20] = (coord) {894, 223};
//    showCoordArr(arr, points);
//    eqLagr = findPolyLagr(arr, points);
//    printf("interpolation de Lagrange non simplifiee (version simplifiee visible par le script python):\n%s\n", eqLagr);
//    askPy(arr, eqLagr, points, "Lagrange");
//    showCoordArr(arr, points);
//    eqNewt = findPolyNewt(arr, points);
//    printf("interpolation de Newton non simplifiee (version simplifiee visible par le script python):\n%s\n", eqNewt);
//    askPy(arr, eqNewt, points, "Newton");


    free(arr);
    return 0;
}

