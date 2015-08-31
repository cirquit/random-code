#include "matrixBib.h"
#include <stdlib.h>
#include <stdio.h>

matrix initMatrix(unsigned int breite, unsigned int hoehe) {
  matrix myMatrix;
  if (breite == 0 || hoehe == 0) {
    myMatrix.eintraege = NULL;
    myMatrix.breite = 0;
    myMatrix.hoehe = 0;
  } else {
    myMatrix.eintraege = (double*) malloc(breite*hoehe*sizeof(double));
    myMatrix.breite = breite;
    myMatrix.hoehe = hoehe;
  }
  return myMatrix;
}

matrix initMatrixZero(unsigned int breite, unsigned int hoehe) {
  matrix myMatrix = initMatrix(breite, hoehe);
  for (int i = 0; i < breite*hoehe; i++) {
    myMatrix.eintraege[i] = 0;
  }
  return myMatrix;
}

matrix initMatrixRand(unsigned int breite, unsigned int hoehe) {
  matrix myMatrix = initMatrix(breite, hoehe);
  for (int i = 0; i < breite*hoehe; i++) {
    myMatrix.eintraege[i] = rand()%200-100+(rand()%100)/100.0;
  }
  return myMatrix;
}

matrix copyMatrix(matrix toCopy) {
  matrix copy = initMatrix(toCopy.breite, toCopy.hoehe);
  for (int i = 0; i < toCopy.breite*toCopy.hoehe; i++) {
    copy.eintraege[i] = toCopy.eintraege[i];
  }
  return copy;
}

void freeMatrix(matrix toDestroy) {
  if (toDestroy.eintraege != NULL) free(toDestroy.eintraege);
  toDestroy.breite = 0;
  toDestroy.hoehe = 0;
}

double getEntryAt(matrix a, unsigned int xPos, unsigned int yPos) {
  if (xPos >= a.breite || yPos >= a.hoehe) return DBL_MAX;
  return a.eintraege[yPos*a.breite+xPos];
}

bool setEntryAt(matrix a, unsigned int xPos, unsigned int yPos, double value) {
  if (xPos >= a.breite || yPos >= a.hoehe) return false;
  a.eintraege[yPos*a.breite+xPos] = value;
  return true;
}

void prettyPrint(matrix a) {
  for (int h=0; h < a.hoehe; h++) {
    printf("(");
    for (int b=0; b < a.breite; b++) {
      printf("%*.2f", 8, getEntryAt(a,b,h)); // drucke min. 8 Zeichen bei 2 Nachkommastellen pro Eintrag
      if (b < a.breite-1) printf(" ");
    }
    printf(")\n");
  }
}

matrix addMatrix(matrix a, matrix b) {
  if (a.breite!=b.breite || a.hoehe!=b.hoehe) {
    matrix fehler = initMatrix(0, 0);
    return fehler;
  }
  matrix erg = initMatrix(a.breite, a.hoehe);
  for (int i = 0; i < a.hoehe*a.breite; i++) {
    erg.eintraege[i] = a.eintraege[i] + b.eintraege[i];
  }
  return erg;
}

matrix subMatrix(matrix a, matrix b) {
  if (a.breite!=b.breite || a.hoehe!=b.hoehe) {
    matrix fehler = initMatrix(0, 0);
    return fehler;
  }
  matrix erg = initMatrix(a.breite, a.hoehe);
  for (int i = 0; i < a.hoehe*a.breite; i++) {
    erg.eintraege[i] = a.eintraege[i] - b.eintraege[i];
  }
  return erg;
}

matrix multMatrix(matrix a, matrix b) {
  if (a.breite != b.hoehe) {
    matrix fehler = initMatrix(0, 0);
    return fehler;
  }
  matrix erg = initMatrix(b.breite, a.hoehe);
  for (int xPos=0; xPos<b.breite; xPos++) {
    for (int yPos=0; yPos<a.hoehe; yPos++) {
      double value = 0;
      for (int i=0; i<a.breite; i++) {
        value += getEntryAt(a,i,yPos) * getEntryAt(b,xPos,i);
      }
      setEntryAt(erg, xPos, yPos, value);
    }
  }
  return erg;
}

matrix transposeMatrix(matrix a) {
  matrix erg = initMatrix(a.hoehe, a.breite);
  for (int xPos=0; xPos<a.breite; xPos++) {
    for (int yPos=0; yPos<a.hoehe; yPos++) {
      setEntryAt(erg, yPos, xPos, getEntryAt(a,xPos,yPos));
    }
  }
  return erg;
}

// nach dem Laplaceschen Entwicklungssatz
// Hier: Entwicklung nach der 0-ten Zeile
// Komplexitaet: O(n!)
double detNachZeileEntwickelt(matrix a) {
  if (a.hoehe!=a.breite || a.hoehe==0 || a.eintraege==NULL) return DBL_MAX;
  if (a.hoehe == 1) return getEntryAt(a,0,0); // trivial, Ende der Rekursion
  int multiplikator = 1; //
  double det = 0;
  // Entwicklung nach der ersten Zeile
  for(int i=0; i<a.breite; i++) {
    // neue Matrix erstellen, ohne die 0-te Zeile und die i-te Spalte
    matrix help = initMatrix(a.hoehe-1, a.breite-1);
    int spalte = 0; // Spaltenindex fuer die Matrix "help"
    for(int x=0; x<a.breite; x++) {
      if (x == i) {
        spalte--; // i-te Spalte nicht uebernehmen
      } else {
        for(int y=1; y<a.hoehe; y++) { // Start bei 1, da 0-te Zeile nicht uebernommen wird
          setEntryAt(help, spalte, y-1, getEntryAt(a,x,y));
        }
      }
      spalte++; // naechste Spalte kopieren
    }
    // rekursiver Aufruf
    det = det + multiplikator * getEntryAt(a,i,0) * determinante(help);
    multiplikator = multiplikator * -1;
    freeMatrix(help); // Wichtig: Speicher wieder freigeben!
  }
  return det;
}


