//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rows, cols, B);

void solveForX(double **A, int rows, int cols, double *B, double *X);

void gaussElim(double **A, int rows, int cols, double *B, double *X);

void solveForX(double **A, int rows, int cols, double *B, double *X) {
    if (A == NULL || B == NULL || X == NULL || rows <= 0 || cols <= 0) {
        printf("How on Earth?!\n");
        EMPTY_OR_NULL
        FAIL_OUT
    }
    int isTriangular = 1; // we suppose from the start that it is triangular, and we will test that claim
    int isNilRow;
    int nilRows = 0;
    int n = cols - 1;
    // in case we can ignore the bottom rows (000|0) and focus on the non-empty square subset of the matrix, thanks to Gauss
    // so we would deal with A(p,p), B(p) and X(p). Remember that X has as many rows as A has cols; we can count on that
    for (int i = 0; i < rows; ++i) {
        isNilRow = 1;
        for (int j = 0; j <= i && j < cols; ++j) {
            // watching out for out-of-bounds cases where we have more rows than cols
            if (isNilRow && A[i][j] != 0) {
                isNilRow = 0;
            }
            if (i == j && fabs(A[i][j]) < EPSILON && isTriangular) {
                isTriangular = 0;
            }
            if (i < j && fabs(A[i][j]) > EPSILON && isTriangular) {
                isTriangular = 0;
            }
        }
        if (isNilRow) {
            nilRows++;
            if (fabs(B[i]) > EPSILON) { // deal with absence of solution (an empty i row corresponding to a non-0 B(i))
                SHOWME
                printf("A * X = B has no solution (L%d: %f != %f)\n", i + 1, A[i][i], B[i]);
                free(X);
                return;
            } else if ((rows - nilRows < cols) && isTriangular) {
                // if an empty rows turns a rectangular matrix into a square matrix, that's great (cols == rows - nilrows)
                // but if it makes it so there are less non-empty rows than there are unknowns, our solution needs to be adapted
                // (infinity of solutions)
                isTriangular = 0;
            }
        }
    }

    if (isTriangular && rows - nilRows == cols) { // deal with unique solution
        printf("X[%d] = B[%d] / A[%d][%d]\n", n, n, n, n);
        printf("X[%d] = %f / %f = %f\n", n, B[n], A[n][n], B[n] / A[n][n]);
        printf("here: A[%d][%d]\n", n, n);

        X[n] = B[n] / A[n][n];
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0;
            for (int j = i + 1; j < cols; ++j) {
                printf("here: A[%d][%d]\n", i, j);
                sum += A[i][j] * X[j];
            }
            printf("here: A[%d][%d]\n", i, i);

            X[i] = (B[i] - sum) / A[i][i];
        }
        SHOWME
        printf("A * X = B has one solution\n");
        printf("X = \n");
        showCol(X, cols);
        free(X);
    } else if (rows - nilRows < cols) {// could probably just be phrased as "else"
        // deal with infinite solutions (with parameters)
        int params = cols - (rows - nilRows);
        printf("X[%d] = B[%d] / A[%d][%d]\n", n, n, n, n);
        printf("X[%d] = %f / %f = %f\n", n, B[n], A[n][n], B[n] / A[n][n]);
        printf("here: A[%d][%d]\n", n, n);

        for (int i = n; i >= rows - nilRows; --i) {
            params++;
        }

        X[n] = B[n] / A[n][n];
        for (int i = n - 1; i >= 0; --i) {
            double sum = 0;
            for (int j = i + 1; j < cols; ++j) {
                printf("here: A[%d][%d]\n", i, j);
                sum += A[i][j] * X[j];
            }
            printf("here: A[%d][%d]\n", i, i);
            X[i] = (B[i] - sum) / A[i][i];
        }
        SHOWME
        printf("A * X = B has an infinite number of solutions\nIMPLEMENT\n");
        //TODO add set of solutions to the related homogeneous system...?
    } else {
        printf("we shouldn't be here... no solutions, right?\n");
        SHOWME
        DEBUG
    }
}

// this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rows, int cols, double *B, double *X) {
    if (A == NULL || B == NULL || X == NULL || rows <= 0 || cols <= 0) {
        EMPTY_OR_NULL
        FAIL_OUT
    }
    SHOWME
    double factor;
    for (int i = 0; i < rows; ++i) {
        printf("__i = %d\n", i);
        for (int j = 0; j <= i && j < cols; ++j) {
            printf("__j = %d\n", j);
            if (fabs(A[i][j]) < EPSILON && i == j) {
                for (int k = i + 1; k < rows; ++k) {
                    printf("1_k = %d\n", k);
//                    printf("%+.1000f < %+.1000f?\n", fabs(A[k][j]), EPSILON);
                    if (fabs(A[k][j]) > EPSILON && i != k) {
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
                        printf("L%d <- L%d - (%+06.1f * L%d)\n", k + 1, k + 1, factor, i + 1);
                        rowTransform(A[k], cols, A[i], factor);
                        B[k] -= factor * B[i];
                        SHOWME
                    }
                }
            }
        }
    }
    printf("solving...\n");
    solveForX(A, rows, cols, B, X);
}


#endif //Y2_NUM_ALGO_LIN_ALG_H
