//
// Created by draia on 16/10/2021.
//

#ifndef Y2_NUM_ALGO_LAGRANGE_H
#define Y2_NUM_ALGO_LAGRANGE_H

void findPolyLagr(coord *coords, int points);

void findPolyLag(coord *coords, int points) {

    if (coords == NULL && points < 2) {
        if (points < 2) {
            printf("we need at least two points to interpolate a polynomial\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int degP = points - 1;
    int ops = 0;
    int bfr = 32;

    char *res = (char *) malloc(sizeof(char) * points * bfr);
    sprintf(res, "%c", '\0');
    char *tmp = (char *) malloc(sizeof(char) * bfr);

    for (int i = 0; i < points; i++) {
        if (fabs(coords[i].y) > EPSILON) {
            sprintf(tmp, "%+05.10f * ", coords[i].y);
            strncat(res, tmp, bfr);
            for (int j = 0; j < points; j++) {
                if (j != i) {
                    sprintf(tmp, "((x - (%+05.10f)) / (%+05.10f) - (%+05.10f))", coords[j].x);
                    strncat(res, tmp, bfr);
                    if (j < i - 1) {
                        sprintf(tmp, " * ");
                        strncat(res, tmp, bfr);
                    }
                }
            }
        }
    }

    printf("operations: %d\n", ops);
}

#endif //Y2_NUM_ALGO_LAGRANGE_H
