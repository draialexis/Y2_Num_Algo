#ifndef Y2_NUM_ALGO_MATRICES_SUITE_H
#define Y2_NUM_ALGO_MATRICES_SUITE_H

#include <math.h>

void fillMatB_rdm(double *matB, int n) {
    for (int i = 0; i < n; ++i) {
        *(matB + i) = rand() % 20;
    }
}

void fillBord(double **bord, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double *crnt = *(bord + i) + j;
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

void fillMat_EZ(double **mat, int n) {
    mat[0][0] = 1;//1
    mat[0][1] = -2;//-2
    mat[0][2] = -1;//-1
    mat[1][0] = 2;//2
    mat[1][1] = -5;//-5
    mat[1][2] = -4;//-4
    mat[2][0] = -3;//-2
    mat[2][1] = 1;//1
    mat[2][2] = -5;//-5
}

#endif //Y2_NUM_ALGO_MATRICES_SUITE_H
