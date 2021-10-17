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

double *mkColVec(int rows);

coord *mkCoordArr(int points);

void fill_X_Y(coord *arr, int points);

void degradeCoordArr(coord *arr, int rows);

void showDiffMat(double **mat, int n);

void showCoordArr(coord *arr, int points);

char *printPoly(double *poly, int n_coeffs, const coord *coords);

void showRow(double *mat, int size);

void cleanCheck(char input);

void checkFopen(FILE *fileName);

void writeToFile(char *myStr, char *fname);

void writePy(const coord *coords, char *eqStr, int points, char *mthd);

void askPy(const coord *coords, char *eqStr, int points, char *mthd);

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
        double *vec = malloc(sizeof(double) * rows);
        if (vec == NULL) {
            MALLOC_FAIL
        }
        return vec;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

coord *mkCoordArr(int points) {
    if (points > 0) {
        coord *arr = (coord *) malloc(sizeof(coord) * points);
        if (arr == NULL) {
            MALLOC_FAIL
        }
        return arr;
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

void degradeCoordArr(coord *arr, int rows) {
    if (arr != NULL && rows > 0) {
        int i = rand() % rows;
        arr[i].y += (1.0/70);
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
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

void showCoordArr(coord *arr, int points) {
    printf("coordonnees (x, y):\n");
    if (points > 0 && arr != NULL) {
        for (int i = 0; i < points; i++) {
            printf("|%+010.5f, %+010.5f|\n", arr[i].x, arr[i].y);
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

char *printPoly(double *poly, int n_coeffs, const coord *coords) {
    int bfr = 256;
    char *res = (char *) malloc(sizeof(char) * n_coeffs * bfr);
    sprintf(res, "%c", '\0');
    char *tmp = (char *) malloc(sizeof(char) * bfr);
    for (int i = 0; i < n_coeffs; i++) {
        if (fabs(poly[i]) > EPSILON) {
            if (i == 0) {
                sprintf(tmp, "%+.50f", poly[i]);
                strncat(res, tmp, bfr);
            } else {
                sprintf(tmp, "%+.50f*", poly[i]);
                strncat(res, tmp, bfr);
                for (int k = 0; k < i; k++) {
                    if (fabs(coords[k].x) < EPSILON) {
                        sprintf(tmp, "(x)");
                        strncat(res, tmp, bfr);
                    } else {
                        sprintf(tmp, "(x-(%.5f))", coords[k].x);
                        strncat(res, tmp, bfr);
                    }
                    if (k < i - 1) {
                        sprintf(tmp, "*");
                        strncat(res, tmp, bfr);
                    }
                }
            }
        }
    }
    return res;
}

void showRow(double *mat, int size) {
    if (size > 0 && mat != NULL) {
        printf("[");
        for (int i = 0; i < size; i++) {
            printf("%+10.5f ", mat[i]);
        }
        printf("]\n\n");
    } else {
        EMPTY_OR_NULL
    }
}

void cleanCheck(char input) {
    getchar();
    if (input == 'q') exit(0);
    fflush(stdin);
}

void checkFopen(FILE *fileName) {
    if (fileName == NULL) {
        EMPTY_OR_NULL
        perror("error while opening file");
        FAIL_OUT
    }
}

void writeToFile(char *myStr, char *fname) {
    FILE *fp = fopen(fname, "w");
    checkFopen(fp);
    fputs(myStr, fp);
    fclose(fp);
}

void writePy(const coord *coords, char *eqStr, int points, char *mthd) {
    int bfr = 256;//128 chars per coordinate were not enough for lagrange
    char *fname;
    char *clr;
    if (strcmp(mthd, "Lagrange") == 0) {
        fname = "lagr_poly.py";
        clr = "green";
    } else {
        fname = "newt_poly.py";
        clr = "cyan";
    }

    char *xStr = (char *) malloc(sizeof(char) * points * bfr);
    char *yStr = (char *) malloc(sizeof(char) * points * bfr);
    char *xPart = (char *) malloc(sizeof(char) * bfr);
    char *yPart = (char *) malloc(sizeof(char) * bfr);
    sprintf(xStr, "%c", '\0');
    sprintf(yStr, "%c", '\0');
    sprintf(xPart, "%c", '\0');
    sprintf(yPart, "%c", '\0');
    for (int i = 0; i < points; i++) {
        sprintf(xPart, "%.10f, ", coords[i].x);
        sprintf(yPart, "%.10f, "
                       "", coords[i].y);
        strncat(xStr, xPart, bfr);
        strncat(yStr, yPart, bfr);
    }
    char *pyStr = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(pyStr,
            "import numpy as np\n"
            "import matplotlib.pyplot as plt\n"
            "import sympy as sym\n"
            "def formula(x):\n"
            "    return sym.expand(%s)\n"
            "x_ = sym.symbols('x')\n"
            "x_t = [%s]\n"
            "y_d = [%s]\n"
            "new_x_t = []\n"
            "new_y_d = []\n"
            "lo = int(min(x_t) - 2.0)\n"
            "hi = int(max(x_t) + 2.0) + 1\n"
            "for i in range(lo, hi):\n"
            "    new_x_t.append(i)\n"
            "    new_y_d.append(formula(i))\n"
            "plt.axhline(0, color='grey')\n"
            "plt.axvline(0, color='grey')\n"
            "plt.plot(new_x_t, new_y_d, color='%s', label='%s')\n"
            "plt.scatter(x_t, y_d, 50, color='blue', label='Given datapoints')\n"
            "plt.xlabel('x')\n"
            "plt.ylabel('P(x)')\n"
            "plt.title(formula(x_))\n"
            "plt.legend()\n"
            "plt.show()\n",
            eqStr, xStr, yStr, clr, mthd);
    writeToFile(pyStr, fname);
}

void askPy(const coord *coords, char *eqStr, int points, char *mthd) {
    char genPy;
    printf("\ngenerer un script .py?"
           "\n* 'o' : oui"
           "\n* 'n' : non"
           "\n>");
    genPy = (char) getchar();
    cleanCheck(genPy);
    if (genPy == 'o') {
        writePy(coords, eqStr, points, mthd);
    }
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
