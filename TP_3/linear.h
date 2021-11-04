//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_LINEAR_H
#define Y2_NUM_ALGO_LINEAR_H

int linReg(coord *coords, int n, double *a, double *b, int *o);

int linReg(coord *coords, int n, double *a, double *b, int *o) {
    if (coords == NULL || n < 2) {
        EMPTY_OR_NULL
        return -1; //-1 can then be interpreted by the main as a failure
    }
    double y_ = 0;
    double x_ = 0;
    double denom = 0;

    //calculate the average of Xs and of Ys
    for (int i = 0; i < n; i++) {
        x_ += coords[i].x;
        y_ += coords[i].y;
        *o += 2;////<< 2n
    }
    x_ /= n;
    y_ /= n;
    *o += 2;////<< 2


    //calculate the sum of the squares of the differences between each X and our X_
    //and calculate the slope by summing the products of the differences
    //between each X and our X_, and between each Y and our Y_
    *a = 0;
    for (int i = 0; i < n; i++) {
        double x_dif = (coords[i].x - x_);////<< n
        denom += pow(x_dif, 2);////<< 2n
        *a += x_dif * (coords[i].y - y_);////<< 3n
        *o += 6;
    }
    //then dividing by our denominator
    //make sure that the denominator is not 0 (or close enough to 0 to cause issues)
    if (fabs(denom) < EPSILON) {
        DEBUG
        return -1;
    }
    *a /= denom;////<< 1
    *o += 1;

    //calculate the intersect from our knowledge of the slope, the average of Xs, and the average of Ys
    *b = y_ - (*a * x_);////<< 2
    *o += 2;
    return 1; //means that it worked.
}

#endif //Y2_NUM_ALGO_LINEAR_H
