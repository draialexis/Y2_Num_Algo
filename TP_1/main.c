#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 3
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

    double *matB = (double *) malloc(ROWS * sizeof(double));
    fillMatB_rdm(matB, ROWS);

    printf("Matrix B:\n");
    showCol(matB, ROWS, 0);

    double **bord = mkMat(ROWS, ROWS);//square

    fillBord(bord, ROWS);

    printf("Bord:\n");
    showMat(bord, ROWS, ROWS);//square

    double **dingDong = mkMat(ROWS, ROWS);//square
    fillDingDong(dingDong, ROWS);

    printf("Ding Dong:\n");

    showMat(dingDong, ROWS, ROWS);//square

    printf("=======================\n");

    double **matA_EZ = mkMat(3, 3);
    fillMat_EZ(matA_EZ, 3);

//    {
//            {1,  -2, -1},
//            {2,  -5, -4},
//            {-3, 1,  -5}
//    };

    showMat(matA_EZ, 3, 3);
    printf("*\n");
    double matX_EZ[3]; //to be filled. temporary
    showCol(matX_EZ, 3, 1);
    printf("=\n");
    double matB_EZ[3] = {2, 6, 1};
    showCol(matB_EZ, 3, 0);

    printf("=======================\nGauss\n=======================\n");
    printf("initial:\n");
    showEqSys(matA_EZ, 3, 3, matB_EZ);
    gaussElim(matA_EZ, 3, 3, matB_EZ);
    printf("final:\n");
    showEqSys(matA_EZ, 3, 3, matB_EZ);


    freeMat(bord, ROWS, ROWS);
    freeMat(dingDong, ROWS, ROWS);
    freeMat(matA_EZ, ROWS, ROWS);
//    free(matB_EZ);
//    free(matX_EZ);
    return 0;
}
