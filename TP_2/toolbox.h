//
// Created by draia on 16/10/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

typedef struct Coordinate {
    double x;
    double y;
} coord;

double **mkMat(int rows, int cols);

double **mk_X_Y(int rows);

double *mkColVec(int rows);

coord *mkCoordArr(int points);

double **copyMat(double **mat, int rows, int cols);

double *copyColVec(double *mat, int rows);

void showMat(double **mat, int rows, int cols);

void showCol(double *mat, int size);

void showCoordArr(coord *arr, int points);

void showRow(double *mat, int size);

void freeMat(double **mat, int rows, int cols);

double minDouble(double a, double b);

void cleanCheck(char input);

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

coord *mkCoordArr(int points) {
    if (points > 0) {
        coord *mat = (coord *) malloc(sizeof(coord) * points);
        if (mat == NULL) {
            MALLOC_FAIL
        }
        return mat;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fill_X_Y(coord *arr, int points) {
    if (arr != NULL && points > 0) {
        char str[30];
        char *endPtr;
        coord input;
        for (int i = 0; i < points; i++) {
            printf("x_%d <- ", i + 1);
            scanf("%s", str);
            input.x = strtod(str, &endPtr);
            cleanCheck(*endPtr);
            printf("f(x_%d) <- ", i + 1);
            scanf("%s", str);
            input.y = strtod(str, &endPtr);
            cleanCheck(*endPtr);
            arr[i] = input;
        }
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
                printf("%+06.10f ", *(*(mat + i) + j));
            }
            i == rows - 1 ? printf("]\n") : printf("|\n");
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void showDiffMat(double **mat, int n) {
    if (n > 0 && mat != NULL) {
        printf("[");
        for (int i = 0; i < n; i++) {
            if (i != 0) printf("|");
            for (int j = 0; j < n - i; j++) {
                printf("%+06.5f ", *(*(mat + i) + j));
            }
            i == n - 1 ? printf("]\n") : printf("|\n");
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void showCol(double *mat, int size) {
    if (size > 0 && mat != NULL) {
        for (int i = 0; i < size; i++) {
            printf("|%+8.10f|\n", mat[i]);
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void showCoordArr(coord *arr, int points) {
    if (points > 0 && arr != NULL) {
        for (int i = 0; i < points; i++) {
            printf("|%+010.5f, %+010.5f|\n", arr[i].x, arr[i].y);
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void showPoly(double *poly, int n_coeffs, coord *coords) {
    printf("unsimplified polynomial equation:\n");

    for (int i = 0; i < n_coeffs; i++) {
        if (poly[i != 0]) {
            if (i == 0) {
                printf("%+04.2f", poly[i]);
            } else {
                printf("%+04.2f * ", poly[i]);
                for (int k = 0; k < i; ++k) {
                    if (fabs(coords[k].x) < EPSILON) {
                        printf("(x)");
                    } else {
                        printf("(x - (%+04.2f))", coords[k].x);
                    }
                    if (k < i - 1) {
                        printf(" * ");
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n\n");
}


void showRow(double *mat, int size) {
    if (size > 0 && mat != NULL) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%+02.5f ", mat[i]);
        }
        printf("]\n\n");
    } else {
        EMPTY_OR_NULL
    }
}
void showBs(double *diffs, int size, double y_0) {
    if (size > 0 && diffs != NULL) {
        printf("[%+02.5f ", y_0);
        for (int i = 0; i < size; i++) {
            printf("%+02.5f ", diffs[i]);
        }
        printf("]\n\n");
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


void shuffleMat(double **mat, int rows, int cols) {
    double tmp;
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

double minDouble(double a, double b) {
    if (a >= b) {
        return b;
    } else {
        return a;
    }
}

void cleanCheck(char input) {
    getchar();
    if (input == 'q') exit(0);
    fflush(stdin);
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
