//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_EXPONENTIAL_H
#define Y2_NUM_ALGO_EXPONENTIAL_H

int expReg(coord *coords, int n, double *a, double *b, int *o);

int expReg(coord *coords, int n, double *a, double *b, int *o) {
    if (coords == NULL || n < 2) {
        EMPTY_OR_NULL
        FAIL_OUT
    }
    coord *coords_ln_y = copyCoords(coords, n);
    for (int i = 0; i < n; i++) {
        if (fabs(coords[i].y) < EPSILON) {
            printf("tried to take ln(x) where x <= 0... exiting program\n");
            FAIL_OUT
        }
        coords_ln_y[i].y = log(coords[i].y);
        *o += 1; ////<< n
    }

    return linReg(coords_ln_y, n, a, b, o); //1 if it worked, -1 else
    ////<< 9n + 5
}

#endif //Y2_NUM_ALGO_EXPONENTIAL_H
