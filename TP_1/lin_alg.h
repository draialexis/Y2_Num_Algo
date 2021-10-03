//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

#define SHOWME showEqSys(A, rowsA, colsA, B);

void solveForX(double **A, int rowsA, int colsA, double *B, double *X, int goDeep);

void gaussElim(double **A, int rowsA, int colsA, double *B, double *X, int goDeep);

void solveForX(double **A, int rowsA, int colsA, double *B, double *X, int goDeep) {
    if (A == NULL || B == NULL || X == NULL || rowsA <= 0 || colsA <= 0) {
        printf("How on Earth?!\n");
        EMPTY_OR_NULL
        FAIL_OUT
    }
    int isTriangular = 1; // we suppose from the start that it is triangular, and we will test that claim
    int isNilRow;
    int nilRows = 0;
    // in case we can ignore the bottom rowsA (000|0) and focus on the non-empty square subset of the matrix, thanks to Gauss
    // so we would deal with A(p,p), B(p) and X(p). Remember that X has as many rowsA as A has colsA; we can count on that
    for (int i = 0; i < rowsA; ++i) {
        isNilRow = 1;
        for (int j = 0; j <= i && j < colsA; ++j) {
            // watching out for out-of-bounds cases where we have more rowsA than colsA
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
            } else if ((rowsA - nilRows < colsA) && isTriangular) {
                // if an empty rowsA turns a rectangular matrix into a square matrix, that's great (colsA == rowsA - nilrows)
                // but if it makes it so there are less non-empty rowsA than there are unknowns, our solution needs to be adapted
                // (infinity of solutions)
                isTriangular = 0;
            }
        }
    }

    if (isTriangular && rowsA - nilRows == colsA) { // deal with unique solution
//        int n = colsA - 1;
//        printf("X[%d] = B[%d] / A[%d][%d]\n", n, n, n, n);
//        printf("X[%d] = %f / %f = %f\n", n, B[n], A[n][n], B[n] / A[n][n]);
//        printf("here: A[%d][%d]\n", n, n);

        X[colsA - 1] = B[colsA - 1] / A[colsA - 1][colsA - 1];
        for (int i = colsA - 2; i >= 0; --i) { //we've already dealt with i = colsA - 1
            double sum = 0;
            for (int j = i + 1; j < colsA; ++j) {
                printf("here: A[%d][%d]\n", i, j);
                sum += A[i][j] * X[j];
            }
            printf("here: A[%d][%d]\n", i, i);
            X[i] = (B[i] - sum) / A[i][i];
        }
        SHOWME
        printf("A * X = B has one solution\n");
        printf("X = \n");
        showCol(X, colsA);
        free(X);
    } else if (rowsA - nilRows < colsA && goDeep) {// could probably just be phrased as "else"
        // deal with infinite solutions (with parameters)

        //TODO deal with non diagonal echelonned matrices
        /*
         * r r r r | r
         * 0 r r r | r
         * 0 0 0 r | r (!)
         * 0 0 0 0 | 0
         */

        int params = colsA - (rowsA - nilRows);
        int rowsX = colsA; // as we know
        int colsX = params + 1;
        double **sols = mkMat(colsA, rowsA);

        /*
         * the resulting eq sys will have 1 row and 1 col per parameter + 1 row and 1 col for all the solved unknowns
         * for a mat(3, 5) with no nil rowsA, for instance, we would have 2 params, and we might see something like:
         *
         *  j=0      j=1       j=2 (params + 1)
         *
         *  +5/2  -(39/2)α  -(9/2)ß   i=0
         *    +1    -(14)α    -(2)ß   i=1
         * -3/2   +(15/2)α  +(3/2)ß   i=2
         *               α            i=3
         *                        ß   i=4 (colsA - 1)
         *
         * where we can ignore the last 2 lines (not storing a string in a matrix for doubles), or store it like:
         *
         *  j=0    j=1   j=2  (params + 1)
         *
         *  +5/2 -39/2  -9/2  i=0
         *    +1   -14    -2  i=1
         * -3/2  +15/2  +3/2  i=2
         *    0      1     0  i=3
         *    0      0     1  i=4 (colsA - 1)
         */
        for (int i = rowsX - 1; i >= params; --i) {
            // once for each parameter. sols will grow both ways when params grows, so this should work
            sols[i][i - params] = 1.0;
        }
        sols[colsX - 1][0] = B[colsX - 1] / A[colsX - 1][colsX - 1];
        for (int j = 1; j < colsX; ++j) {
            sols[colsX - 1][j] = -(A[colsX - 1][colsX - 1 + j] / A[colsX - 1][colsX - 1]);
        }// express one variable in terms of all the parameters, use that result to express the other variables

        //TODO pick it back up using screenshot and the notes on the sum
        for (int i = colsX - 2; i >= 0; --i) {
            for (int j_a = i; j_a < colsA; ++j_a) {
                for (int j_x = 0; j_x < colsX; ++j_x) {
                    if (j_x == 0) {
//                        sols[i][j_x] = B[i] / A[i][i] + (A[i][i + 1] * sols[i + 1][j_x]);
                    } else {
//                        sols[i][j_x] =
                    }
                }
            }
        }

        SHOWME
        printf("A * X = B has an infinite amount of solutions\n");
        double **solsT = transverseMat(sols, rowsX, colsX);
        for (int i = 0; i < colsX; ++i) {
            showCol(solsT[i], rowsX);// we show each row of the transverse of sols (and we show it as a column)
            //because it's more expensive to take out a column from a 2d array in C
            //... it's better to do the work once with transverseMat, and then use rows
            // NEVER MIND, it seems to be the same O(n). But it's easier to wrap one's head around this version, isn't it?
            if (i < colsX - 1) {
                printf(" + x%d * \n", i + 1 + colsX); // colsX is size (params + 1 (for real numbers))
            }
            printf("\n");
        }
        free(sols);
    } else if (!goDeep) {
        char input = 'n';
        printf("A * X = B has an infinite amount of solutions\n"
               "This could take a long time to compute. Try anyway? (Y/n): ");
        scanf("%c", &input);
        getchar();
        printf("\n");
        if (input == 'Y') {
            solveForX(A, rowsA, colsA, B, X, 1);
        } else {
            printf("OK, moving on...\n");
            return;
        }
    } else {
        printf("we shouldn't be here... no solutions, right?\n");
        SHOWME
        DEBUG
    }
}

