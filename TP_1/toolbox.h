//
// Created by draia on 26/09/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

double **mkDoubleSquareMAt(int n) {

    double **mat = malloc(sizeof(double *) * n);

    if (mat == NULL) {
        MALLOC_FAIL
    }

    int hasFailed = 0;

    for (int i = 0; i < n; ++i) {

        mat[i] = malloc(n * sizeof(double));

        if (mat[i] == NULL) {
            hasFailed = 1;
        }
    }

    if (hasFailed) {
        for (int i = 0; i < n; ++i) {
            if(mat[i] != NULL) {
                free(mat[i]);
            }
        }
        free(mat);
        MALLOC_FAIL
    }
    return mat;
}

int **mkIntSquareMAt(int n) {

    int **mat = malloc(sizeof(int *) * n);

    if (mat == NULL) {
        MALLOC_FAIL
    }

    int hasFailed = 0;

    for (int i = 0; i < n; ++i) {

        mat[i] = malloc(n * sizeof(int));

        if (mat[i] == NULL) {
            hasFailed = 1;
        }
    }

    if (hasFailed) {
        for (int i = 0; i < n; ++i) {
            if(mat[i] != NULL) {
                free(mat[i]);
            }
        }
        free(mat);
        MALLOC_FAIL
    }
    return mat;
}

//TODO free
//TODO print

#endif //Y2_NUM_ALGO_TOOLBOX_H
