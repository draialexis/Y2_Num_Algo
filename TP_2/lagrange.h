//
// Created by draia on 16/10/2021.
//

#ifndef Y2_NUM_ALGO_LAGRANGE_H
#define Y2_NUM_ALGO_LAGRANGE_H

char *findPolyLagr(coord *coords, int points);

char *findPolyLagr(coord *coords, int points) {

    if (coords == NULL && points < 2) {
        if (points < 2) {
            printf("we need at least two points to interpolate a polynomial\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int ops = 0;
    int bfr = 128;

    char *eqStr = (char *) malloc(sizeof(char) * points * 2 * bfr);
    sprintf(eqStr, "%c", '\0');
    char *tmp = (char *) malloc(sizeof(char) * bfr);

    double pdt;
    int first = 1;

    for (int i = 0; i < points; i++) {
        if (fabs(coords[i].y) > EPSILON) {
            if (!first) {
                sprintf(tmp, " + ");
                strncat(eqStr, tmp, 3);
            } else {
                first = 0;
            }
            pdt = coords[i].y;
            for (int j = 0; j < points; j++) {
                if (j != i) {

                    // we can extract the known factors from the unknowns, then combine them, for readability and file-size
                    //      li = (x -xj) / (x_i - x_j)
                    //
                    // <=>  li = 1 / (x_i - x_j) * (x -xj)
                    pdt *= (1 / (coords[i].x - coords[j].x));
                    ops += 3;

                    if (fabs(coords[j].x) > EPSILON) {
                        sprintf(tmp, "(x - (%+05.10f)) * ", coords[j].x);
                        strncat(eqStr, tmp, bfr);
                    } else {
                        sprintf(tmp, "(x) * ");
                        strncat(eqStr, tmp, bfr);
                    }
                }
            }
            sprintf(tmp, "(%+05.10f)", pdt);
            strncat(eqStr, tmp, bfr);
        }
    }
    printf("operations: %d\n", ops);

    return eqStr;
}

#endif //Y2_NUM_ALGO_LAGRANGE_H
