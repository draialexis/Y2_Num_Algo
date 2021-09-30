//
// Created by draia on 29/09/2021.
//

#ifndef Y2_NUM_ALGO_LIN_ALG_H
#define Y2_NUM_ALGO_LIN_ALG_H

void rowDiv_i(int *arr, int size, int div) {
    for (int k = 0; k < size; ++k) {
        arr[k] = arr[k] / div;
    }
}

void rowSub_i(int *arr, int size, const int *sub) {
    for (int k = 0; k < size; ++k) {
        arr[k] = arr[k] - sub[k];
    }
}

// this destructive function changes the matrices as a side-effect
void gaussElim_i(int **A, int rows, int cols, int *B) {

    //TODO remember I'm treating mats B and X as 1d-arrays

    if (cols < 2) {
        printf("yeah, right\n");
        DEBUG
        exit(0);
    }

    //TODO remember perform the same operations on the "rows" of matB
    //TODO make sure proportional rows disappear naturally
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j <= cols; ++j) {
            if (A[i][j] != 0) {
                for (int k = i + 1; k < rows; ++k) {
                    if (A[k][j] != 0) {
                        rowDiv_i(A[k], cols, A[i][j]);
                        rowSub_i(A[k], cols, A[i]);
                    }
                }
            } else {
                for (int k = i + 1; k < rows; ++k) {
                    if (A[k][j] != 0) {
                        A[i] = A[k];
                    }
                }
            }
        }
    }
}

//void order_gauss_d() {
//
//}

#endif //Y2_NUM_ALGO_LIN_ALG_H
