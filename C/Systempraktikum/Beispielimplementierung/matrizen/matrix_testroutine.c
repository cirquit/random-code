#include "matrixBib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*
Main-Funktion
*/
int main(int argc, char *argv[]) {

  // Zufallszahlengenerator initialisieren
  srand(time(NULL));
  matrix a = initMatrixRand(5,5);
  matrix b = initMatrixRand(5,5);

  printf("a =\n"); prettyPrint(a);
  printf("\nb =\n"); prettyPrint(b);

  matrix c = addMatrix(a, b);
  printf("\na + b =\n");
  prettyPrint(c);
  freeMatrix(c);

  c = subMatrix(a, b);
  printf("\na - b =\n");
  prettyPrint(c);
  freeMatrix(c);

  c = multMatrix(a, b);
  printf("\na * b =\n");
  prettyPrint(c);
  freeMatrix(c);

  c = transposeMatrix(a);
  printf("\na^T =\n");
  prettyPrint(c);
  freeMatrix(c);

  printf("\ndet(a) = %.2f\n", determinante(a));
  printf("detQuick(a) = %.2f\n\n", detQuick(a));

  printf("\ndet(b) = %.2f\n", determinante(b));
  printf("detQuick(b) = %.2f\n\n", detQuick(b));

  freeMatrix(a);
  freeMatrix(b);

  return 0;
}
