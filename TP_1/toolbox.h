//
// Created by draia on 26/09/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

double **mkMat(int rows, int cols);

double *mkColVec(int rows);

double **copyMat(double **mat, int rows, int cols);

double *copyColVec(double *mat, int rows);

void degradeMat(double **mat, int rows, int cols);

void showMat(double **mat, int rows, int cols);

void showCol(double *mat, int size);

void showRow(double *mat, int size);

void showEqSys(double **A, int rows, int cols, double *B);

void freeMat(double **mat, int rows, int cols);

void rowMult(double *arr, int size, double factor);

void rowTransform(double *arr, int size, double *sub, double factor);

void rowSwap(double **matA, double *matB, int i, int k, int cols);

double **transverseMat(double **mat, int rowsM, int colsM);

void shuffleMat(double **mat, int rows, int cols);

int isHomSys(double *matB, int size);

int nilRows(double **matA, int rowsA, int colsA, double *matB, int isHomSys);

int isSDD(double **matA, int size);

double **mkMat(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        double **mat = (double **) malloc(sizeof(double *) * rows);
        if (mat == NULL) {
            MALLOC_FAIL
        }
        int hasFailed = 0;
        for (int i = 0; i < rows; i++) {
            mat[i] = (double *) malloc(sizeof(double) * cols);
            if (mat[i] == NULL) {
                hasFailed = 1;
            }
        }
        if (hasFailed) {
            for (int i = 0; i < rows; i++) {
                if (mat[i] != NULL) {
                    free(mat[i]);
                }
            }
            free(mat);
            MALLOC_FAIL
        }
        return mat;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

double *mkColVec(int rows) {
    if (rows > 0) {
        double *mat = malloc(sizeof(double) * rows);
        if (mat == NULL) {
            MALLOC_FAIL
        }
        return mat;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

double **copyMat(double **mat, int rows, int cols) {
    double **res = mkMat(rows, cols);
    if (mat != NULL && res != NULL && rows > 0 && cols > 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res[i][j] = mat[i][j];
            }
        }
        return res;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

double *copyColVec(double *mat, int rows) {
    double *res = mkColVec(rows);
    if (mat != NULL && res != NULL && rows > 0) {
        for (int i = 0; i < rows; i++) {
            res[i] = mat[i];
        }
        return res;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void degradeMat(double **mat, int rows, int cols) {
    if (mat != NULL && rows > 0 && cols > 0) {
        int i = rand() % rows;
        int j = rand() % cols;
        printf("it's happening!\nmat[%d][%d]\n", i, j);
        mat[i][j] = mat[i][j] + 0.1;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void showMat(double **mat, int rows, int cols) {
    if (rows > 0 && cols > 0 && mat != NULL) {
        printf("[");
        for (int i = 0; i < rows; i++) {
            if (i != 0) printf("|");
            for (int j = 0; j < cols; j++) {
                printf("%+06.1f ", *(*(mat + i) + j));
            }
            i == rows - 1 ? printf("]\n") : printf("|\n");
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void showCol(double *mat, int size) {
    if (size > 0 && mat != NULL) {
        for (int i = 0; i < size; i++) {
            printf("|%+8.2f|\n", mat[i]);
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}


void showRow(double *mat, int size) {
    if (size > 0 && mat != NULL) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%+20.20f ", mat[i]);
        }
        printf("]\n\n");
    } else {
        EMPTY_OR_NULL
    }
}

void showEqSys(double **A, int rows, int cols, double *B) {
    if (rows > 0 && cols > 0 && A != NULL && B != NULL) {
        printf("[");
        for (int i = 0; i < rows; i++) {
            if (i != 0) printf("|");
            for (int j = 0; j < cols; j++) {
                printf("%+06.1f ", A[i][j]);
            }
            printf("| %+06.1f", B[i]);
            i == rows - 1 ? printf("]\n") : printf("|\n");

        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void freeMat(double **mat, int rows, int cols) {
    if (rows > 0 && cols > 0 && mat != NULL) {
        for (int i = 0; i < rows; i++) {
            if (mat[i] != NULL) {
                free(mat[i]);
            }
        }
        free(mat);
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void rowTransform(double *arr, int size, double *sub, double factor) {
    if (arr != NULL && size > 0 && sub != NULL && fabs(factor) > EPSILON) {
        for (int j = 0; j < size; j++) {
            arr[j] = arr[j] - (factor * sub[j]);
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void rowSwap(double **matA, double *matB, int i, int k, int cols) {
    if (matA != NULL && matB != NULL && cols > 0) {
        // not checking for non-nullity of arrays inside A... *
        // presumably, the error would have been caught at malloc or in another function
        // no need to multiply complexity of rowSwap by 'rows'
        if (i == k) {
            printf("swapper and swapped appear to be the same\n");
            DEBUG
            FAIL_OUT
        }
        double tmp;
        for (int j = 0; j < cols; j++) {
            tmp = matA[i][j];
            matA[i][j] = matA[k][j];
            matA[k][j] = tmp;
        }
        tmp = matB[i];
        matB[i] = matB[k];
        matB[k] = tmp;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

double **transverseMat(double **mat, int rowsM, int colsM) {
    if (mat != NULL && rowsM > 0 && colsM > 0) {
        int rows = colsM;
        int cols = rowsM;
        double **res = mkMat(rows, cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                res[i][j] = mat[j][i];
            }
        }
        return res;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void shuffleMat(double **mat, int rows, int cols) {
    double tmp = 0.0;
    if (mat != NULL && rows > 0 && cols > 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                tmp = mat[i][j];
                mat[i][j] = mat[rand() % rows][rand() % cols];
                mat[rand() % rows][rand() % cols] = tmp;
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

int isHomSys(double *matB, int size) {
    if (matB != NULL && size > 0) {
        int res = 1;// dealing with homogeneous systems
        for (int i = 0; i < size; i++) {
            if (res && matB[i] > EPSILON) {
                res = 0;
            }
        }
        return res;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

int nilRows(double **matA, int rowsA, int colsA, double *matB, int isHomSys) {
    if (matA != NULL && rowsA > 0 && colsA > 0 && matB != NULL) {
        int isNilRow = 1;
        int nilRows = 0;
        // in case we can ignore the bottom rows (000|0) and focus on the non-empty square subset of the matrix, thanks to Gauss
        // so we would deal with A(p,p), B(p) and X(p). Remember that X has as many rows as A has cols; we can count on that
        for (int i = rowsA - 1; i >= 0; i--) {
            // we want to check for nil rows starting from the bottom: the forward elimination from the gauss function
            // will have placed those at the very bottom
            for (int j = 0; j < colsA; j++) {
                if (isNilRow && fabs(matA[i][j]) > EPSILON) {//any non-0s in the rows?
                    isNilRow = 0;
                }
            }
            if (isNilRow) {
                nilRows++;
                if (!isHomSys && fabs(matB[i]) >
                                 EPSILON) {// deal with absence of solution (an empty i row corresponding to a non-0 B(i))
                    printf("A * X = B n'admet aucune solution : L%d => %+06.1f = 0000.0\n", i + 1, matB[i]);
                    return -1;
                }
            }
        }
        return nilRows;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

int isSDD(double **matA, int size) {
    double diag = 0.0;
    double undiag = 0.0;
    for (int i = 0; i < size; i++) {
        diag = fabs(matA[i][i]);
        for (int j = 0; j < size; j++) {
            if (i != j) {
                undiag += fabs(matA[i][j]);
            }
        }
        if (diag <= undiag) {
            return 0;
        }
    }
    return 1;
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
