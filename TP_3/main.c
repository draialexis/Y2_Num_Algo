//
// Created by draia on 28/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define BUFFER_SIZE 32768
#define EPSILON 0.00000000000000022204460492503131
#define DEBUG printf("an error occurred\nfile %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "toolbox.h"
#include "linear.h"
#include "exponential.h"
#include "power.h"

int main() {
    double a, b;
    int n, o;
    coord *arr;

    char str[20];
    char *endPtr;
    printf("pour quitter ce programme, entrez 'q' en reponse a une requete\n");
    printf("combien de coordonnees voulez-vous entrer?\n>");
    scanf("%s", str);
    n = strtol(str, &endPtr, 10);
    cleanCheck(*endPtr);
    arr = mkCoordArr(n);
    printf("\n");
    fill_X_Y(arr, n);
    showCoordArr(arr, n);
    char mthd;
    printf("\nquelle methode utiliser ?"
           "\n* 'l' : regression lineaire"
           "\n* 'e' : ajustement exponentiel"
           "\n* 'p' : ajustement puissance"
           "\n>");
    mthd = (char) getchar();
    cleanCheck(mthd);
    if (mthd == 'l') {
        if (linReg(arr, n, &a, &b, &o) == 1) {
            printf("y = %f x + %f\n", a, b);
        } else {
            DEBUG
        }
    } else if (mthd == 'e') {
        if (expReg(arr, n, &a, &b, &o) == 1) {
            printf("y = e^(%.15f * x %+.15f)\n", a, b);
        } else {
            DEBUG
        }
    } else if (mthd == 'p') {
        if (powReg(arr, n, &a, &b, &o) == 1) {
            printf("y = pow(x, %.15f) * %.15f\n", a, b);
        } else {
            DEBUG
        }
    } else {
        printf("exiting program\n");
        FAIL_OUT
    }
    askPy(arr, a, b, n, mthd);
    printf("nb d'ops: %d\n", o);
    coord *app = coordsApprox(arr, a, b, n, mthd);
    double dev = deviation(arr, app, a, b, n);
    printf("ecart type sur l'echantillon: %.5f", dev);
    o = 0;

//    3.1
//    n = 11;
//    arr = mkCoordArr(n);
//    arr[0] = (coord) {10, 8.04};
//    arr[1] = (coord) {8, 6.95};
//    arr[2] = (coord) {13, 7.58};
//    arr[3] = (coord) {9, 8.81};
//    arr[4] = (coord) {11, 8.11};
//    arr[5] = (coord) {14, 9.96};
//    arr[6] = (coord) {6, 7.24};
//    arr[7] = (coord) {4, 4.26};
//    arr[8] = (coord) {12, 10.84};
//    arr[9] = (coord) {7, 4.82};
//    arr[10] = (coord) {5, 5.68};
//    showCoordArr(arr, n);
//    if (linReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = %f x + %f\n", a, b);
//        askPy(arr, a, b, n, 'l');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'l');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

//    3.2 S1
//    n = 11;
//    arr = mkCoordArr(n);
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
//    showCoordArr(arr, n);
//    if (linReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = %f x + %f\n", a, b);
//        askPy(arr, a, b, n, 'l');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'l');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

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
//    showCoordArr(arr, n);
//    if (linReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = %f x + %f\n", a, b);
//        askPy(arr, a, b, n, 'l');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'l');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

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
//    showCoordArr(arr, n);
//    if (linReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = %f x + %f\n", a, b);
//        askPy(arr, a, b, n, 'l');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'l');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

//
//    3.3.1
//    n = 11;
//    arr = mkCoordArr(n);
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
//    showCoordArr(arr, n);
//    if (linReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = %f x + %f\n", a, b);
//        askPy(arr, a, b, n, 'l');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'l');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

//    3.3.2
//    n = 10;
//    arr = mkCoordArr(n);
//    arr[0] = (coord) {643, 84};
//    arr[1] = (coord) {862, 84};
//    arr[2] = (coord) {524, 82};
//    arr[3] = (coord) {679, 80};
//    arr[4] = (coord) {902, 226};
//    arr[5] = (coord) {918, 260};
//    arr[6] = (coord) {828, 82};
//    arr[7] = (coord) {875, 186};
//    arr[8] = (coord) {809, 77};
//    arr[9] = (coord) {894, 223};
//    showCoordArr(arr, n);
//    if (linReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = %.15f x + %.15f\n", a, b);
//        askPy(arr, a, b, n, 'l');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'l');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

//    3.4
//    n = 10;
//    arr = mkCoordArr(n);
//    arr[0] = (coord) {88, 5.89};
//    arr[1] = (coord) {89, 6.77};
//    arr[2] = (coord) {90, 7.87};
//    arr[3] = (coord) {91, 9.11};
//    arr[4] = (coord) {92, 10.56};
//    arr[5] = (coord) {93, 12.27};
//    arr[6] = (coord) {94, 13.92};
//    arr[7] = (coord) {95, 15.72};
//    arr[8] = (coord) {96, 17.91};
//    arr[9] = (coord) {97, 22.13};
//    showCoordArr(arr, n);
//    if (expReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = e^(%.15f * x %+.15f)\n", a, b);
//        askPy(arr, a, b, n, 'e');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'e');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

//    3.5
//    n = 7;
//    arr = mkCoordArr(n);
//    arr[0] = (coord) {20, 352};
//    arr[1] = (coord) {30, 128};
//    arr[2] = (coord) {40, 62.3};
//    arr[3] = (coord) {50, 35.7};
//    arr[4] = (coord) {100, 6.3};
//    arr[5] = (coord) {300, 0.4};
//    arr[6] = (coord) {500, 0.1};
//    showCoordArr(arr, n);
//    if (powReg(arr, n, &a, &b, &o) == 1) {
//        printf("y = pow(x, %.15f) * %.15f\n", a, b);
//        askPy(arr, a, b, n, 'p');
//        printf("nb d'ops: %d\n", o);
//        o = 0;
//        coord *app = coordsApprox(arr, a, b, n, 'p');
//        double dev = deviation(arr, app, a, b, n);
//        printf("standard deviation: %.5f", dev);
//    } else {
//        DEBUG
//    }

    return 0;
}