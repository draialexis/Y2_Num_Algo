//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_EXPONENTIAL_H
#define Y2_NUM_ALGO_EXPONENTIAL_H

int expReg(coord *coords, int n, double *a, double *b);

int expReg(coord *coords, int n, double *a, double *b) {
    coord *coords_ln_y = copyCoords(coords, n);
    for (int i = 0; i < n; i++) {
        coords_ln_y[i].y = log(coords[i].y);
    }
    linReg(coords_ln_y, n, a, b);
    return 1;
}

#endif //Y2_NUM_ALGO_EXPONENTIAL_H
