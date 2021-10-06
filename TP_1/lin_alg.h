//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rowsA, colsA, B);

void solveForX(double **A, int rowsA, int colsA, double *B, double *X, int homSys);

void gaussElim(double **A, int rowsA, int colsA, double *B, double *X, int isJacobiHelper);

void jacobiMethod(double **A, int rowsA, int colsA, double *B, double *X, int maxIteration, double error);

void jacobiMethod(double **A, int rowsA, int colsA, double *B, double *X, int maxIteration, double error) {
    if(A == NULL || rowsA < 2 || colsA < 2 || B == NULL || X == NULL || maxIteration < 1 || error < EPSILON){
        printf("les matrices doivent etre non-nulles, A doit etre au moins (2, 2), max_iterations doit etre superieur a 1,"
               " l'epsilon ne peut pas etre inferieur a l'epsilon de la machine (%.30f)", EPSILON);
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int homSys = isHomSys(B, rowsA);

    if(colsA > rowsA) {
        printf("A * X = B a une infinite de solutions\n");
        if (homSys) {
            printf("...y compris le vecteur 0(%d)\n", colsA);
        }
    }
    int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys);
    if(nilRowsCount == -1) {
        return;
    }
    if(rowsA - nilRowsCount == colsA) {// the matrix is square after all, let's go
        int strictDiagDom = isSDD(double **matA, int rowsA, int colsA);


    }

}

void solveForX(double **A, int rowsA, int colsA, double *B, double *X, int homSys) {
    if (A == NULL || B == NULL || X == NULL || rowsA <= 0 || colsA <= 0) {
        printf("How on Earth?!\n");
        EMPTY_OR_NULL
        FAIL_OUT
    }
    int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys);
    if(nilRowsCount == -1) {
        return;
    }

    if (rowsA - nilRowsCount == colsA) { // deal with unique solution
        printf("A * X = B a une solution\n");

        if (homSys) {
            printf("...le vecteur 0(%d)\n", colsA);
        } else {
            X[colsA - 1] = B[colsA - 1] / A[colsA - 1][colsA - 1];
            for (int i = colsA - 2; i >= 0; i--) { //we've already dealt with i = colsA - 1
                double sum = 0;
                for (int j = i + 1; j < colsA; j++) {
                    sum += A[i][j] * X[j];
                }
                X[i] = (B[i] - sum) / A[i][i];
            }
            printf("X = \n");
            showCol(X, colsA);
        }
    } else if (rowsA - nilRowsCount < colsA) { // "deal" with infinite amount of solutions
        // could probably just be phrased as "else"
        printf("A * X = B a une infinite de solutions\n");
        if (homSys) {
            printf("...y compris le vecteur 0(%d)\n", colsA);
        }
    } else {
        printf("we shouldn't be here... no solutions, right?\n");
        DEBUG
    }
}

// NB: this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rowsA, int colsA, double *B, double *X, int isJacobiHelper) {
    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL || X == NULL) {
        if (rowsA < 2 || colsA < 2) {
            printf("we will not deal with a matA(m, n) if m or n is below 2\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int homSys = isHomSys(B, rowsA);

    SHOWME
    double factor;
    for (int i = 0; i < rowsA; i++) {
        int maxPos = i;
        double maxVal = fabs(A[maxPos][i]);

        for (int k = i + 1; k < rowsA; ++k) {
            if (fabs(A[k][i]) - maxVal > EPSILON) {
                maxVal = fabs(A[k][i]);
                maxPos = k;
            }
        }

        if (maxPos != i) {
            printf("L%d <-> L%d\n", i + 1, maxPos + 1);
            rowSwap(A, B, i, maxPos, colsA);
            SHOWME
        }

        for (int k = i + 1; k < rowsA; ++k) {
            if (fabs(A[k][i]) < EPSILON || fabs(A[i][i]) < EPSILON) {
                //to make sure we don't handle numbers too small, for stability
                continue;
            } else {
                factor = (A[k][i] / A[i][i]);
                printf("L%d <- L%d - (%+06.1f * L%d)\n", k + 1, k + 1, factor, i + 1);
                rowTransform(A[k], colsA, A[i], factor);
                B[k] -= factor * B[i];
                SHOWME
            }
        }
    }
    if(!isJacobiHelper){
        solveForX(A, rowsA, colsA, B, X, homSys);
    } else {
        jacobiMethod(A, rowsA, colsA, B, X, 20, 0.001); //arbitrary values for testing purposes
    }
}

#endif //Y2_NUM_ALGO_LIN_ALG_H
