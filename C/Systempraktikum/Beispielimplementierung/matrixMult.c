#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Groesse der Matrizen festlegen
#define SIZE 3

/*
Main
*/
int main(int argc, char *argv[]) {
  
  // a * b = erg
  int a[SIZE][SIZE], b[SIZE][SIZE], erg[SIZE][SIZE];
  
  // Zufallszahlengenerator initialisieren
  srand(time(NULL));
  // a und b mit zufaelligen werten zwischen 0 und 9 belegen
  for (int i=0; i < SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
      a[i][j] = rand()%10;
      b[i][j] = rand()%10;
    }
  }
  
  // Multiplikation durchfuehren
  for (int i=0; i < SIZE; i++) {
    for (int j=0; j < SIZE; j++) {
      int temp = 0;
      for (int n=0; n < SIZE; n++) {
        temp += a[i][n] * b[n][j];
      }
      erg[i][j] = temp;
    }
  }
  
  // Ergebnis ausgeben
  for (int i=0; i < SIZE; i++) {
    for (int j=0; j < SIZE; j++) printf("%i ", a[i][j]);
    if (i == SIZE/2) printf("* "); else printf("  ");
    for (int j=0; j < SIZE; j++) printf("%i ", b[i][j]);
    if (i == SIZE/2) printf("= "); else printf("  ");
    for (int j=0; j < SIZE; j++) printf("%3d ", erg[i][j]);
    printf("\n");
  }
  
  // Ende
  return 0;
}