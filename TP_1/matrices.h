int i, j;

void fillMatB(int * matB, int n){
    for (i = 0; i < n; ++i) {
        *(matB + i) = rand() % 20;
    }
}

void printMatB(const int * matB, int n){
    for (i = 0; i < n; i++) {
        printf("%+04d\n", *(matB + i));
    }
}

void printIntMatrix(const int * matrix, int n){
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%+04d ", *(matrix + (i * n) + j));
        }
        printf("\n");
    }
}

void printDoubleMatrix(const double * matrix, int n){
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%+.2f ", *(matrix + (i * n) + j));
        }
        printf("\n");
    }
}

void fillBord(int * bord, int n){
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            if (i == j) {
                *(bord + (i * n) + j) = 1;
                /*
                * address of a 'box': goes from address of first value (original pointer), and since
                * the values are stored one after the other (in a line, more than in a square...),
                * we add to it the number of rows that we've gone through, times the total number
                * of columns, plus the number of columns that we've gone through.
                * try it with an example (use i =/= j for helpful results)
                */
            } else if (i + 1 == n) {
                *(bord + (i * n) + j) = (int)pow(2, (n - (j + 1)));
            } else if (j + 1== n) {
                *(bord + (i * n) + j) = (int)pow(2, (n - (i + 1)));
            } else {
                *(bord + (i * n) + j) = 0;
            }
        }
    }
}

void fillDingDong(double * dingDong, int n){
    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            *(dingDong + (i * n) + j) = (double)1 / (2 * (n - (i + 1) - (j + 1) + 1.5));
        }
    }
}

