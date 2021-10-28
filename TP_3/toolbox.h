//
// Created by draia on 28/10/2021.
//

#ifndef Y2_NUM_ALGO_TOOLBOX_H
#define Y2_NUM_ALGO_TOOLBOX_H

typedef struct Coordinate {
    double x;
    double y;
} coord;

coord *mkCoordArr(int points);

coord *mkCoordArr(int points) {
    if (points > 0) {
        coord *arr = NULL;
        arr = (coord *) malloc(sizeof(coord) * points);
        if (arr == NULL) {
            MALLOC_FAIL
        }
        return arr;
    } else {
        EMPTY_OR_NULL
        FAIL_OUT
    }
}

#endif //Y2_NUM_ALGO_TOOLBOX_H
