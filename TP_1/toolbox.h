//
// Created by draia on 26/09/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

double **mkDoubleMat(int cols, int rows) {

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

int **mkIntMat(int rows, int cols) {

    int **mat = malloc(sizeof(int *) * rows);

    if (mat == NULL) {
        MALLOC_FAIL
    }

    int hasFailed = 0;

    for (int i = 0; i < rows; ++i) {

        mat[i] = malloc(sizeof(int) * cols);

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

void freeMat_i(int **mat, int rows, int cols) {
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

void freeMat_d(double **mat, int rows, int cols) {
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

void showMat_d(double **mat, int rows, int cols) {
    if (rows > 0 && cols > 0 && mat != NULL) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%+.3f ", *(*(mat + i) + j));
            }
            printf("\n");
        }
    } else {
        EMPTY_OR_NULL
    }
}

void showMat_i(int **mat, int rows, int cols) {
    if (rows > 0 && cols > 0 && mat != NULL) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%+06d ", *(*(mat + i) + j));
            }
            printf("\n");
        }
    } else {
        EMPTY_OR_NULL
    }
}

void showColVect(const int *matB, int n) {
    for (int i = 0; i < n; i++) {
        printf("%+06d\n", *(matB + i));
    }
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
