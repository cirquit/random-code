#include <float.h>
#include <stdbool.h>

typedef struct {
  double *eintraege;
  unsigned int breite;
  unsigned int hoehe;
} matrix;

/*
Initialisiert eine neue Matrix:
- reserviert lediglich den notwendigen Speicher
*/
matrix initMatrix(unsigned int breite, unsigned int hoehe);

/*
Initialisiert eine neue Matrix:
- reserviert den notwendigen Speicher
- befuellt die Matrix mit 0
*/
matrix initMatrixZero(unsigned int breite, unsigned int hoehe);

/*
Initialisiert eine neue Matrix:
- reserviert den notwendigen Speicher
- befuellt die Matrix mit Zufallszaheln
*/
matrix initMatrixRand(unsigned int breite, unsigned int hoehe);

/*
Kopiert eine Matrix und gibt die Kopie zurueck
*/
matrix copyMatrix(matrix toCopy);

/*
"Zerstoert" eine Matrix
- gibt reservierten Speicher wieder frei
- setzt alle Werte auf NULL bzw. "0"
*/
void freeMatrix(matrix toDestroy);

/*
Gibt den Eintrag der Matrix an der Stelle (xPos, yPos) zurueck, DBL_MAX im Fehlerfall
*/
double getEntryAt(matrix a, unsigned int xPos, unsigned int yPos);

/*
Setzt den Eintrag der Matrix an der Stelle (xPos, yPos)
Rueckgabe: true, false im Fehlerfall
*/
bool setEntryAt(matrix a, unsigned int xPos, unsigned int yPos, double value);

/*
Gibt eine Matrix auf der Kommandozeile aus
*/
void prettyPrint(matrix a);

/*
Addiert zwei Matrizen
Rueckgabe:
- Ergebnis der Addition in neu erzeugter Matrix
- Matrix der Groesse "0" im Fehlerfall
*/
matrix addMatrix(matrix a, matrix b);

/*
Subtrahiert zwei Matrizen:
Rueckgabe: "a - b"
- Ergebnis der Subtraktion in neu erzeugter Matrix
- Matrix der Groesse "0" im Fehlerfall
*/
matrix subMatrix(matrix a, matrix b);

/*
Multipliziert zwei Matrizen:
Rueckgabe: "a * b"
- Ergebnis der Multiplikation in neu erzeugter Matrix
- Matrix der Groesse "0" im Fehlerfall
*/
matrix multMatrix(matrix a, matrix b);

/*
Transponiert eine Matrix:
Rueckgabe: "a^T"
*/
matrix transposeMatrix(matrix a);

/*
Gibt die Determinante der Matrix a zurueck, DBL_MAX im Fehlerfall
*/
double determinante(matrix a); // ein einfacher Algorithmus reicht fuer kleine Matrizen
double detQuick(matrix a);     // wer moechte kann ein effizientes Verfahren implementieren
