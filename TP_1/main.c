#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 5
#define COLS 5
#define EPSILON 0.00000000000022737367544323206000
#define DEBUG printf("file %s; line %d\n", __FILE__, __LINE__);
#define FAIL_OUT exit(EXIT_FAILURE);
#define MALLOC_FAIL printf("!_malloc failed_!\n"); DEBUG FAIL_OUT
#define EMPTY_OR_NULL printf("this data structure doesn't have a positive integer value as its size, or the pointer to it isn't valid\n"); DEBUG;

#include "toolbox.h"
#include "matrices_suite.h"
#include "lin_alg.h"

int main() {

    srand((unsigned) time(NULL));
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
    char go = '0';
    int first = 1;
    while (go != 'q') {

        char inp[30];
        char *endPtr;

        if (first) {
            printf("\nbienvenue dans ce solveur de systemes d'equations lineaires\n");
            first = 0;
        }
        printf("entrez le caractere 'q' pour arreter (a tout moment),\nou tout autre pour continuer :\n>");

        go = (char) getchar();
        cleanCheck(go);//cleans the console input buffer and checks if the user wants to quit

        char methd;
        printf("choisissez votre methode :"
               "\n* 'g' : Gauss"
               "\n* 'j' : Jacobi"
               "\n>");
        methd = (char) getchar();
        cleanCheck(methd);

        char compare;
        printf("voulez-vous comparer jacobi(A) avec gauss(A) ?"
               "\n* 'o' : oui"
               "\n* 'n' : non"
               "\n>");
        compare = (char) getchar();
        cleanCheck(compare);

        int max_i;
        double eps;
        if (methd == 'j' || compare == 'o') {
            printf("choisissez le nombre max d'iterations, puis epsilon :"
                   "\nmax_i"
                   "\n>");
            scanf("%s", inp);
            max_i = (int) strtol(inp, &endPtr, 10);
            cleanCheck(*endPtr);

            printf("epsilon"
                   "\n>");
            scanf("%s", inp);
            eps = strtod(inp, &endPtr);
            cleanCheck(*endPtr);
        }

        char matA;
        printf("choisissez votre matrice A :"
               "\n* 'b' : Bord"
               "\n* 'd' : Ding Dong"
               "\n* 'f' : Franc"
               "\n* 'h' : Hilbert -"
               "\n* 'H' : Hilbert +"
               "\n* 'k' : KMS"
               "\n* 'l' : Lehmer"
               "\n* 'L' : Lotkin"
               "\n* 'm' : Moler"
               "\n* 's' : matrice a diagonale strictement dominante"
               "\n* 'a' : \"aleatoire\" (utilise '(rand() mod 101) + 50')"
               "\n* 'c' : creuse"
               "\n* 'C' : customisee (input via console)"
               "\n>");
        matA = (char) getchar();
        cleanCheck(matA);

        int size = 0;
        int rows = 0;
        int cols = 0;

        if (matA == 'a' || matA == 'c' || matA == 'C') {
            printf("choisissez le nombre de rangees, puis de colonnes :"
                   "\nrangees"
                   "\n>");
            scanf("%s", inp);
            rows = (int) strtol(inp, &endPtr, 10);
            cleanCheck(*endPtr);

            printf("colonnes"
                   "\n>");
            scanf("%s", inp);
            cols = (int) strtol(inp, &endPtr, 10);
            cleanCheck(*endPtr);
        } else {
            printf("la matrice choisie est carree ; choisissez sa taille :"
                   "\n>");
            scanf("%s", inp);
            size = (int) strtol(inp, &endPtr, 10);
            cleanCheck(*endPtr);
        }

        char degrade;
        if (compare != 'o') {
            printf("voulez-vous comparer A avec une matrice A' perturbee (par '0.1', sur l'un des coeffs) ?"
                   "\n* 'o' : oui"
                   "\n* 'n' : non"
                   "\n>");
            degrade = (char) getchar();
            cleanCheck(degrade);
        }

        char matB;
        printf("choisissez votre matrice B :"
               "\n* 'a' : \"aleatoire\" (utilise '(rand() mod 101) + 50')"
               "\n* 'C' : customisee (input via console)"
               "\n>");
        matB = (char) getchar();
        cleanCheck(matB);

        int isSquare = 0;
        if (!(rows && cols)) {
            rows = size;
            cols = size;
            isSquare = 1;
        }

        char details;
        printf("derniere question : voulez-vous observer les etapes, ou juste le resultat ?"
               "\n* 'e' : chaque etape / iteration"
               "\n* 'r' : seulement le resultat"
               "\n>");
        details = (char) getchar();
        cleanCheck(details);

        int show = 0;
        if (details == 'e') show = 1;

        double **matA_live = mkMat(rows, cols);
        doA(matA_live, rows, cols, matA, isSquare);
        double *matB_live = mkColVec(rows);
        doB(matB_live, rows, matB);
        if (compare != 'o' && degrade == 'o') {
            double **matA_live_prime = copyMat(matA_live, rows, cols);
            degradeMat(matA_live_prime, rows, cols);
            double *matB_live_prime = copyColVec(matB_live, rows);
            if (methd == 'g') {
                gaussMethod(matA_live, rows, cols, matB_live, 0, show);
                gaussMethod(matA_live_prime, rows, cols, matB_live_prime, 0, show);
            } else if (methd == 'j') {
                jacobiMethod(matA_live, rows, cols, matB_live, max_i, eps, show);
                jacobiMethod(matA_live_prime, rows, cols, matB_live_prime, max_i, eps, show);
            }
            freeMat(matA_live_prime, rows, cols);
            free(matB_live_prime);
        }
        if (compare == 'o' && degrade != 'o') {
            double **matA_live_scd = copyMat(matA_live, rows, cols);
            double *matB_live_scd = copyColVec(matB_live, rows);
            jacobiMethod(matA_live, rows, cols, matB_live, max_i, eps, show);
            gaussMethod(matA_live_scd, rows, cols, matB_live_scd, 0, show);
            freeMat(matA_live_scd, rows, cols);
            free(matB_live_scd);
        } else {
            if (methd == 'g') {
                gaussMethod(matA_live, rows, cols, matB_live, 0, show);
            } else if (methd == 'j') {
                jacobiMethod(matA_live, rows, cols, matB_live, max_i, eps, show);
            }
        }
        freeMat(matA_live, rows, cols);
        free(matB_live);
    }
    return 0;
}
