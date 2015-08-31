#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 5

// defining struct matrix
struct matrix {
  int inc [SIZE][SIZE];
  unsigned int row;
  unsigned int column;
} mA, mB, mC;



// generating random numbers
int irand( int a, int e){
    double r = e - a + 1;
    return a + (int)(r * rand()/(RAND_MAX+1.0));
}

// filling matrix with generated numbers
struct matrix fillMatrix (struct matrix mA) {

srand(time(0));             // generating seed for the rng

    for (int row = 0; row < mA.row; row++){
        for(int column = 0; column < mA.column; column++){
            mA.inc[row][column] = irand(0,9);
        }
    }

    return mA;

}

// defining the show instance for struct matrix
void showMatrix (struct matrix mA){


    for (int row = 0; row < mA.row; row++){
        printf ("\n");
        for(int column = 0; column < mA.column; column++){
            int x =  mA.inc[row][column];
            printf ("%i ",x); 
        }
    }
    printf ("\n\n");

}

// defining multiplying for two struct matrix's
struct matrix multiplyMatrix (struct matrix mA, struct matrix mB, int n){
     
mC.row = n; //initializing
mC.column = n;

        for (int row = 0; row < n; row++) {
             for (int col = 0; col < n; col++) {
                    // Multiply the row of A by the column of B to get the row, column of product.
                    for (int inner = 0; inner < n; inner++) {
                        mC.inc[row][col] += mA.inc[row][inner] * mB.inc[inner][col];
                    }
            }
        }

return mC;

}

int main(int argc, char *argv[]){

    mA.row = SIZE;
    mA.column = SIZE;
    mB.row = SIZE;
    mB.column = SIZE;

    mA = fillMatrix (mA);
    mB = fillMatrix (mB);

    showMatrix (mA);
    showMatrix (mB);

    showMatrix (multiplyMatrix (mA, mB, SIZE));

return 0;


}









