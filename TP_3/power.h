//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_POWER_H
#define Y2_NUM_ALGO_POWER_H

int powReg(coord *coords, int n, double *a, double *b, int *o);

int powReg(coord *coords, int n, double *a, double *b, int *o) {
    coord *coords_ln = copyCoords(coords, n);
    for (int i = 0; i < n; i++) {
        if (fabs(coords[i].x) < EPSILON || fabs(coords[i].y) < EPSILON) {
            printf("tried to take ln(x) where x <= 0... exiting program\n");
            return 0;
        }
        coords_ln[i].x = log(coords[i].x);
        coords_ln[i].y = log(coords[i].y);////<< 2n
        *o += 2;
    }

    int res = linReg(coords_ln, n, a, b, o);
    *b = exp(*b);////<< 1
    *o += 1;
    return res; //1 if it worked, -1 else
}


#endif //Y2_NUM_ALGO_POWER_H
