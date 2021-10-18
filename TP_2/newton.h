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
            denom = coords[i + j + 1].x - coords[i].x;////<< (n*(n-1))/2
            ops++;
            if (fabs(denom) > EPSILON) {
                //fill in first column of differences table
                if (j == 0) {
                    diffs[i][j] = (coords[i + 1].y - coords[i].y) / denom;////<< 2*(n*(n-1))/2 au pire, 0 au mieux
                    ops += 2;
                    // δ(y_i) = y_i - y_1
                    //          ----------  for i ≥ 2
                    //           x_i - x_1
                    //
                } else {
                    //fill in the rest thanks to the first column

                    if (!isMonoPrev) {
                        diffs[i][j] = (diffs[i + 1][j - 1] - diffs[i][j - 1]) / denom;
                        ops += 2;
                    }
                        // δ^k(y_i) = δ^(k-1)(y_i) - δ^(k-1)(y_k)
                        //           -----------------------------  for i ≥ k+1
                        //                   x_i - x_k

                        //si la colonne prec de cette table a des coeff identiques, tous les coeffs suivants seront 0
                        // on s'epargne des calculs et on peut réévaluer le degré du polynome cherché
                        // possible aussi avec lagrange, mais difficile à implémenter si ce n'est pas à la main.
                        // du au manque de précision des calculs de floats
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
            } else {
                printf("deux coordonnees avec meme x.\n");
                DEBUG
                FAIL_OUT
            }
        }
        //if we haven't proved that the column isn't monotone, it means that it is. We can fill rest with 0s and stop calculating
        // but if we're already 0-filling the matrix, we don't care
        if (!isMonoPrev && isMono) {
            isMonoPrev = 1;
            degP = j + 1;
        }
    }

    const int n_coeffs = degP + 1;//+ 1 for the x^0 coeff
    printf("differences divisees:\n");
    showDiffMat(diffs, degP);
    //we put all our 'b's in an array, b0 first
    double *poly = mkColVec(n_coeffs);
    for (int i = 0; i < n_coeffs; i++) {
        if (i == 0) {
            poly[i] = coords[0].y;
        } else {
            poly[i] = diffs[0][i - 1]; //b1 = diffs[0][0], b2 = diffs[0][1], etc.
        }
    }
    return printPoly(poly, n_coeffs, coords, ops);
}

#endif //Y2_NUM_ALGO_NEWTON_H
