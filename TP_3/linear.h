//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_LINEAR_H
#define Y2_NUM_ALGO_LINEAR_H

int linReg(coord *coords, int n, double *a, double *b); //TODO add , double *err

int linReg(coord *coords, int n, double *a, double *b) {
    if (coords == NULL && n < 2) {
        if (n < 2) {
            printf("we need at least two points to perform linear regression\n");
        }
        EMPTY_OR_NULL
        return -1; //-1 can then be interpreted by the main as a failure
    }
    double y_ = 0;
    double x_ = 0;
    double denom = 0;

    for (int i = 0; i < n; i++) {
        x_ += coords[i].x;
        y_ += coords[i].y;
    }
    x_ /= n;
    y_ /= n;

    for (int i = 0; i < n; i++) {
        denom += pow(coords[i].x - x_, 2);
    }

    if (fabs(denom) < EPSILON) {
        DEBUG
        return -1;
    }

    *a = 0;
    for (int i = 0; i < n; i++) {
        *a += (coords[i].x - x_) * (coords[i].y - y_);
    }
    *a /= denom;
    *b = y_ - (*a * x_);

    return 1; //means that it worked.
}

#endif //Y2_NUM_ALGO_LINEAR_H
