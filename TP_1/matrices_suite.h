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

void fillFranc(double **franc, int size);

void fillHilbert_minus(double **hilbert, int size);

void fillHilbert_plus(double **hilbert, int size);

void fillKMS(double **kms, int size);

void fillLehmer(double **lehmer, int size);

void fillLotkin(double **lotkin, int size);

void fillMoler(double **moler, int size);

void fillSDD(double **sdd, int size);

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
        char str[30];
        char *endPtr;
        double input;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("A(%d, %d) <- ", i + 1, j + 1);
                scanf("%s", str);
                input = strtod(str, &endPtr);
                cleanCheck(*endPtr);
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
        char str[30];
        char *endPtr;
        double input;
        for (int i = 0; i < rows; i++) {
            printf("B(%d) <- ", i + 1);
            scanf("%s", str);
            input = strtod(str, &endPtr);
            cleanCheck(*endPtr);
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
                    bord[i][j] = 1.0;
                } else if (i + 1 == size) {
                    bord[i][j] = (double) pow(2, (size - (j + 1)));
                } else if (j + 1 == size) {
                    bord[i][j] = (double) pow(2, (size - (i + 1)));
                } else {
                    bord[i][j] = 0.0;
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

void fillFranc(double **franc, int size) {
    if (franc != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i <= j + 2) {
                    franc[i][j] = 0.0;
                } else {
                    franc[i][j] = minDouble(i + 1, j + 1);
                }
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillHilbert_minus(double **hilbert, int size) {
    if (hilbert != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                hilbert[i][j] = (double) 1 / (i + 1 + j + 1 - 1);
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillHilbert_plus(double **hilbert, int size) {
    if (hilbert != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                hilbert[i][j] = (double) 1 / (i + 1 + j + 1 + 1);
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillKMS(double **KMS, int size) {
    if (KMS != NULL && size > 0) {
        double range = ((1 - EPSILON) - EPSILON); // (max - min)
        double div = RAND_MAX / range;
        double p = EPSILON + (rand() / div);
        printf("parametre 'p' de ]0, 1[ : %.5f\n", p);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                KMS[i][j] = (double) pow(p, abs((i + 1) - (j + 1)));
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillLehmer(double **lehmer, int size) {
    if (lehmer != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i <= j) {
                    lehmer[i][j] = (double) (i + 1) / (j + 1);
                } else {
                    lehmer[i][j] = (double) (j + 1) / (i + 1);
                }
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillLotkin(double **lotkin, int size) {
    if (lotkin != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i + 1 == 1) {
                    lotkin[i][j] = 1.0;
                } else {
                    lotkin[i][j] = (double) 1 / (i + 1 + j + 1 - 1);
                }
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillMoler(double **moler, int size) {
    if (moler != NULL && size > 0) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (i == j) {
                    moler[i][j] = (double) i + 1;
                } else {
                    moler[i][j] = minDouble(i + 1, j + 1) - 2.0;
                }
            }
        }
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fillSDD(double **sdd, int size) {
    if (sdd != NULL && size > 0) {
        double sum;
        double rdm;
        for (int i = 0; i < size; i++) {
            sum = 0.0;
            for (int j = 0; j < size; j++) {
                if (i != j) {
                    rdm = (double) (rand() % 20) + 1;
                    sdd[i][j] = rdm;
                    sum += fabs(rdm);
                }
            }
            sdd[i][i] = sum + rdm;
        }
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
            case 'f':
                fillFranc(matA, rows);
                break;
            case 'h':
                fillHilbert_minus(matA, rows);
                break;
            case 'H':
                fillHilbert_plus(matA, rows);
                break;
            case 'k':
                fillKMS(matA, rows);
                break;
            case 'l':
                fillLehmer(matA, rows);
                break;
            case 'L':
                fillLotkin(matA, rows);
                break;
            case 'm':
                fillMoler(matA, rows);
                break;
            case 's':
                fillSDD(matA, rows);
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
