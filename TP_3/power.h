//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_POWER_H
#define Y2_NUM_ALGO_POWER_H

int powReg(coord *coords, int n, double *a, double *b);

int powReg(coord *coords, int n, double *a, double *b) {
    coord *coords_ln = copyCoords(coords, n);
    for (int i = 0; i < n; i++) {
        coords_ln[i].x = log(coords[i].x);
        coords_ln[i].y = log(coords[i].y);
    }
    int res = linReg(coords_ln, n, a, b);
    *b = exp(*b);
    return res;
}


#endif //Y2_NUM_ALGO_POWER_H
