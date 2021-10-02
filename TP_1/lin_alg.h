//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rows, cols, B);

#define EPSILON 0.000000000000000222044604925031

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
            if (i == j && A[i][j] != 1) { //TODO change, we don't want coeff 1 anymore
                isCoef1Triangle = 0;
                SHOWME
            }
            if (i < j && A[i][j] != 0) {
                isCoef1Triangle = 0;
                SHOWME
            }
        }
        if (isNilRow) {
            if (B[i] < EPSILON) {
                printf("A * X = B cannot be solved with Gauss (0 =/= 0)\n");
                free(X);
                return;
            }
            nilRows++;
        }
    }
    if (isCoef1Triangle) {
        X[cols - 1] = B[cols - 1] / A[rows - 1][cols - 1];
        printf("yo\n");
        for (int i = cols - 2; i >= 0; --i) {
            double sum = 0;
            for (int j = i + 1; j < cols; ++j) {
                sum += A[i][j] * X[j];
            }
            X[i] = (B[i] - sum) / A[i][i];
            printf("yo\n");
        }
    }
    printf("X = \n");
    showCol(X, cols);
    free(X);
}

// this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rows, int cols, double *B, double *X) {
    if (A == NULL || B == NULL || X == NULL || rows <= 0 || cols <= 0) {
        EMPTY_OR_NULL
        exit(0);
    }
    SHOWME
    double factor;

    //TODO make sure proportional rows disappear naturally
    for (int i = 0; i < rows; ++i) {
        printf("__i = %d\n", i);
        for (int j = 0; j <= i && j < cols; ++j) {
            printf("__j = %d\n", j);
            if ((fabs(A[i][j]) < EPSILON || A[i][j] == 0.0) && i == j) {
                for (int k = i + 1; k < rows; ++k) {
                    printf("1_k = %d\n", k);
                    printf("%+.30f < %+.30f?\n", fabs(A[k][j]), EPSILON);
                    if (fabs(A[k][j]) > EPSILON || A[k][j] != 0.0) {
                        printf("L%d <-> L%d\n", i + 1, k + 1);
                        rowSwap(A, B, i, k, cols);
                        i--; // we want to make sure to come back to where we found the A(i, j) == 0 && i == j, now that it's fixed
                        SHOWME
                        break;
                    }
                }
            } else {
                for (int k = i + 1; k < rows; ++k) {
                    printf("2_k = %d\n", k);
                    factor = (A[k][j] / A[i][j]);
                    if (fabs(A[k][j]) < EPSILON) {
                        continue;
                    } else {
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
//TODO factorization
}


#endif //Y2_NUM_ALGO_LIN_ALG_H
