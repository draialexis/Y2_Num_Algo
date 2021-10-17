//
// Created by draia on 16/10/2021.
//

#ifndef Y2_NUM_ALGO_NEWTON_H
#define Y2_NUM_ALGO_NEWTON_H

char *findPolyNewt(const coord *coords, int points);

char *findPolyNewt(const coord *coords, const int points) {

    if (coords == NULL && points < 2) {
        if (points < 2) {
            printf("we need at least two points to interpolate a polynomial\n");
        }
        EMPTY_OR_NULL
        FAIL_OUT
    }

    //using a table of divided differences, find the Newton interpolation polynomial that matches our datapoints

    int degP = points - 1;
    double **diffs = mkMat(degP, degP);
    int isMono;
    double prev;
    int isMonoPrev = 0;
    int ops = 0;
    double denom;
    double div;
    for (int j = 0; j < degP; j++) {
        isMono = 1;
        for (int i = 0; i < degP - j; i++) {//we don't want to fill the entire matrix
            /*

            *   *   *   *   *
            *   *   *   *   0
            *   *   *   0   0
            *   *   0   0   0
            *   0   0   0   0

             */
            denom = coords[i + j + 1].x - coords[i].x;
            ops++;
            if (fabs(denom) > EPSILON) {
                div = 1 / denom;
                ops++;
            } else {
                printf("deux coordonnees avec meme x.\n");
                DEBUG
                FAIL_OUT
            }
            //fill in first column of differences table
            if (j == 0) {
                diffs[i][j] = (coords[i + 1].y - coords[i].y) * div;
                ops += 2;
                // δ(y_i) = y_i - y_1
                //          ----------  for i ≥ 2
                //           x_i - x_1
                //
            } else {
                //fill in the rest thanks to the first column

                if (!isMonoPrev) {
                    diffs[i][j] = (diffs[i + 1][j - 1] - diffs[i][j - 1]) * div;
                    ops += 3;
                }
                    // δ^k(y_i) = δ^(k-1)(y_i) - δ^(k-1)(y_k)
                    //           -----------------------------  for i ≥ k+1
                    //                   x_i - x_k
                else {
                    diffs[i][j] = 0.0;
                }
            }

            // we assume the column has all same coeffs. If two coeffs are different on one column, we take note
            // if we've spotted a mono column already, we don't need to check all that
            if (!isMonoPrev) {
                if (isMono && i != 0) {
                    if (fabs(diffs[i][j] - prev) > EPSILON) {
                        isMono = 0;
                    }
                }
                prev = diffs[i][j];
            }
        }
        //if we haven't proved that the column isn't monotone, it means that it is. We can fill rest with 0s and stop calculating
        // but if we're already 0-filling the matrix, we don't care
        if (!isMonoPrev && isMono) {
            isMonoPrev = 1;
            degP = j + 1;
        }
    }

    printf("operations: %d\n", ops);
    const int n_coeffs = degP + 1;//+ 1 for the x^0 coeff
    showDiffMat(diffs, degP);//TODO remove
    //we put all our 'b's in an array, b0 first
    double *poly = mkColVec(n_coeffs);
    for (int i = 0; i < degP + 1; i++) {
        if (i == 0) {
            poly[i] = coords[0].y;
        } else {
            poly[i] = diffs[0][i - 1]; //b1 = diffs[0][0], b2 = diffs[0][1], etc.
        }
    }
    showRow(poly, n_coeffs);//TODO remove
    return printPoly(poly, n_coeffs, coords);
}

#endif //Y2_NUM_ALGO_NEWTON_H
