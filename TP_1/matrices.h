#ifndef Y2_NUM_ALGO_MATRICES_H
#define Y2_NUM_ALGO_MATRICES_H

#include <math.h>

void fillMatB_rdm(int *matB, int n) {
    for (int i = 0; i < n; ++i) {
        *(matB + i) = rand() % 20;
    }
}

void fillBord(int **bord, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int *crnt = *(bord + i) + j;
            if (i == j) {
                *crnt = 1;
            } else if (i + 1 == n) {
                *crnt = (int) pow(2, (n - (j + 1)));
            } else if (j + 1 == n) {
                *crnt = (int) pow(2, (n - (i + 1)));
            } else {
                *crnt = 0;
            }
        }
    }
}

void fillDingDong(double **dingDong, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(*(dingDong + i) + j) = (double) 1 / (2 * (n - (i + 1) - (j + 1) + 1.5));
        }
    }
}

void fillMat_EZ(int **mat, int n) {
    mat[0][0] = 0;//change back to 1...
    mat[0][1] = -2;
    mat[0][2] = -1;
    mat[1][0] = 2;
    mat[1][1] = -5;
    mat[1][2] = -4;
    mat[2][0] = -3;
    mat[2][1] = 1;
    mat[2][2] = -5;
}

#endif //Y2_NUM_ALGO_MATRICES_H
