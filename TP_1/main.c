#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define N 15
#define DEBUG printf("file %s; line %d", __FILE__, __LINE__);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG; exit(EXIT_FAILURE);

#include "matrices.h"
#include "toolbox.h"

int main() {

    srand(time(NULL));

    int *matB = (int *) malloc(N * sizeof(int));
    fillMatB(matB, N);

    printf("\nMatrix B:\n");
    printMatB(matB, N);

    int **bord = mkIntSquareMAt(N);

    fillBord(bord, N);

    printf("\nBord:\n");
    printIntMatrix(bord, N);
//    free(bord);

    double **dingDong = mkDoubleSquareMat(N);

    fillDingDong(dingDong, N);

    printf("\nDing Dong:\n");
    printDoubleMatrix(dingDong, N);
//    free(dingDong);

    return 0;
}
