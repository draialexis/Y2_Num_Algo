#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <math.h>
#include "matrices.h"
#define N 5


int main() {

    srand(time(NULL));

    int * matB = (int *)malloc(N * sizeof(int));
    fillMatB(matB, N);

    printf("\nMatrix B:\n");
    printMatB(matB, N);

    int * bord = (int *)malloc(N * N * sizeof(int));

    fillBord(bord, N);

    printf("\nBord:\n");
    printIntMatrix(bord, N);
//    free(bord);

    double * dingDong = (double *)malloc(N * N * sizeof(double));

    fillDingDong(dingDong, N);

    printf("\nDing Dong:\n");
    printDoubleMatrix(dingDong, N);
//    free(dingDong);

    return 0;
}