// this destructive function changes the matrices as a side-effect
void gaussElim(double **A, int rowsA, int colsA, double *B, double *X, int goDeep) {

    if (A == NULL || rowsA < 2 || colsA < 2 || B == NULL || X == NULL) {
        if (rowsA < 2 || colsA < 2) {
            printf("we will not deal with a matA(m, n) if m or n is below 2\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }
    //TODO implement below
    //If all bk  are zero, the set of equations is called a homogeneous system, and we have at least one solution: xk  = 0 for all k.
    SHOWME
    double factor;
    for (int i = 0; i < rowsA; ++i) {
        printf("__i = %d\n", i);
        for (int j = 0; j <= i && j < colsA; ++j) {
            printf("__j = %d\n", j);
            if (fabs(A[i][j]) < EPSILON && i == j) {
                for (int k = i + 1; k < rowsA; ++k) {
                    printf("1_k = %d\n", k);
//                    printf("%+.1000f < %+.1000f?\n", fabs(A[k][j]), EPSILON);
                    if (fabs(A[k][j]) > EPSILON && i != k) {
                        printf("L%d <-> L%d\n", i + 1, k + 1);
                        rowSwap(A, B, i, k, colsA);
                        i--; // we want to make sure to come back to where we found the A(i, j) == 0 && i == j, now that it's fixed
                        SHOWME
                        break;
                    }
                }
            } else {
                for (int k = i + 1; k < rowsA; ++k) {
                    printf("2_k = %d\n", k);
                    factor = (A[k][j] / A[i][j]);
                    if (fabs(A[k][j]) < EPSILON) {
                        continue;
                    } else {
                        printf("L%d <- L%d - (%+06.1f * L%d)\n", k + 1, k + 1, factor, i + 1);
                        rowTransform(A[k], colsA, A[i], factor);
                        B[k] -= factor * B[i];
                        SHOWME
                    }
                }
            }
        }
    }
    printf("solving...\n");
    solveForX(A, rowsA, colsA, B, X, goDeep);
}


#endif //Y2_NUM_ALGO_LIN_ALG_H
