//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rowsA, colsA, B);

void jacobiMethod(double **A, int rowsA, int colsA, double *B, int maxIteration, double error);

void gaussMethod(double **A, int rowsA, int colsA, double *B, int isJacobiHelper);

void solveGauss(double **A, int rowsA, int colsA, double *B, int homSys);

// NB: this destructive function changes the matrices as a side-effect
void gaussMethod(double **A, int rowsA, int colsA, double *B, int isJacobiHelper) {
    //// O(n^2) * 8 bits used, for matrix of doubles
    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL) {
        if (rowsA < 2 || colsA < 2) {
            printf("we will not deal with a matA(m, n) if m or n is below 2\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    printf("=======================\nGauss\n=======================\n");


    int homSys = isHomSys(B, rowsA); //if B is nil, our job might just be made a lot easier

    SHOWME
    double factor;
    for (int i = 0; i < rowsA; i++) {
        int maxPos = i;
        double maxVal = fabs(A[maxPos][i]);

        for (int k = i + 1; k < rowsA; ++k) {
            if (fabs(A[k][i]) - maxVal > EPSILON) { // swapping rows so that our leading coefficients are greater
                maxVal = fabs(A[k][i]);
                                // sum from i+1 to n : (n(n+1)/2) - 1 + (n(n+1)/2) - 2 + ... -> O(n²) calls to fabs()
                maxPos = k;
            }
        }

        if (maxPos != i) {
            printf("L%d <-> L%d\n", i + 1, maxPos + 1);
            rowSwap(A, B, i, maxPos, colsA);                                               //at worst 2n attributions
            SHOWME
        }

        for (int k = i + 1; k < rowsA; ++k) {
            if (fabs(A[k][i]) < EPSILON || fabs(A[i][i]) < EPSILON) {
                //to make sure we don't handle numbers too small, for stability
                continue;
            } else {
                factor = (A[k][i] / A[i][i]);
                                //// at worst (n(n+1)/2) - 1 + (n(n+1)/2) - 2 + ... -> O(n^2) arithmetic operations
                printf("L%d <- L%d - (%+06.1f * L%d)\n", k + 1, k + 1, factor, i + 1);
                rowTransform(A[k], colsA, A[i], factor);
                          //// at worst n * ((n(n+1)/2) - 1 + (n(n+1)/2) - 2 + ...) -> O(n^3) arithmetic operations
                B[k] -= factor * B[i];
                                //// at worst (n(n+1)/2) - 1 + (n(n+1)/2) - 2 + ... -> O(n^2) arithmetic operations
                SHOWME
            }
        }
    }
    if (!isJacobiHelper) {
        solveGauss(A, rowsA, colsA, B, homSys);                                //// -> O(n^2) arithmetic operations
    }
}

// NB: this destructive function could change the matrices as a side-effect
void solveGauss(double **A, int rowsA, int colsA, double *B, int homSys) {
    if (A == NULL || B == NULL || rowsA <= 0 || colsA <= 0) {
        printf("How on Earth?!\n");
        EMPTY_OR_NULL
        FAIL_OUT
    }
    int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys);         //// at worst n^2 artihmetic operations -> O(n^2)
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
                                 //// at worst (n(n+1)/2) - 1 + (n(n+1)/2) - 2 + ... -> O(n^2) arithmetic operations
                }
                X[i] = (B[i] - sum) / A[i][i];                          //// at worst n arithmetic operations -> O(n)
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

// NB: this destructive function could change the matrices as a side-effect
void jacobiMethod(double **A, int rowsA, int colsA, double *B, int maxIteration, double error) {
    //// O(n^2) * 8 bits used, for matrix of doubles
    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL || maxIteration < 1 || fabs(error) < EPSILON) {
        printf("les matrices doivent etre non-nulles, A doit etre au moins (2, 2), max_iterations doit etre superieur a 1,"
               " l'epsilon ne peut pas etre inferieur a l'epsilon de la machine (%.30f)\n", EPSILON);
        EMPTY_OR_NULL
        FAIL_OUT
    }
    printf("=======================\nJacobi\n=======================\n");

    int homSys = isHomSys(B, rowsA);

    if (colsA > rowsA) {
        printf("A * X = B a une infinite de solutions\n");
        if (homSys) {
            printf("...y compris le vecteur 0(%d)\n", colsA);
        }
    }
    if (colsA < rowsA) { // not a square matrix, but we may be able to save it
        gaussMethod(A, rowsA, colsA, B, 1); //// at worst O(n^3) arithmetic operations
    }
    int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys); /// at worst O(n^2) arithmetic operations
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
                            sum += A[i][j] * X[j];  //// at worst (max_it) * (n^2) -> O(n^3) arithmetic operations
                        }
                    }
                    Xprev[i] = X[i];
                    X[i] = (1 / A[i][i]) * (B[i] - sum);//// at worst 2((max_it) * (n)) -> O(n^2) arithmetic operations
                    if (isStable && fabs(Xprev[i] - X[i]) > error) {
                        isStable = 0;
                    }
                }

                printf("iteration #%d\n", counter);
                showCol(X, size);

                if (isStable) {
                    showEqSys(A, size, size, B);
                    printf("a l'iteration #%d, l'approximation s'est stabilisee en dessous de l'epsilon %.10f\n"
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

#endif //Y2_NUM_ALGO_LIN_ALG_H
