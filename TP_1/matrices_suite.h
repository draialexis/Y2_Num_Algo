#ifndef Y2_NUM_ALGO_MATRICES_SUITE_H
#define Y2_NUM_ALGO_MATRICES_SUITE_H

#include <math.h>

void fillMatB_rdm(double *mat, int size);

void fillMatA_rdm(double **mat, int rows, int cols);

void fillMatA_userInput(double **mat, int rows, int cols);

void fillMatB_userInput(double *mat, int rows);

void fillSparseMat(double **mat, int rows, int cols);

void fillBord(double **bord, int size);

void fillDingDong(double **dingDong, int size);

void fillMat_EZ(double **mat);

void fillMatB_EZ(double *mat);

void doB(double *matB, int size, char choice);

void doA(double **matA, int rows, int cols, char choice, int isSquare);

void fillMatB_rdm(double *mat, int size) {
    if (size > 0) {
        for (int i = 0; i < size; i++) {
            mat[i] = (rand() % 101) + 50;
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatA_rdm(double **mat, int rows, int cols) {
    if (mat != NULL && rows > 0 && cols > 0) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat[i][j] = (rand() % 101) + 50;
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatA_userInput(double **mat, int rows, int cols) {
    if (mat != NULL && rows > 0 && cols > 0) {
        double input = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("A(%d, %d) <- ", i + 1, j + 1);
                scanf("%lf", &input);
                getchar();
                fflush(stdin);
                mat[i][j] = input;
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatB_userInput(double *mat, int rows) {
    if (mat != NULL && rows > 0) {
        double input = 0;
        for (int i = 0; i < rows; i++) {
            printf("B(%d) <- ", i + 1);
            scanf("%lf", &input);
            getchar();
            fflush(stdin);
            mat[i] = input;
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillSparseMat(double **mat, int rows, int cols) {
    if (mat != NULL && rows > 0 && cols > 0) {
        double area = rows * cols;
        double zeros = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (zeros / area > 0.7) {
                    mat[i][j] = (double) (rand() % 9) + 1;
                } else {
                    mat[i][j] = 0.0;
                    zeros++;
                }
            }
        }
        shuffleMat(mat, rows, cols);
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillBord(double **bord, int size) {
    if (bord != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    bord[i][j] = 1;
                } else if (i + 1 == size) {
                    bord[i][j] = (int) pow(2, (size - (j + 1)));
                } else if (j + 1 == size) {
                    bord[i][j] = (int) pow(2, (size - (i + 1)));
                } else {
                    bord[i][j] = 0;
                }
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillDingDong(double **dingDong, int size) {
    if (dingDong != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                dingDong[i][j] = (double) 1 / (2 * (size - (i + 1) - (j + 1) + 1.5));
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMat_EZ(double **mat) {
    if (mat != NULL) {
        mat[0][0] = 2.0;
        mat[0][1] = 1.0;
        mat[1][0] = 5.0;
        mat[1][1] = 3.0;
        mat[2][0] = 4.0;
        mat[2][1] = 2.0;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMatB_EZ(double *mat) {
    if (mat != NULL) {
        mat[0] = 11.0;
        mat[1] = 13.0;
        mat[2] = 22.0;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void doB(double *matB, int size, char choice) {
    if (matB != NULL && size > 0) {
        switch (choice) {
            case 'a':
                fillMatB_rdm(matB, size);
                break;
            case 'C':
                fillMatB_userInput(matB, size);
                break;
            default:
                printf("votre choix de type de matrice B n'a pas ete compris. mode aleatoire.\n");
                fillMatB_rdm(matB, size);
                break;
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void doA(double **matA, int rows, int cols, char choice, int isSquare) {
    if (matA == NULL || rows <= 0 || cols <= 0) {
        EMPTY_OR_NULL
        FAIL_OUT
    }
    if (isSquare) {
        switch (choice) {
            case 'b':
                fillBord(matA, rows);
                break;
            case 'd':
                fillDingDong(matA, rows);
                break;
            case 'a' :
                fillMatA_rdm(matA, rows, cols);
                break;
            case 'c' :
                fillSparseMat(matA, rows, cols);
                break;
            case 'C' :
                fillMatA_userInput(matA, rows, cols);
                break;
            default:
                printf("votre choix de type de matrice A n'a pas ete compris. mode aleatoire.\n");
                fillMatA_rdm(matA, rows, cols);
                break;
        }
        //TODO Etc.
    } else {
        switch (choice) {
            case 'a' :
                fillMatA_rdm(matA, rows, cols);
                break;
            case 'c' :
                fillSparseMat(matA, rows, cols);
                break;
            case 'C' :
                fillMatA_userInput(matA, rows, cols);
                break;
            default:
                printf("votre choix de type de matrice A n'a pas ete compris. mode aleatoire.\n");
                fillMatA_rdm(matA, rows, cols);
                break;
        }
    }
}

#endif //Y2_NUM_ALGO_MATRICES_SUITE_H
