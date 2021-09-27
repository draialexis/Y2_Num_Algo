void fillMatB(int *matB, int n) {
    for (int i = 0; i < n; ++i) {
        *(matB + i) = rand() % 20;
    }
}

void printMatB(int *matB, int n) {
    for (int i = 0; i < n; i++) {
        printf("%+04d\n", *(matB + i));
    }
}

void printIntMatrix(int **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%+06d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void printDoubleMatrix(double **matrix, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%+.2f ", *(*(matrix + i) + j));
        }
        printf("\n");
    }
}

void fillBord(int **bord, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int * crnt = *(bord + i) + j;
            if (i == j) {
                *crnt = 1;
            } else if (i + 1 == n) {
                *crnt = (int) pow(2, (n - (j + 1)));
            } else if (j + 1 == n) {
                *crnt = (int) pow(2, (n - (i + 1)));
            } else {
                *crnt = 0;
            }
        }
    }
}

void fillDingDong(double **dingDong, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            *(*(dingDong + i) + j) = (double) 1 / (2 * (n - (i + 1) - (j + 1) + 1.5));
        }
    }
}

