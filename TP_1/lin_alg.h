//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H


// this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rows, int cols, double *B) {

    double factor;
    //TODO remember I'm treating mats B and X as 1d-arrays

    if (cols < 2) {
        printf("yeah, right\n");
        DEBUG
        exit(0);
    }

    //TODO make sure proportional rows disappear naturally
    for (int i = 0; i < rows; ++i) {
        printf("__i = %d\n", i);
        for (int j = 0; j <= i; ++j) {
            printf("__j = %d\n", j);
            if (A[i][j] != 0) {
                if (A[i][j] != 1) {
                    factor = 1 / A[i][j];
                    printf("L%d <- L%d * %+06.3f\n", i + 1, i + 1, factor);
                    rowMult(A[j], cols, factor);
                    B[i] *= factor;
                    showEqSys(A, rows, cols, B);////
                }
                for (int k = i + 1; k < rows; ++k) {
                    printf("__k = %d\n", k);
                    factor = (A[k][j]);
                    if (factor != 0) {
                        if (k != j) {
                            printf("L%d <- L%d - (%+06.3f * L%d)\n", k + 1, k + 1, factor, i + 1);
                            rowSub(A[k], cols, A[i], factor);
                            B[k] -= factor * B[i];
                            showEqSys(A, rows, cols, B);////
                        }
                    }
                }
            } else {
                for (int k = i + 1; k < rows; ++k) {
                    if (A[k][j] != 0) {
                        printf("L%d <-> L%d\n", i + 1, k + 1);
                        rowSwap(A, B, i, k, cols);
                        showEqSys(A, rows, cols, B);////
                        i--; // we want to make sure to come back to where we found the A(i, j) == 0 && i == j, now that it's fixed
                        break;
                    }
                }
            }
        }
    }
}

#endif //Y2_NUM_ALGO_LIN_ALG_H
