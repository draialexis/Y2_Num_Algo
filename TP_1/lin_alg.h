//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rows, cols, B);

void solveForX(double **A, int rows, int cols, double *B, double *X) {
    int isCoef1Triangle = 1;
    int isNilRow;
    int nilRows = 0;
    for (int i = 0; i < rows; ++i) {
        isNilRow = 1;
        for (int j = 0; j <= i; ++j) {
            if (isNilRow && A[i][j] != 0) {
                isNilRow = 0;
            }
            if (i == j && A[i][j] != 1) {
                isCoef1Triangle = 0;
                SHOWME
            }
            if (i < j && A[i][j] != 0) {
                isCoef1Triangle = 0;
                SHOWME
            }
        }
        if (isNilRow) {
            if (B[i] != 0) {
                printf("A * X = B cannot be solved with Gauss (0 =/= 0)\n");
                free(X);
                return;
            }
            nilRows++;
        }
    }
    if (isCoef1Triangle) {
        X[cols - 1] = B[cols - 1];
        for (int i = cols - 1; i >= 0; --i) {
            X[i] = B[i];
//        printf("X(%d) = B(%d)(%+06.1f)", i + 1, i + 1, X[i], B[i]);
            for (int j = i + 1; j < cols; ++j) {
//            printf(" - A(%d %d) * X(%d)(%+06.1f * %+06.1f)", i + 1, j + 1, i + 2, A[i][j], X[i + 1]);
                X[i] -= A[i][j] * X[j];
            }
//        printf("\n");
        }
    }
    printf("X = \n");
    showCol(X, cols);
}

// this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rows, int cols, double *B, double *X) {
    if (A == NULL || B == NULL || X == NULL || rows <= 0 || cols <= 0) {
        EMPTY_OR_NULL
        exit(0);
    }
    SHOWME
    double factor = 0;
    double inverse = 0;

    //TODO make sure proportional rows disappear naturally
    for (int i = 0; i < rows; ++i) {
        printf("__i = %d\n", i);
        for (int j = 0; j <= i && j < cols; ++j) {
            printf("__j = %d\n", j);
            if (A[i][j] == 0 && i == j) {
                for (int k = i + 1; k < rows; ++k) {
                    if (A[k][j] != 0) {
                        printf("L%d <-> L%d\n", i + 1, k + 1);
                        rowSwap(A, B, i, k, cols);
                        i--; // we want to make sure to come back to where we found the A(i, j) == 0 && i == j, now that it's fixed
                        SHOWME
                        break;
                    }
                }
            } else {
                if (A[i][j] != 1 && i == j) {
                    inverse = 1 / A[i][j];
                    printf("L%d <- L%d * %+06.1f\n", i + 1, i + 1, inverse);
                    rowMult(A[j], cols, inverse);
                    B[i] *= inverse;
                    SHOWME
                }
                for (int k = i + 1; k < rows; ++k) {
                    printf("__k = %d\n", k);
                    factor = (A[k][j]);
                    if (factor != 0) {
                        printf("factor = %+020.20f\n", factor);
                        if (k != j) {
                            printf("L%d <- L%d - (%+06.1f * L%d)\n", k + 1, k + 1, factor, i + 1);
                            rowSub(A[k], cols, A[i], factor);
                            B[k] -= factor * B[i];
                            SHOWME
                        }
                    }
                }
            }
        }
    }
    solveForX(A, rows, cols, B, X);
}

#endif //Y2_NUM_ALGO_LIN_ALG_H
