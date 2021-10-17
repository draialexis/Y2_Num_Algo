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
    int cnt = 0;

    char *eqStr = (char *) malloc(sizeof(char) * points * 2 * bfr);
    sprintf(eqStr, "%c", '\0');
    char *tmp = (char *) malloc(sizeof(char) * bfr);

    for (int i = 0; i < points; i++) {
        if (fabs(coords[i].y) > EPSILON) {
            sprintf(tmp, "(%+05.10f", coords[i].y);
            strncat(eqStr, tmp, bfr);
            for (int j = 0; j < points; j++) {
                if (j != i) {
                    cnt++;
                    sprintf(tmp, " * ((x - (%+05.10f)) / ((%+05.10f) - (%+05.10f)))", coords[j].x, coords[i].x,
                            coords[j].x);
                    ops += 3;
                    strncat(eqStr, tmp, bfr);
//                    if (j < points - 1) {
//                        sprintf(tmp, " * ");
//                        strncat(eqStr, tmp, 30);
//                    }
                }
            }
            if (i < points - 1) {
                sprintf(tmp, ") + ");
            } else {
                sprintf(tmp, ")");
            }
            strncat(eqStr, tmp, 5);
        }
    }
    printf("operations: %d\n", ops);

    return eqStr;
}

#endif //Y2_NUM_ALGO_LAGRANGE_H
