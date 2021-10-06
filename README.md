# Algorithmique numérique -- TP#1

Une fois le repo cloné, le fichier main.c peut être compilé en utilisant l'option de librarie "-lm" 

`gcc -Wall main.c -o main -lm`

La méthode de Gauss consiste à utiliser des opérations élémentaires sur les lignes d’une matrice augmentée (A|B) (substitution, addition, multiplication par un scalaire) de manière à obtenir une matrice équivalente mais triangulaire. Cela rend la résolution de AX = B beaucoup plus rapide en général, plus aisée, et plus sûre. En effet, on peut simplement partir de la dernière ligne où l’on trouve la valeur de notre dernière inconnue, puis on effectue les substitutions en remontant dans le système.
 
En revanche, dans certains cas, résoudre un tel système n’est pas aussi simple que de trouver la solution unique comme décrit plus haut. Si une ligne nulle de A correspond à une ligne non nulle de B, le système n’admet aucune solution. Plus grave, si un système contient plus d’inconnues principales que de lignes principales, il admet alors une infinité de solutions, basée sur au moins un paramètre et au moins une inconnue proportionnelle à ce dernier.
 
En termes de programmation, les problèmes spécifiques qui ont émergés sont des difficultés à coder la résolution de système avec infinité de solutions (abandonné après quelques jours), de l’instabilité en essayant d’implémenter Gauss-Jordan (entraînant parfois des coefficients très petits), et des troubles avec des opérations arithmétiques sur des floats très petits (remédié par l’utilisation d’un epsilon (de 2^-40)).
 
Dès l’entrée dans la fonction `gaussMethod()`, on établit l’homogénéité ou non du système, grâce à une fonction annexe `isHomSys()`.

       int homSys = isHomSys(B, rowsA);


On s’affaire ensuite à intervertir des lignes de la matrice augmentée, pour placer les nombres les plus grands possibles (en termes de valeur absolue) sur la diagonale, et limitant ainsi les factorisations et multiplications par des floats très petits, favorisant ainsi la stabilité de l’algorithme.

       for (int i = 0; i < rowsA; i++) {
           int maxPos = i;
           double maxVal = fabs(A[maxPos][i]);
           for (int k = i + 1; k < rowsA; ++k) {
               if (fabs(A[k][i]) - maxVal > EPSILON) {
                   maxVal = fabs(A[k][i]);
                   maxPos = k;
               }
           }
           if (maxPos != i) {rowSwap(A, B, i, maxPos, colsA);}


Une fois la diagonale dotée du coefficient le plus grand de la colonne, on entame une deuxième boucle interne ou l’on effectue des opérations élémentaires sur la ligne correspondante de la matrice augmentée.

       for (int k = i + 1; k < rowsA; ++k) {
           if (fabs(A[k][i]) < EPSILON || fabs(A[i][i]) < EPSILON) {
               continue;
           } else {
               factor = (A[k][i] / A[i][i]);
               rowTransform(A[k], colsA, A[i], factor);
               B[k] -= factor * B[i];
           }
       }
On passe alors le relais à une fonction annexe, `solveGauss()`. Qui passe temporairement le relais à `nilRows()`.
 
       int nilRowsCount = nilRows(A, rowsA, colsA, B, homSys);
       if (nilRowsCount == -1) {
           return;
       }

Cette fonction nous renvoie le nombre de lignes nulles de (A|B). Dans le cas où elle trouve une ligne nulle de A correspondant à un coefficient non-nul de B, `nilRows()` annonce l’absence de solution à l’utilisateur et renvoie un signal pour stopper le programme.
 
Si au contraire la prise en compte d’une ligne non principale nous permet de détecter que le nombre d’inconnues est maintenant égal au nombre de lignes, on peut alors déclarer qu’une solution unique existe. En effet, s’il y avait des lignes proportionnelles, elles auraient étées dévoilées et traitées avant.
 
       if (rowsA - nilRowsCount == colsA) { 
           printf("A * X = B a une solution\n");
           if (homSys) {
               printf("...le vecteur 0(%d)\n", colsA);
           } else {
               double *X = mkColVec(colsA);
               X[colsA - 1] = B[colsA - 1] / A[colsA - 1][colsA - 1];
               for (int i = colsA - 2; i >= 0; i--) {
                   double sum = 0;
                   for (int j = i + 1; j < colsA; j++) {
                       sum += A[i][j] * X[j];
                   }
                   X[i] = (B[i] - sum) / A[i][i];                          
               }
               printf("X = \n");
               showCol(X, colsA);
               free(X);
           }
       } else if (rowsA - nilRowsCount < colsA) {
           printf("A * X = B a une infinite de solutions\n");
           if (homSys) {
               printf("...y compris le vecteur 0(%d)\n", colsA);
           }
       } 
    }
 
