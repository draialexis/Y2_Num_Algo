#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 5
#define COLS 4
#define EPSILON 0.000000000000000222044604925031
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "matrices_suite.h"
#include "toolbox.h"
#include "lin_alg.h"

int main() {

    // TODO https://ent.uca.fr/moodle/mod/forum/discuss.php?d=148630
/*
    printf("size of doubles: %llu bits\n", sizeof(double) * 8);

    //calculating machine epsilon
    double epsilon = 1.0;
    int count = 0;
    while (1.0 + (epsilon / 2.0) > 1.0) {
        // will be false as epsilon tends toward 0 ; will be interpreted as false after a few dozen iterations
        // on my desktop, 1.0 + 0.000000000000000444089209850063 / 2 > 1.0 is true
        // which means it detects doubles as close to 0 as 0.000000000000000222044604925031 (2^-52)
        epsilon = epsilon / 2.0;
        printf("epsilon = %.32f\n", epsilon);
        count++;
    }
    printf("epsilon = 2^-%d\n", count);

    //don't know why we do this... found that example in C# and C++ on https://newbedev.com/how-to-choose-epsilon-value-for-floating-point
    double epsilon_equation = sqrt(2 * epsilon * epsilon);
    printf("fabs(1.0 + 2.0 - 3.0) = %.32f\n", fabs(1.0 + 2.0 - 3.0));
    printf("sqrt(3.0 * sqrt(2 * epsilon * epsilon) * sqrt(2 * epsilon * epsilon) = %.32f\n",
           sqrt(3.0 * epsilon_equation * epsilon_equation)); // so.. epsilon * sqrt(6) ?? why?
    // are we checking that those successive operations don't deviate from the expected result?
    //printf("%.32f\n", epsilon * sqrt(6));
    printf("epsilon is valid: ");
    // ternary conditionals are cool
    (fabs(1.0 + 2.0 - 3.0) < sqrt(3.0 * epsilon_equation * epsilon_equation)) ? printf("true\n") : printf("false\n");
*/


    srand(time(NULL));
    double **matA = mkMat(ROWS, COLS);
    fillMatA_rdm(matA, ROWS, COLS);
    double **matA_EZ = mkMat(3, 4);
    fillMat_EZ(matA_EZ);


    double *matX = mkColVec(COLS);// A(m,n) * X(_n_, p) = B(m, p) // p = 1
    double *matX_EZ = mkColVec(4);


    double *matB = mkColVec(ROWS);
    fillMatB_rdm(matB, ROWS);
    double *matB_EZ = mkColVec(3);
    fillMatB_EZ(matB_EZ);


    printf("=======================\nGauss\n=======================\n");
    gaussElim(matA_EZ, 3, 4, matB_EZ, matX_EZ);
    freeMat(matA_EZ, 3, 4);
//    printf("=======================\nGauss\n=======================\n");
//    gaussElim(matA, ROWS, COLS, matB, matX);
//    freeMat(matA, ROWS, COLS);
    return 0;
}