// Zuerst wird eine Matrix in eine Dreiecksmatrix mit gleicher Determinante ueberfuehrt:
// Gaußsches Eliminationsverfahren:
//   - Ist A eine Dreiecksmatrix, dann ist das Produkt der Hauptdiagonalelemente die Determinante von A.
//   - Falls B sich aus A ergibt, indem man zwei Zeilen oder Spalten vertauscht, dann ist det(B) = -det(A)
//   - Falls B sich aus A ergibt, indem man ein Vielfaches einer Zeile oder Spalte zu einer anderen Zeile oder Spalte addiert, dann ist det(B) = det(A).
//   - Falls B sich aus A ergibt, indem man ein c-faches einer Zeile oder Spalte bildet, dann ist det(B) = c * det(A).
// Komplexitaet: O(n^3)
double detQuick(matrix a) {
  if (a.hoehe!=a.breite || a.hoehe==0 || a.eintraege==NULL) return DBL_MAX;
  int n = a.hoehe;

  // Determinaten fuer bis zu 4x4-Matrizen per Hand berechnen
  if (a.hoehe == 1) return getEntryAt(a,0,0);
  if (n==2) return a.eintraege[0]*a.eintraege[3]-a.eintraege[1]*a.eintraege[2];
  if (n==3) return a.eintraege[0]*(a.eintraege[4]*a.eintraege[8] - a.eintraege[5]*a.eintraege[7]) +
                   a.eintraege[1]*(a.eintraege[5]*a.eintraege[6]-a.eintraege[3]*a.eintraege[8]) +
                   a.eintraege[2]*(a.eintraege[3]*a.eintraege[7]-a.eintraege[4]*a.eintraege[6]);
  if (n==4) {
    double d = 0;
    d = a.eintraege[0]*(a.eintraege[5]*(a.eintraege[10]*a.eintraege[15]-a.eintraege[11]*a.eintraege[14]) +
        a.eintraege[6]*(a.eintraege[11]*a.eintraege[13]-a.eintraege[9]*a.eintraege[15]) +
        a.eintraege[7]*(a.eintraege[9]*a.eintraege[14]-a.eintraege[10]*a.eintraege[13]));
    d -= a.eintraege[1]*(a.eintraege[4]*(a.eintraege[10]*a.eintraege[15]-a.eintraege[11]*a.eintraege[14]) +
         a.eintraege[6]*(a.eintraege[11]*a.eintraege[12]-a.eintraege[8]*a.eintraege[15]) +
         a.eintraege[7]*(a.eintraege[8]*a.eintraege[14]-a.eintraege[10]*a.eintraege[12]));
    d += a.eintraege[2]*(a.eintraege[4]*(a.eintraege[9]*a.eintraege[15]-a.eintraege[11]*a.eintraege[13]) +
         a.eintraege[5]*(a.eintraege[11]*a.eintraege[12]-a.eintraege[8]*a.eintraege[15]) +
         a.eintraege[7]*(a.eintraege[8]*a.eintraege[13]-a.eintraege[9]*a.eintraege[12])) -
         a.eintraege[3]*(a.eintraege[4]*(a.eintraege[9]*a.eintraege[14]-a.eintraege[10]*a.eintraege[13]) +
         a.eintraege[5]*(a.eintraege[10]*a.eintraege[12]-a.eintraege[8]*a.eintraege[14]) +
         a.eintraege[6]*(a.eintraege[8]*a.eintraege[13]-a.eintraege[9]*a.eintraege[12]));
    return d;
  }

  matrix m = copyMatrix(a);
  double q = 0;
  for(int j=0; j<n; j++) {
    q = m.eintraege[j*n+j];
    if (q == 0) {
      for(int i=j+1; i<n; i++) {
        if (m.eintraege[i*n+j] != 0) {
          for(int k=0; k<n; k++) m.eintraege[j*n+k] += m.eintraege[i*n+k];
          q = m.eintraege[j*n+j];
          break;
        }
      }
    }
    if (q != 0) {
      for(int i=j+1; i<n; i++) {
        if (i != j) {
          q = m.eintraege[i*n+j] / m.eintraege[j*n+j];
          for(int k=0; k<n; k++) m.eintraege[i*n+k] -= q*m.eintraege[j*n+k];
        }
      }
    }
  }
  double p = 1;
  for (int i=0; i<n; i++) {
    p = p * m.eintraege[i*(n+1)];
  }
  freeMatrix(m);
  return p;
}


/*
Es gibt eine Menge Algorithmen zur Berechnung der Determinante einer Matrix:
- Die Entwicklung der Determinante nach Zeilen ist sicherlich eine der einfacher zu verstehenden Varianten,
  aber mit einer Komplexitaet von O(n!) sehr aufwaendig
- detQuick arbeitet in O(n^3)
*/
double determinante(matrix a) {
  return detNachZeileEntwickelt(a);
  //return detQuick(a);
}
