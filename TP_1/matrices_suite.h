#ifndef Y2_NUM_ALGO_MATRICES_SUITE_H
#define Y2_NUM_ALGO_MATRICES_SUITE_H

#include <math.h>

void fillMatB_rdm(double *mat, int n) {
    for (int i = 0; i < n; ++i) {
        mat[i] = rand() % 3;
    }
}

void fillMatA_rdm(double **mat, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mat[i][j] = rand() % 3;
        }
    }
}

void fillMatA_userInput(double **mat, int rows, int cols) {
    double input = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            printf("A[%d][%d] <- ", i + 1, j + 1);
            scanf("%lf", &input);
            mat[i][j] = input;
        }
    }
}

void fillMatB_userInput(double *mat, int rows) {
    double input = 0;
    for (int i = 0; i < rows; ++i) {
        printf("B[%d] <- ", i + 1);
        scanf("%lf", &input);
        mat[i] = input;
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

void fillMat_EZ(double **mat) {
    mat[0][0] = 1.0;//1
    mat[0][1] = -2.0;//-2
    mat[0][2] = -1.0;//-1
    mat[1][0] = 2.0;//2
    mat[1][1] = -5.0;//-5
    mat[1][2] = -4.0;//-4
    mat[2][0] = -3.0;//-3
    mat[2][1] = 1.0;//1
    mat[2][2] = -5.0;//-5
    /*
     * Solution:
     * [+2.5
     *  +1
     *  -1.5]
     */
}

#endif //Y2_NUM_ALGO_MATRICES_SUITE_H
