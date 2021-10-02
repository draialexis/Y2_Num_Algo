#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 5
#define COLS 4
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG; exit(EXIT_FAILURE);
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "matrices_suite.h"
#include "toolbox.h"
#include "lin_alg.h"

int main() {

    // TODO check out https://ent.uca.fr/moodle/mod/forum/discuss.php?d=148630

    srand(time(NULL));
    double **matA = mkMat(ROWS, COLS);
    fillMatA_rdm(matA, ROWS, COLS);
    double **matA_EZ = mkMat(3, 3);
    fillMat_EZ(matA_EZ);

    double *matX = mkColVec(COLS);// A(m,n) * X(_n_, p) = B(m, p) // p = 1
    double *matX_EZ = mkColVec(3);
    //X will be freed and a message will appear in the console, if the system is unsolvable)


    double *matB = mkColVec(ROWS);
    fillMatB_rdm(matB, ROWS);
    double matB_EZ[3] = {2, 6, 1};

    printf("=======================\nGauss\n=======================\n");
    gaussElim(matA_EZ, 3, 3, matB_EZ, matX_EZ);
    freeMat(matA_EZ, 3, 3);
//    printf("=======================\nGauss\n=======================\n");
//    gaussElim(matA, ROWS, COLS, matB, matX);
//    freeMat(matA, ROWS, COLS);


    return 0;
}
