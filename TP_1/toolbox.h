//
// Created by draia on 26/09/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

double **mkDoubleSquareMat(int n) {

    double **mat = malloc(sizeof(double *) * n);

    if (mat == NULL) {
        MALLOC_FAIL
    }
    for (int i = 0; i < n; ++i) {

        mat[i] = malloc(n * sizeof(double));

        if (mat[i] == NULL) {
            MALLOC_FAIL
        }
    }
    return mat;
}

int **mkIntSquareMAt(int n) {

    int **mat = malloc(sizeof(int *) * n);

    if (mat == NULL) {
        MALLOC_FAIL
    }
    for (int i = 0; i < n; ++i) {

        mat[i] = malloc(n * sizeof(int));

        if (mat[i] == NULL) {
            MALLOC_FAIL
        }
    }
    return mat;
}

//TODO free
//TODO print

#endif //Y2_NUM_ALGO_TOOLBOX_H
