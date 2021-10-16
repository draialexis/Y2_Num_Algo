//
// Created by draia on 16/10/2021.
//

#ifndef Y2_NUM_ALGO_NEWTON_H
#define Y2_NUM_ALGO_NEWTON_H

void findPolyNewt(coord *coords, int points) {
    //TODO input validation

    //TODO check if two coords.x are the same.
    //  If not, go on.
    //  If so, check if the corresponding coords.y are the same.
    //      If not, exit with failure and alert,
    //          (or average them?)
    //      If so, remove one of the two entries and reset the check on the new coords
    //           which implies:
    //              points--;
    //              coord *tmp = ...
    //              coords = tmp;
    //              free(tmp);

    //using a table of divided differences, find the Newton interpolation polynomial that matches our datapoints

    int degP = points - 1;
    double **diffs = mkMat(degP, degP);
    int isMono;
    double prev;
    int isMonoPrev = 0;
    int jMono;
    int ops = 0;
    for (int j = 0; j < degP; ++j) {
        isMono = 1;
        for (int i = 0; i < degP - j; ++i) {//we don't want to fill the entire matrix

            /*

            *   *   *   *   *
            *   *   *   *   0
            *   *   *   0   0
            *   *   0   0   0
            *   0   0   0   0

             */

            //fill in first column of differences table
            if (j == 0) {
//                printf("diffs[%d][%d] = (coords[%d].y - coords[%d].y) / (coords[%d].x - coords[%d].x\n",
//                                i, j, i + 1, i, i + j + 1, i);
                diffs[i][j] = (coords[i + 1].y - coords[i].y) / (coords[i + 1].x - coords[i].x);
                ops += 3;
                // δ(y_i) = y_i - y_1
                //          ----------  for i ≥ 2
                //           x_i - x_1
                //
            } else {
                //fill in the rest thanks to the first column
//                printf("diffs[%d][%d] = (diffs[%d][%d] - diffs[%d][%d]) / (coords[%d].x - coords[%d].x)\n",
//                       i, j, i + 1, j - 1, i, j - 1, i + j + 1, i);
                if (!isMonoPrev) {
                    diffs[i][j] = (diffs[i + 1][j - 1] - diffs[i][j - 1]) / (coords[i + j + 1].x - coords[i].x);
                    ops += 3;
                }
                    // δ_n(y_i) = δ_(n-1)(y_i) - δ_(n-1)(y_n)
                    //           -----------------------------  for i ≥ n+1
                    //                   x_i - x_n
                else {
                    diffs[i][j] = 0.0;
                }
            }

            // we assume the column has all same coeffs. If two coeffs are different on one column, we take note
            // if we've spotted a mono column already, we don't need to check all that
            if (!isMonoPrev) {
                if (isMono && i != 0) {
                    if (diffs[i][j] != prev) {
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

    //we put all our 'b's in an array, b0 first
    double *poly = mkColVec(n_coeffs);
    for (int i = 0; i < degP + 1; ++i) {
        if (i == 0) {
            poly[i] = coords[0].y;
        } else {
            poly[i] = diffs[0][i - 1]; //b1 = diffs[0][0], b2 = diffs[0][1], etc.
        }
    }
    showPoly(poly, n_coeffs, coords);
}

#endif //Y2_NUM_ALGO_NEWTON_H
