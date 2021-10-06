//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rowsA, colsA, B);

void jacobiMethod(double **A, int rowsA, int colsA, double *B, int maxIteration, double error);

void gaussMethod(double **A, int rowsA, int colsA, double *B, int isJacobiHelper);

void solveGauss(double **A, int rowsA, int colsA, double *B, int homSys);

void jacobiMethod(double **A, int rowsA, int colsA, double *B, int maxIteration, double error) {
    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL || maxIteration < 1 || fabs(error) < EPSILON) {
        printf("les matrices doivent etre non-nulles, A doit etre au moins (2, 2), max_iterations doit etre superieur a 1,"
               " l'epsilon ne peut pas etre inferieur a l'epsilon de la machine (%.30f)\n", EPSILON);
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int homSys = isHomSys(B, rowsA);

    if (colsA > rowsA) {
        printf("A * X = B a une infinite de solutions\n");
        if (homSys) {
            printf("...y compris le vecteur 0(%d)\n", colsA);
        }
    }
    if (colsA < rowsA) {
        gaussMethod(A, rowsA, colsA, B, 1);
    }
    int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys);
    if (nilRowsCount == -1) {
        return;
    }
    if (rowsA - nilRowsCount == colsA) {// the matrix is square after all, let's go
        int size = colsA;
        int strictDiagDom = isSDD(A, size);
        //we make sure to only go through the remaining square matrix,
        //and since any nil rows should be at the bottom, this should work
        if (!strictDiagDom) {
            showMat(A, size, size);
            char gaussInstead = '0';
            printf("A n'est pas a diagonale strictement dominante. Jacobi ne peut rien pour nous.\n"
                   "essayer avec Gauss ?\n"
                   "'o' : oui\n"
                   "'n' : non\n>");
            gaussInstead = (char) getchar();
            fflush(stdin);
            if (gaussInstead == 'o') {
                gaussMethod(A, size, size, B, 0);
            }
        } else {
            double *X = mkColVec(size);//our approximations, iteratively improved
            double *Xprev = mkColVec(size);
            for (int i = 0; i < size; ++i) {
                // the initial guess ("X0") is that all our unknowns are 0
                X[i] = 0.0;
                Xprev[i] = 0.0;
            }
            int counter = 1;
            double sum;
            // if convergence is reached, print result and return
            int isStable;
            while (counter <= maxIteration) {
                isStable = 1;
                for (int i = 0; i < size; ++i) {
                    sum = 0.0;
                    for (int j = 0; j < size; ++j) {
                        if (i != j) {
                            sum += A[i][j] * X[j];
                        }
                    }
                    Xprev[i] = X[i];
                    X[i] = (1 / A[i][i]) * (B[i] - sum);
                    if (fabs(Xprev[i] - X[i]) > error) {
                        isStable = 0;
                    }
                }
                if (isStable) {
                    showEqSys(A, size, size, B);
                    printf("apres l'iteration #%d, l'approximation s'est stabilisee en dessous de l'epsilon %.10f\n"
                           "A * X = B a une solution\n"
                           "X ->\n", counter, error);
                    showCol(X, size);
                    break;
                }
                counter++;
            }
            free(X);
        }
    }

}

// NB: this destructive function changes the matrices as a side-effect
void gaussMethod(double **A, int rowsA, int colsA, double *B, int isJacobiHelper) {
    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL) {
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
    if (!isJacobiHelper) {
        solveGauss(A, rowsA, colsA, B, homSys);
    }
}

void solveGauss(double **A, int rowsA, int colsA, double *B, int homSys) {
    if (A == NULL || B == NULL || rowsA <= 0 || colsA <= 0) {
        printf("How on Earth?!\n");
        EMPTY_OR_NULL
        FAIL_OUT
    }
    int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys);
    if (nilRowsCount == -1) {
        return;
    }

    if (rowsA - nilRowsCount == colsA) { // deal with unique solution
        printf("A * X = B a une solution\n");

        if (homSys) {
            printf("...le vecteur 0(%d)\n", colsA);
        } else {
            double *X = mkColVec(colsA);
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
            free(X);
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

#endif //Y2_NUM_ALGO_LIN_ALG_H
