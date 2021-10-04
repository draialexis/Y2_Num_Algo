#ifndef Y2_NUM_ALGO_MATRICES_SUITE_H
#define Y2_NUM_ALGO_MATRICES_SUITE_H

#include <math.h>

void fillMatB_rdm(double *mat, int size);

void fillMatA_rdm(double **mat, int rows, int cols);

void fillMatA_userInput(double **mat, int rows, int cols);

void fillMatB_userInput(double *mat, int rows);

void fillBord(double **bord, int size);

void fillDingDong(double **dingDong, int size);

void fillMat_EZ(double **mat);

void fillMatB_EZ(double *mat);

void fillMatB_rdm(double *mat, int size) {
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            mat[i] = (rand() % 101) + 50;
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatA_rdm(double **mat, int rows, int cols) {
    if (mat != NULL && rows > 0 && cols > 0) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mat[i][j] = (rand() % 101) + 50;
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatA_userInput(double **mat, int rows, int cols) {
    if (mat != NULL && rows > 0 && cols > 0) {
        double input = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                printf("A[%d][%d] <- ", i + 1, j + 1);
                scanf("%lf", &input);
                mat[i][j] = input;
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatB_userInput(double *mat, int rows) {
    if (mat != NULL && rows > 0) {
        double input = 0;
        for (int i = 0; i < rows; ++i) {
            printf("B[%d] <- ", i + 1);
            scanf("%lf", &input);
            mat[i] = input;
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillBord(double **bord, int size) {
    if (bord != NULL && size > 0) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                double *crnt = *(bord + i) + j;
                if (i == j) {
                    *crnt = 1;
                } else if (i + 1 == size) {
                    *crnt = (int) pow(2, (size - (j + 1)));
                } else if (j + 1 == size) {
                    *crnt = (int) pow(2, (size - (i + 1)));
                } else {
                    *crnt = 0;
                }
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillDingDong(double **dingDong, int size) {
    if (dingDong != NULL && size > 0) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                *(*(dingDong + i) + j) = (double) 1 / (2 * (size - (i + 1) - (j + 1) + 1.5));
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMat_EZ(double **mat) {
    if (mat != NULL) {
        mat[0][0] = 1.0;//1
        mat[0][1] = -2.0;//-2
        mat[0][2] = -1.0;//-1
//        mat[0][3] = -1.0;
//        mat[0][4] = 2.0;
        mat[1][0] = 2.0;//2
        mat[1][1] = -5.0;//-5
        mat[1][2] = -4.0;//-4
//        mat[1][3] = -1.0;
//        mat[1][4] = 5.0;
        mat[2][0] = -3.0;//-3
        mat[2][1] = 1.0;//1
        mat[2][2] = -5.0;//-5
//        mat[2][3] = -7.0;
//        mat[2][4] = -4.0;
        mat[3][0] = 3.0;
        mat[3][1] = -6.0;// 3 * L1
        mat[3][2] = -3.0;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatB_EZ(double *mat) {
    if (mat != NULL) {
        mat[0] = 2.0;//2
        mat[1] = 6.0;//6
        mat[2] = 1.0;//1
        mat[3] = 6.0;// 3 * L1
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

#endif //Y2_NUM_ALGO_MATRICES_SUITE_H
