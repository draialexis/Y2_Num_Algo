//
// Created by draia on 26/09/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

double **mkMat(int cols, int rows) {

    double **mat = malloc(sizeof(double *) * rows);

    if (mat == NULL) {
        MALLOC_FAIL
    }

    int hasFailed = 0;

    for (int i = 0; i < rows; ++i) {

        mat[i] = malloc(sizeof(double) * cols);

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
}

double *mkColVec(int rows) {
    double *mat = malloc(sizeof(double) * rows);
    if (mat == NULL) {
        MALLOC_FAIL
    }
    return mat;
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
    }
}

void showMat(double **mat, int rows, int cols) {
    if (rows > 0 && cols > 0 && mat != NULL) {
        printf("[");
        for (int i = 0; i < rows; i++) {
            if (i != 0) printf("|");
            for (int j = 0; j < cols; j++) {
                printf("%+06.3f ", *(*(mat + i) + j));
            }
            i == rows - 1 ? printf("]\n") : printf("|\n");
        }
    } else {
        EMPTY_OR_NULL
    }
}


void showCol(const double *mat, int n, int isX) {
    if(isX){
        for (int i = 0; i < n; ++i) {
            printf("|?|\n");
        }
    } else {
        for (int i = 0; i < n; i++) {
            printf("|%+06.3f|\n", *(mat + i));
        }
    }
    printf("\n");
}

void showRow(const double *mat, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%+06.3f ", *(mat + i));
    }
    printf("]\n");
}

void showEqSys(double **A, int rows, int cols, double *B) {
    if (rows > 0 && cols > 0 && A != NULL && B != NULL) {
        printf("[");
        for (int i = 0; i < rows; i++) {
            if (i != 0) printf("|");
            for (int j = 0; j < cols; j++) {
                printf("%+06.3f ", A[i][j]);
            }
            printf("| %+06.3f", B[i]);
            i == rows - 1 ? printf("]\n") : printf("|\n");

        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void rowMult(double *arr, int size, double factor) {
    for (int k = 0; k < size; ++k) {
        arr[k] *= factor;
    }
}

void rowSub(double *arr, int size, const double *sub, const double factor) {
    for (int k = 0; k < size; ++k) {
        arr[k] = arr[k] - (factor * sub[k]);
    }
}

void rowSwap(double **matA, double *matB, int i, int k, int cols) {
    double *tmpArrA = mkColVec(cols);
    double tmp;
    tmpArrA = matA[i];
    matA[i] = matA[k];
    matA[k] = tmpArrA;
    free(tmpArrA);
    tmp = matB[i];
    matB[i] = matB[k];
    matB[k] = tmp;
}


#endif //Y2_NUM_ALGO_TOOLBOX_H
