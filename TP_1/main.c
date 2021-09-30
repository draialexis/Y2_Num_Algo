#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 3
#define COLS 4
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG; exit(EXIT_FAILURE);
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "matrices.h"
#include "toolbox.h"
#include "lin_alg.h"

int main() {

    // TODO check out https://ent.uca.fr/moodle/mod/forum/discuss.php?d=148630

    srand(time(NULL));

    int *matB = (int *) malloc(ROWS * sizeof(int));
    fillMatB_rdm(matB, ROWS);

    printf("\nMatrix B:\n");
    showColVect(matB, ROWS);

    int **bord = mkIntMat(ROWS, ROWS);//square

    fillBord(bord, ROWS);

    printf("\nBord:\n");
    showMat_i(bord, ROWS, ROWS);//square

    double **dingDong = mkDoubleMat(ROWS, ROWS);//square
    fillDingDong(dingDong, ROWS);

    printf("\nDing Dong:\n");

    showMat_d(dingDong, ROWS, ROWS);//square

    printf("\n");

    int ** matA_EZ = mkIntMat(3, 3);
    fillMat_EZ(matA_EZ, 3);

//    {
//            {1,  -2, -1},
//            {2,  -5, -4},
//            {-3, 1,  -5}
//    };

    showMat_i(matA_EZ, 3, 3);
    printf("*\n");
    int matX_EZ[3]; //to be filled. temporary
    showColVect(matX_EZ, 3);
    printf("=\n");
    int matB_EZ[3] = {2, 6, 1};
    showColVect(matB_EZ, 3);

    printf("Gauss\n");
    printf("before\n");
    showMat_i(matA_EZ, 3, 3);
    gaussElim_i(matA_EZ, 3, 3, matB_EZ);
    printf("after\n");
    showMat_i(matA_EZ, 3, 3);

    freeMat_i(bord, ROWS, ROWS);
    freeMat_d(dingDong, ROWS, ROWS);
    freeMat_i(matA_EZ, ROWS, ROWS);
//    free(matB_EZ);
//    free(matX_EZ);
    return 0;
}
