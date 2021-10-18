//
// Created by draia on 16/10/2021.
//

#ifndef Y2_NUM_ALGO_LAGRANGE_H
#define Y2_NUM_ALGO_LAGRANGE_H

char *findPolyLagr(coord *coords, int points);

char *findPolyLagr(coord *coords, int points) {

    if (coords == NULL && points < 2) {
        if (points < 2) {
            printf("il faut au moins deux points pour interpoler un polynome\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    int ops = 0;
    int bfr = 32;
    char *eqStr = (char *) malloc(sizeof(char) * points * 512);
    sprintf(eqStr, "%c", '\0');
    char *tmp = (char *) malloc(sizeof(char) * bfr);
    double pdt;
    double denom;
    int first = 1;

    for (int i = 0; i < points; i++) {
        if (fabs(coords[i].y) > EPSILON) {
            if (!first) {
                ops++;////<< n-1
                sprintf(tmp, "+");
                strncat(eqStr, tmp, 2);
            } else {
                first = 0;
            }
            pdt = coords[i].y;
            for (int j = 0; j < points; j++) {
                if (j != i) {
                    denom = coords[i].x - coords[j].x;
                    ops++;////<< n(n-1)
                    if (fabs(denom) > EPSILON) {
                        // we can extract the known factors from the unknowns, then combine them later
                        // for readability and file-size
                        //      li = (x -xj) / (x_i - x_j)
                        //
                        // <=>  li = 1 / (x_i - x_j) * (x -xj)
                        pdt /= denom;////<< n(n-1)
                        ops++;
                        if (fabs(coords[j].x) > EPSILON) {
                            sprintf(tmp, "(x-(%.5f))*", coords[j].x);
                            strncat(eqStr, tmp, bfr);
                        } else {
                            sprintf(tmp, "(x)*");
                            strncat(eqStr, tmp, bfr);
                        }
                        ops += 2;////<< 2(n(n-1))
                    } else {
                        printf("deux coordonnees avec meme x.\n");
                        DEBUG
                        FAIL_OUT
                    }
                }
            }
            sprintf(tmp, "(%+.15f)", pdt);
            strncat(eqStr, tmp, bfr);
        }
    }
    printf("operations: %d\n", ops);

    return eqStr;
}

#endif //Y2_NUM_ALGO_LAGRANGE_H