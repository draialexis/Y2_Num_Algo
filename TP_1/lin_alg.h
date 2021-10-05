//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rowsA, colsA, B);

void solveForX(double **A, int rowsA, int colsA, double *B, double *X, int homSys);

void gaussElim(double **A, int rowsA, int colsA, double *B, double *X);

void solveForX(double **A, int rowsA, int colsA, double *B, double *X, int homSys) {
    if (A == NULL || B == NULL || X == NULL || rowsA <= 0 || colsA <= 0) {
        printf("How on Earth?!\n");
        EMPTY_OR_NULL
        FAIL_OUT
    }
    int isNilRow = 1;
    int nilRows = 0;
    // in case we can ignore the bottom rows (000|0) and focus on the non-empty square subset of the matrix, thanks to Gauss
    // so we would deal with A(p,p), B(p) and X(p). Remember that X has as many rows as A has cols; we can count on that
    for (int i = rowsA -1 ; i >= 0; --i) {
        // we want to check for nil rows starting from the bottom: the forward elimination from the gauss function
        // will have placed those at the very bottom
        for (int j = 0; j < colsA; ++j) {
            if (isNilRow && fabs(A[i][j]) > EPSILON) { //any non-0s in the rows?
                isNilRow = 0;
            }
        }
        if (isNilRow) {
            nilRows++;
            if (fabs(B[i]) > EPSILON) { // deal with absence of solution (an empty i row corresponding to a non-0 B(i))
                SHOWME
                printf("A * X = B has no solution (L%d: 0.0 * x%d = %.1f)\n", i + 1, i + 1, B[i]);
                if (homSys) {
                    printf("...except the 0(%d)-vector\n", colsA);
                }
                free(X);
                return;
            }
        }
    }

    if (rowsA - nilRows == colsA) { // deal with unique solution
        SHOWME
        printf("A * X = B has one solution\n");

        if (homSys) {
            printf("...the 0(%d)-vector\n", colsA);
        } else {
            X[colsA - 1] = B[colsA - 1] / A[colsA - 1][colsA - 1];
            for (int i = colsA - 2; i >= 0; --i) { //we've already dealt with i = colsA - 1
                double sum = 0;
                for (int j = i + 1; j < colsA; ++j) {
                    sum += A[i][j] * X[j];
                }
                X[i] = (B[i] - sum) / A[i][i];
            }
            printf("X = \n");
            showCol(X, colsA);
        }
        free(X);
    } else if (rowsA - nilRows < colsA) { // deal with infinite amount of solutions
        // could probably just be phrased as "else"
        printf("A * X = B has an infinite amount of solutions\n");
        if (homSys) {
            printf("...including the 0(%d)-vector\n", colsA);
        }
    } else {
        printf("we shouldn't be here... no solutions, right?\n");
        SHOWME
        DEBUG
    }
}

// NB: this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rowsA, int colsA, double *B, double *X) {
    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL || X == NULL) {
        if (rowsA < 2 || colsA < 2) {
            printf("we will not deal with a matA(m, n) if m or n is below 2\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int homSys = 1;// dealing with homogeneous systems
    for (int i = 0; i < rowsA; ++i) {
        if (homSys && B[i] > EPSILON) {
            homSys = 0;
        }
    }

    SHOWME
    double factor;
    for (int i = 0; i < rowsA; ++i) {
        int maxPos = i;
        double maxVal = fabs(A[maxPos][i]);

        for (int k = i + 1; k < rowsA; ++k) {
            if (fabs(A[k][i]) - maxVal > EPSILON) {
                maxVal = fabs(A[k][i]);
                maxPos = k;
            }
        }

        if (maxPos != i) {
            printf("R%d <-> R%d\n", i + 1, maxPos + 1);
            rowSwap(A, B, i, maxPos, colsA);
            SHOWME
        }

        for (int k = i + 1; k < rowsA; ++k) {
            if (fabs(A[k][i]) < EPSILON || fabs(A[i][i]) < EPSILON) {
                continue;
            } else {
                factor = (A[k][i] / A[i][i]);
                printf("R%d <- R%d - (%+06.1f * R%d)\n", k + 1, k + 1, factor, i + 1);
                rowTransform(A[k], colsA, A[i], factor);
                B[k] -= factor * B[i];
                SHOWME
            }
        }
    }
    printf("solving...\n");
    solveForX(A, rowsA, colsA, B, X, homSys);
}

#endif //Y2_NUM_ALGO_LIN_ALG_H
