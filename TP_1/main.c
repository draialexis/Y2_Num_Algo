#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 15
#define COLS 15
#define EPSILON 0.00000000000022737367544323206000
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "toolbox.h"
#include "matrices_suite.h"
#include "lin_alg.h"

int main() {

/*
    printf("size of doubles: %llu bits\n", sizeof(double) * 8);

    //calculating machine epsilon
    double epsilon = 1.0;
    int count = 1;
    while (1.0 + (epsilon / 2.0) > 1.0) {
        // will be false as epsilon tends toward 0 ; will be interpreted as false after a few dozen iterations
        // on my desktop, 1.0 + 0.000000000000000444089209850063 / 2 > 1.0 is true
        // which means it detects doubles as close to 0 as 0.000000000000000222044604925031 (2^-51)
        epsilon = epsilon / 2.0;
        printf("2^-%d = %.32f\n", count, epsilon);
        count++;
    }

    //don't know why we do this... found that example in C# and C++ on https://newbedev.com/how-to-choose-epsilon-value-for-floating-point
    double epsilon_equation = sqrt(2 * epsilon * epsilon);
    printf("fabs(1.0 + 2.0 - 3.0) = %.32f\n", fabs(1.0 + 2.0 - 3.0));
    printf("sqrt(3.0 * sqrt(2 * epsilon * epsilon) * sqrt(2 * epsilon * epsilon) = %.32f\n",
           sqrt(3.0 * epsilon_equation * epsilon_equation)); // so.. epsilon * sqrt(6) ?? why?
    // are we checking that those successive operations don't deviate from the expected result?
    printf("epsilon is valid: ");
    // ternary conditionals are cool
    (fabs(1.0 + 2.0 - 3.0) < sqrt(3.0 * epsilon_equation * epsilon_equation)) ? printf("true\n") : printf("false\n");

    //it turns out that my epsilon is too high at 2^-52, going for 2^-42 seems to work though

    printf("EPSILON = %.32f\n", pow(2, -42));
*/
    srand((unsigned) time(NULL));

//    double **matA = mkMat(ROWS, COLS);
//    fillMatA_rdm(matA, ROWS, COLS);
//    double *matB = mkColVec(ROWS);
//    fillMatB_rdm(matB, ROWS);
//
//    double **matA_prime = copyMat(matA, ROWS, COLS);
//    degradeMat(matA_prime, ROWS, COLS);
//    double *matB_prime = copyColVec(matB, ROWS);
//
//    printf("=======================\nGauss\n=======================\n");
//    gaussMethod(matA, ROWS, COLS, matB, 0);
//    freeMat(matA, ROWS, COLS);
//    free(matB);
//
//    printf("=======================\nGauss\n=======================\n");
//    gaussMethod(matA_prime, ROWS, COLS, matB_prime, 0);
//    freeMat(matA_prime, ROWS, COLS);
//    free(matB_prime);
//    double **matA_EZ = mkMat(3, 2);
//    fillMat_EZ(matA_EZ);
//    double *matB_EZ = mkColVec(3);
//    fillMatB_EZ(matB_EZ);
//
//    printf("=======================\nJacobi\n=======================\n");
//    jacobiMethod(matA_EZ, 3, 2, matB_EZ, 20, 0.1);
//    printf("=======================\nGauss\n=======================\n");
//    gaussMethod(matA_EZ, 3, 2, matB_EZ, 0);
//    freeMat(matA_EZ, 3, 2);
//    free(matB_EZ);
//    double **matASparse = mkMat(ROWS, COLS);
//    fillSparseMat(matASparse, ROWS, COLS);
//    double *matBSparse = mkColVec(ROWS);
//    fillMatB_rdm(matBSparse, ROWS);
//
//    printf("=======================\nGauss\n=======================\n");
//    gaussMethod(matASparse, ROWS, COLS, matBSparse, 0);
//    freeMat(matASparse, ROWS, COLS);
//    free(matBSparse);


    char go = '0';
    int first = 1;
    while (go != 'q') {

        char str[30];

        if (first) {
            printf("bienvenue dans ce solveur de systemes d'equations lineaires\n");
            first = 0;
        }
        printf("entrez le caractere 'q' pour arreter,\nou tout autre pour continuer :\n>");

        go = (char) getchar();
        getchar();
        fflush(stdin);

        if (go == 'q') {
            break;
        }

        char method = '0';
        printf("choisissez votre methode :"
               "\n* 'g' : Gauss"
               "\n* 'j' : Jacobi"
               "\n>");
        method = (char) getchar();
        getchar();
        if (method == 'q') exit(0);
        fflush(stdin);

        int max_i_input;
        double epsilon_input;
        if (method == 'j') {
            printf("choisissez le nombre max d'iterations, puis epsilon :\nmax_i\n>");
            scanf("%s", str);
            max_i_input = (int) strtol(str, NULL, 10);
            fflush(stdin);

            printf("epsilon\n>");
            scanf("%s", str);
            epsilon_input = (double) strtof(str, NULL);
            fflush(stdin);
        }

        char matA_input = '0';
        //TODO signal which ones are strictly diagonally dominant
        printf("choisissez votre matrice A :"
               "\n* 'b' : Bord"
               "\n* 'd' : Ding Dong"
               //               "\n* 'f' : Franc"
               //               "\n* 'h' : Hilbert -"
               //               "\n* 'H' : Hilbert +"
               //               "\n* 'k' : KMS"
               //               "\n* 'l' : Lehmer"
               //               "\n* 'L' : Lotkin"
               //               "\n* 'm' : Moler"
               "\n* 'a' : \"aleatoire\" (utilise '(rand() mod 101) + 50')"
               "\n* 'c' : creuse"
               "\n* 'C' : customisee (input via console)"
               "\n>");
        matA_input = (char) getchar();
        getchar();
        fflush(stdin);
        if (matA_input == 'q') exit(0);

        int size_input = 0;
        int rows_input = 0;
        int cols_input = 0;

        if (matA_input == 'a' || matA_input == 'c' || matA_input == 'C') {
            printf("choisissez le nombre de rangees, puis de colonnes :\nrangees\n>");
            scanf("%s", str);
            rows_input = (int) strtol(str, NULL, 10);
            fflush(stdin);
            printf("colonnes\n>");
            scanf("%s", str);
            cols_input = (int) strtol(str, NULL, 10);
            fflush(stdin);

        } else {
            printf("la matrice choisie est carree ; choisissez sa taille :\n>");
            scanf("%s", str);
            size_input = (int) strtol(str, NULL, 10);
            fflush(stdin);
        }

        char degrade = '0';
        printf("voulez-vous comparer A avec une matrice A' perturbee (par '0.1', sur l'un des coeffs) ?"
               "\n* 'o' : oui"
               "\n* 'n' : non"
               "\n>");
        degrade = (char) getchar();
        fflush(stdin);

        char matB_input = '0';
        printf("choisissez votre matrice B :"
               "\n* 'a' : \"aleatoire\" (utilise '(rand() mod 101) + 50')"
               "\n* 'C' : customisee (input via console)"
               "\n>");
        matB_input = (char) getchar();
        getchar();
        if (matB_input == 'q') exit(0);
        fflush(stdin);

        int isSquare = 0;
        if (!(rows_input && cols_input)) {
            rows_input = size_input;
            cols_input = size_input;
            isSquare = 1;
        }

        double **matA_live = mkMat(rows_input, cols_input);
        doA(matA_live, rows_input, cols_input, matA_input, isSquare);
        double *matB_live = mkColVec(rows_input);
        doB(matB_live, rows_input, matB_input);
        if (degrade == 'o') {
            double **matA_live_prime = copyMat(matA_live, rows_input, cols_input);
            degradeMat(matA_live_prime, rows_input, cols_input);
            double *matB_live_prime = copyColVec(matB_live, ROWS);
            if (method == 'g') {
                gaussMethod(matA_live, rows_input, cols_input, matB_live, 0);
                gaussMethod(matA_live_prime, rows_input, cols_input, matB_live_prime, 0);
            } else if (method == 'j') {
                jacobiMethod(matA_live, rows_input, cols_input, matB_live, max_i_input, epsilon_input);
                jacobiMethod(matA_live_prime, rows_input, cols_input, matB_live_prime, max_i_input, epsilon_input);
            }
            freeMat(matA_live_prime, rows_input, cols_input);
            free(matB_live_prime);
        } else {
            if (method == 'g') {
                gaussMethod(matA_live, rows_input, cols_input, matB_live, 0);
            } else if (method == 'j') {
                jacobiMethod(matA_live, rows_input, cols_input, matB_live, max_i_input, epsilon_input);
            }
        }
        freeMat(matA_live, rows_input, cols_input);
        free(matB_live);
    }

    return 0;
}
