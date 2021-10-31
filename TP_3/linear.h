//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_LINEAR_H
#define Y2_NUM_ALGO_LINEAR_H

int linReg(coord *coords, int n, double *a, double *b, int *o); //TODO add , double *err

int linReg(coord *coords, int n, double *a, double *b, int *o) {
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

    //calculate the average of Xs and of Ys
    for (int i = 0; i < n; i++) {
        x_ += coords[i].x;
        y_ += coords[i].y;
        *o += 2;////<< 2n
    }
    x_ /= n;
    y_ /= n;
    *o += 2;////<< 2

    //use least squares method: calculate the sum of the squares of the differences between each X and our X_
    for (int i = 0; i < n; i++) {
        denom += pow(coords[i].x - x_, 2);////<< 3n
        *o += 3;
    }

    //make sure that the denominator is not 0 (or close enough to 0 to cause issues)
    if (fabs(denom) < EPSILON) {
        DEBUG
        return -1;
    }

    //calculate the slope by summing the products of the differences
    //between each X and our X_, and between each Y and our Y_
    //then dividing by our denominator
    *a = 0;
    for (int i = 0; i < n; i++) {
        *a += (coords[i].x - x_) * (coords[i].y - y_);////<< 4n
        *o += 4;
    }
    *a /= denom;////<< 1
    *o += 1;

    //calculate the intersect from our knowledge of the slope, the average of Xs, and the average of Ys
    *b = y_ - (*a * x_);////<< 2
    *o += 2;
//    printf("%d points, complexite: 9n+5, nb d'ops attendu: %d\n", n, ((9 * n) + 5));
    return 1; //means that it worked.
}

#endif //Y2_NUM_ALGO_LINEAR_H
