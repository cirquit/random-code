#include "matrixBib.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <float.h>
#include "myFirstBib.a"

// generating random numbers
int irand( int a, int e){
    double r = e - a + 1;
    return a + (int)(r * rand()/(RAND_MAX+1.0));
}

// works
matrix initMatrix(unsigned int breite, unsigned int hoehe){
    matrix m1;
    m1.eintraege = malloc (breite * sizeof(double*));
    for (int i = 0; i < breite; i++){
        m1.eintraege[i] = malloc (sizeof(double) * hoehe);
    }
    m1.breite    = breite;
    m1.hoehe     = hoehe;
return m1;
}

// works
matrix initMatrixRand(unsigned int breite, unsigned int hoehe){
    matrix m1 = initMatrix(breite, hoehe);
    srand(time(0));
    for (int i = 0; i < m1.breite; i++){
        for (int j = 0; j < m1.hoehe; j++){
            m1.eintraege[i][j] = (double) irand(1,9);
        }
    }
return m1;
}

//works
matrix initMatrixZero(unsigned int breite, unsigned int hoehe){
    matrix m1 = initMatrix(breite, hoehe);

    for (int i = 0; i < breite; i++){
        for (int j = 0; j < hoehe; j++){
            m1.eintraege[i][j] = 1;
        }
    }
return m1;
}

//works
matrix copyMatrix(matrix toCopy){
    matrix m1 = initMatrix(toCopy.breite, toCopy.hoehe);
    for (int i = 0; i < toCopy.breite; i++){
        for (int j = 0; j < toCopy.hoehe; j++){
            m1.eintraege[i][j] = toCopy.eintraege[i][j];
        }
    }
    return m1;
}

// don't even know how to test this
void freeMatrix(matrix toDestroy){
    for (int i = 0; i < toDestroy.hoehe; i++){
            free(toDestroy.eintraege[i]);
    }
    free(toDestroy.eintraege);
}

// works
double getEntryAt(matrix a, unsigned int xPos, unsigned int yPos){
    if (a.breite < xPos || a.hoehe < yPos || xPos < 0 || yPos < 0) {
        return DBL_MAX;
    }
    else {return a.eintraege[xPos][yPos];}
}

//works
bool setEntryAt(matrix a, unsigned int xPos, unsigned int yPos, double value){
    if (a.breite < xPos || a.hoehe < yPos) {
        return false;
    }
    else {a.eintraege[xPos][yPos] = value; return true;}
}


// works
void prettyPrint(matrix a){
    for (int i = 0; i < a.breite; i++){
        printf ("\n");
        for (int j = 0; j < a.hoehe; j++){
            printf ("%f  |", a.eintraege[i][j]);
        }
    }
}

// works
matrix addMatrix(matrix a, matrix b){

    if (a.breite == b.breite && a.hoehe == b.hoehe){
   
        matrix m1 = initMatrix(a.breite, a.hoehe);
        for (int i = 0; i < a.breite; i++){
            for (int j = 0; j < a.hoehe; j++){
                 m1.eintraege[i][j] = a.eintraege[i][j] + b.eintraege[i][j];
            }
        }
    return m1;
    }
    else {matrix m1 = initMatrix(0, 0); return m1;}
}

matrix subMatrix(matrix a, matrix b){

    if (a.breite == b.breite && a.hoehe == b.hoehe){
   
        matrix m1 = initMatrix(a.breite, a.hoehe);
        for (int i = 0; i < a.breite; i++){
            for (int j = 0; j < a.hoehe; j++){
                 m1.eintraege[i][j] = a.eintraege[i][j] - b.eintraege[i][j];
            }
        }

    freeMatrix(a);
    freeMatrix(b);
    return m1;
    }
    else {matrix m1 = initMatrix(0, 0); return m1;}
}

// works
matrix multMatrix(matrix a, matrix b){

if (a.breite == b.hoehe){

  matrix m1 = initMatrix(b.breite, a.hoehe);
  for (int xPos=0; xPos<b.breite; xPos++) {
    for (int yPos=0; yPos<a.hoehe; yPos++) {
      for (int i=0; i<a.breite; i++) {
        m1.eintraege[xPos][yPos] += a.eintraege[i][yPos] * b.eintraege[xPos][i];
      }
    }
  }

}

else {
    matrix m1 = initMatrix (0,0);
    return m1;
}
}
// propably working (dunno about the math tho)
matrix transposeMatrix(matrix a){
    matrix m1 = initMatrix (a.hoehe, a.breite);
    for (int i = 0; i < a.breite; i++){
            for (int j = 0; j < a.hoehe; j++){
                 m1.eintraege[j][i] = a.eintraege[i][j];
            }
        }

return m1;
}

