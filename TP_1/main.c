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

    // TODO "Pour tester la sensibilite des algorithmes, resoudre les systemes Ax=b et A'x=b (A' est la matrice A dont
    //  les coefficients ont ete legerement perturbes) puis comparer les solutions x et x' obtenues est suffisant."
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
    srand(time(NULL));

    /*
    double **matA = mkMat(ROWS, COLS);
    fillMatA_rdm(matA, ROWS, COLS);
    double *matB = mkColVec(ROWS);
    fillMatB_rdm(matB, ROWS);
    double *matX = mkColVec(COLS);// "COLS" because: A(m,n) * X(_n_, p) = B(m, p) // p = 1

    double **matA_prime = copyMat(matA, ROWS, COLS);
    degradeMat(matA_prime, ROWS, COLS);
    double *matB_prime = copyColVec(matB, ROWS);
    double *matX_prime = mkColVec(COLS);

    printf("=======================\nGauss\n=======================\n");
    gaussElim(matA, ROWS, COLS, matB, matX, 0);
    freeMat(matA, ROWS, COLS);
    free(matB);
    free(matX);

    printf("=======================\nGauss\n=======================\n");
    gaussElim(matA_prime, ROWS, COLS, matB_prime, matX_prime, 0);
    freeMat(matA_prime, ROWS, COLS);
    free(matB_prime);
    free(matX_prime);

    double **matA_EZ = mkMat(3, 2);
    fillMat_EZ(matA_EZ);
    double *matB_EZ = mkColVec(3);
    fillMatB_EZ(matB_EZ);
    double *matX_EZ = mkColVec(3);

    printf("=======================\nGauss\n=======================\n");
    gaussElim(matA_EZ, 3, 2, matB_EZ, matX_EZ, 0);
    freeMat(matA_EZ, 3, 2);
    free(matB_EZ);
    free(matX_EZ);

    double **matASparse = mkMat(ROWS, COLS);
    fillSparseMat(matASparse, ROWS, COLS);
    double *matBSparse = mkColVec(ROWS);
    fillMatB_rdm(matBSparse, ROWS);
    double *matXSparse = mkColVec(COLS);

    printf("=======================\nGauss\n=======================\n");
    gaussElim(matASparse, ROWS, COLS, matBSparse, matXSparse, 0);
    freeMat(matASparse, ROWS, COLS);
    free(matBSparse);
    free(matXSparse);
    */



    char go = '0';
    int first = 1;
    while (go != 'q') {

        char str[30];

        if (first) {
            printf("bienvenue dans ce solveur de systemes d'equations lineaires\n");
            first = 0;
        }
        printf("entrez le caractere 'q' pour arreter,\nou autre pour continuer :\n>");

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
        fflush(stdin);

        int max_i_input;
        int epsilon_input;
        if (method == 'j') {
            printf("choisissez le nombre max d'iterations, puis epsilon :\nmax_i\n>");
            scanf("%s", str);
            max_i_input = (int) strtol(str, NULL, 10);
            fflush(stdin);

            printf("epsilon\n>");
            scanf("%s", str);
            epsilon_input = (int) strtol(str, NULL, 10);
            fflush(stdin);
        }

        char matA_input = '0';
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

//        char degrade = '0';
//        printf("voulez-vous comparer avec une matrice A perturbee (par '0.1', sur un coeff) ?"
//               "\n* 'o' : oui"
//               "\n* 'n' : non"
//               "\n>");
//        scanf("%c", &degrade);
//        getchar();
//        fflush(stdin);
//TODO maybe, if there's time?

        char matB_input = '0';
        printf("choisissez votre matrice B :"
               "\n* 'a' : \"aleatoire\" (utilise '(rand() mod 101) + 50')"
               "\n* 'C' : customisee (input via console)"
               "\n>");
        matB_input = (char) getchar();
        getchar();
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
        double *matX_live = mkColVec(cols_input);

        switch (method) {
            case 'g' :
                DEBUG
                gaussElim(matA_live, rows_input, cols_input, matB_live, matX_live, 0);
                break;
            case 'j' :
                DEBUG
                jacobiMethod(matA_live, rows_input, cols_input, matB_live, matX_live, max_i_input, epsilon_input);
                break;
            default :
                printf("votre choix de methode n'a pas ete compris. methode de Gauss.\n");
                gaussElim(matA_live, rows_input, cols_input, matB_live, matX_live, 0);
                break;
        }
        freeMat(matA_live, rows_input, cols_input);
        free(matB_live);
        free(matX_live);
    }
    return 0;
}
