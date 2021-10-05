//
// Created by draia on 26/09/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

double **mkMat(int rows, int cols);

double *mkColVec(int rows);

void showMat(double **mat, int rows, int cols);

void showCol(double *mat, int size);

void showRow(double *mat, int size);

void showEqSys(double **A, int rows, int cols, double *B);

void freeMat(double **mat, int rows, int cols);

void rowMult(double *arr, int size, double factor);

void rowTransform(double *arr, int size, double *sub, double factor);

void rowSwap(double **matA, double *matB, int i, int k, int cols);

double **transverseMat(double **mat, int rowsM, int colsM);

struct MaxValMaxPos maxInCol(double *col, int n);

double **mkMat(int rows, int cols) {
    if (rows > 0 && cols > 0) {
        double **mat = (double **) malloc(sizeof(double *) * rows);
        if (mat == NULL) {
            MALLOC_FAIL
        }
        int hasFailed = 0;
        for (int i = 0; i < rows; ++i) {
            mat[i] = (double *) malloc(sizeof(double) * cols);
            if (mat[i] == NULL) {
                hasFailed = 1;
            }
        }
        if (hasFailed) {
            for (int i = 0; i < rows; ++i) {
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
            printf("|%+6.2f|\n", mat[i]);
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
        for (int j = 0; j < size; ++j) {
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
        double *tmpArrA = mkColVec(cols);
        fillMatB_rdm(tmpArrA, cols);
        tmpArrA = matA[i];
        matA[i] = matA[k];
        matA[k] = tmpArrA;
//    free(tmpArrA);
// that line caused a nasty bug... so, it's already being freed at end of the function because it's on the heap???
        double tmp;
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
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                res[i][j] = mat[j][i];
            }
        }
        return res;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