// works
double getFakPos(matrix a, int xPos, int yPos, int counter){
    double erg = 1;
    for (int i = 0; i < counter; i++){
        erg = erg * a.eintraege[xPos+i][yPos+i];
    }
    return erg;
}
// works
double getFakNeg(matrix a, int xPos, int yPos, int counter){
    double erg = 1;
    for (int i = 0; i < counter; i++){
        erg = erg * a.eintraege[xPos-i][yPos+i];
    }
    return erg;
}
// works
matrix expandMatrix (matrix a){
    matrix m1 = initMatrix (a.breite, a.hoehe + a.hoehe -1); // breite und hoehe vertauscht

    for (int i = 0; i < a.breite; i++){
        for (int j = 0; j < a.hoehe; j++){
            m1.eintraege[i][j] = a.eintraege[i][j];
        }
    }


    for (int i = 0; i < m1.breite; i++){
        for(int j = a.hoehe; j < m1.hoehe;j++){
            m1.eintraege[i][j] = a.eintraege[i][j-a.hoehe];
        }
    }
/*    m1.eintraege[0][a.hoehe] = a.eintraege[0][0];
    m1.eintraege[0][a.hoehe+1] = a.eintraege[0][1];

    m1.eintraege[1][a.hoehe] = a.eintraege[1][0];
    m1.eintraege[1][a.hoehe+1] = a.eintraege[1][1];

    m1.eintraege[2][a.hoehe] = a.eintraege[2][0];
    m1.eintraege[2][a.hoehe+1] = a.eintraege[2][1];
*/

return m1;

}
// very inefficient - maybe correct with modulo of length, so we don't have to expand
double determinante(matrix a){
    if (a.breite == 2 && a.hoehe == 2){return a.eintraege[0][0] * a.eintraege[1][1] - a.eintraege[1][0] * a.eintraege[0][1];}
    else {
        matrix exA = expandMatrix(a);
        double pos = 0;
        double neg = 0;
/*    printf ("%f\n" , getFakPos(m7, 0, 0, m7.breite));
    printf ("%f\n" , getFakPos(m7, 0, 1, m7.breite));
    printf ("%f\n" , getFakPos(m7, 0, 2, m7.breite));

    printf ("%f\n" , getFakNeg(m7, 2, 0, m7.breite));
    printf ("%f\n" , getFakNeg(m7, 2, 1, m7.breite));
    printf ("%f\n" , getFakNeg(m7, 2, 2, m7.breite));    */
           for (int i = 0; i < exA.breite; i++){
                pos += getFakPos(exA, 0, i, exA.breite);
            }
             for (int i = 0; i < exA.breite; i++){
                neg -= getFakNeg(exA, exA.breite-1, i, exA.breite);
            }
    return pos + neg;
    }
}

/*
int main (int argc, char *argv[]){


//###############################################
    printf ("\nThis is initMatrix(4,4).\n");
    matrix m1 = initMatrix(4,4);
    prettyPrint (m1);
//###############################################

    printf ("\n\nThis is setEntryAt(m1, 1, 1, 2).\n");
    bool x = setEntryAt(m1, 1, 1, 2);    
    prettyPrint (m1);
    printf ("\n\n %d -> 1 = true / 0 = false", x);

//###############################################

    printf ("\n\nThis is getEntryAt(m1, 1, 1).\n");
    double y = getEntryAt(m1, 1, 1);    
    printf ("\n %f", y);
//###############################################

    printf ("\n\nThis is initMatrixRand(3,3)\n ");

    matrix m2 = initMatrixRand(3,3);
    prettyPrint (m2);

//###############################################

    printf ("\n\nThis is initMatrixZero(3,3) (currently 1 for test cases)\n ");

    matrix m3 = initMatrixZero(3,3);
    prettyPrint (m3);

//###############################################

    printf ("\n\nThis is copyMatrix(m2) (from initMatrixRand(3,3))\n ");
    prettyPrint (copyMatrix(m2));

//###############################################

    printf ("\n\nThis is addMatrix(m2,m2) (from initMatrixRand(3,3)\n ");
    matrix m4 = addMatrix(m2,m2);
    prettyPrint (m4);

//###############################################


    printf ("\n\nThis is subMatrix(m4,m2) (m4 = add (m2,m2))\n ");
    prettyPrint (subMatrix(m4,m2));

//###############################################

    printf ("\n\nThis is transposeMatrix() (2,3) -> (3,2)\n ");
    matrix m5 = initMatrixRand(2,3);
    prettyPrint (m5);
    printf ("\n\n");
    prettyPrint (transposeMatrix(m5));

//###############################################

    printf ("\n\nNew random matrix (3,3)\n");
    matrix m6 = initMatrixRand(3,3);
    prettyPrint (m6);
    printf ("\n\nExpanded random matrix \n");
    matrix m7 = expandMatrix(m6);
    prettyPrint (expandMatrix(m6));
    double bam = determinante(m6);
    printf ("\n\nThis is the determinante: %f ", bam);
}
*/