//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

typedef struct Coordinate {
    double x;
    double y;
} coord;

coord *mkCoordArr(int n);

void fill_X_Y(coord *arr, int n);

void cleanCheck(char input);

void showCoordArr(coord *arr, int n);

void askPy(const coord *coords, double a, double b, int n, char mthd);

void writePy(const coord *coords, double a, double b, int n, char mthd);

void writeToFile(char *myStr, char *fname);

void checkFopen(FILE *fileName);

coord *mkCoordArr(int n) {
    if (n > 0) {
        coord *arr = NULL;
        arr = (coord *) malloc(sizeof(coord) * n);
        if (arr == NULL) {
            MALLOC_FAIL
        }
        return arr;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

void fill_X_Y(coord *arr, int n) {
    if (arr != NULL && n > 0) {
        char str[20];
        char *endPtr;
        coord input;
        for (int i = 0; i < n; i++) {
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

void cleanCheck(char input) {
    getchar();
    if (input == 'q') exit(0);
    fflush(stdin);
}

void showCoordArr(coord *arr, int n) {
    printf("coordonnees (x, y):\n");
    if (n > 0 && arr != NULL) {
        for (int i = 0; i < n; i++) {
            printf("|%+010.5f, %+010.5f|\n", arr[i].x, arr[i].y);
        }
        printf("\n");
    } else {
        EMPTY_OR_NULL
    }
}

void askPy(const coord *coords, double a, double b, int n, char mthd) {
    char genPy;
    printf("\ngenerer un script .py?"
           "\n* 'o' : oui"
           "\n* 'n' : non"
           "\n>");
    genPy = (char) getchar();
    cleanCheck(genPy);
    if (genPy == 'o') {
        writePy(coords, a, b, n, mthd);
    }
}

void writePy(const coord *coords, double a, double b, int n, char mthd) {
    int bfr = 32;
    char *fname;
    char *eqStr = (char *) malloc(sizeof(char) * bfr);
    sprintf(eqStr, "%c", '\0');

    if (mthd == 'r') {
        fname = "lin.py";
        sprintf(eqStr, "%.15f * x %+.15f", a, b);
    } else if (mthd == 'e') {
        fname = "exp.py";
        sprintf(eqStr, "np.exp(%.15f * x %+.15f)", a, b);
    } else if (mthd == 'p') {
        fname = "pow.py";
        sprintf(eqStr, "pow(x, %.15f) * %.15f)", a, b);
    }

    char *xStr = (char *) malloc(sizeof(char) * n * bfr);
    char *yStr = (char *) malloc(sizeof(char) * n * bfr);
    char *xPart = (char *) malloc(sizeof(char) * bfr);
    char *yPart = (char *) malloc(sizeof(char) * bfr);
    sprintf(xStr, "%c", '\0');
    sprintf(yStr, "%c", '\0');
    sprintf(xPart, "%c", '\0');
    sprintf(yPart, "%c", '\0');
    for (int i = 0; i < n; i++) {
        sprintf(xPart, "%.15f, ", coords[i].x);
        sprintf(yPart, "%.15f, ", coords[i].y);
        strncat(xStr, xPart, bfr);
        strncat(yStr, yPart, bfr);
    }
    char *pyStr = (char *) malloc(sizeof(char) * BUFFER_SIZE);
    sprintf(pyStr,
            "import numpy as np\n"
            "import matplotlib.pyplot as plt\n"
            "def curve_eq(x):\n"
            "    return %s\n"
            "x = [%s]\n"
            "y = [%s]\n"
            "new_x = []\n"
            "new_y = []\n"
            "lo = int(min(x) - 2.0)\n"
            "hi = int(max(x) + 2.0) + 1\n"
            "for i in np.linspace(lo, hi, ((hi - lo) * 10)):\n"
            "    new_x.append(i)\n"
            "    new_y.append(curve_eq(i))\n"
            "plt.axhline(0, color='grey')\n"
            "plt.axvline(0, color='grey')\n"
            "plt.plot(new_x, new_y, color='g', label='regression')\n"
            "plt.scatter(x, y, 50, color='b', label='donnees')\n"
            "plt.xlabel('x')\n"
            "plt.ylabel('y')\n"
            "plt.title('y = %s')\n"
            "plt.legend()\n"
            "plt.show()\n",
            eqStr, xStr, yStr, eqStr);
    writeToFile(pyStr, fname);
}

void writeToFile(char *myStr, char *fname) {
    FILE *fp = fopen(fname, "w");
    checkFopen(fp);
    fputs(myStr, fp);
    fclose(fp);
}

void checkFopen(FILE *fileName) {
    if (fileName == NULL) {
        EMPTY_OR_NULL
        perror("error while opening file");
        FAIL_OUT
    }
}

coord *copyCoords(coord *arr, int n) {
    coord *res = mkCoordArr(n);
    if (arr != NULL && res != NULL && n > 0) {
        for (int i = 0; i < n; i++) {
            res[i] = arr[i];
        }
        return res;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
