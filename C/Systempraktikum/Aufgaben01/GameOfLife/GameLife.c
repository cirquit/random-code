#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


#define TIME_TO_WAIT 0.1 /* wait for one second */
#define SIZE 37// real size is always SIZE - 2 because of the neighbours check

// defining struct Matrix
struct Matrix {
  char inc [SIZE][SIZE];
  unsigned int row;
  unsigned int column;
} platform,cplat;

// defining tuple to access coords #### maybe saving the condition of the platform here
struct Coords {
    int row;
    int column;
    // char c;
} c0,c1,c2,c3,c4,c5,c6,c7,c8,tempC; // c8 is the current cell

// defining storage for all neighbours
struct Neighbours {
  struct Coords field[9];
} nextTo;

// generating random numbers
int irand( int a, int e){
    double r = e - a + 1;
    return a + (int)(r * rand()/(RAND_MAX+1.0));
}

// encoding 0,1 and 2 to cell counterparts
char rndToCell (int i) {

  char c;
      switch (i) {
         case 1:   c = 'O'; break; // living cell
         case 2:   c = '.'; break; // dead cell
         default : c = '/'; break; // space is empty
      }
  return c;
}

// translating O X and / to number counterparts
int cellToRnd (char c) {

  int i;
      switch (c) {
         case 'O': i = 1; break; // living cell
         case '.': i = 2; break; // dead cell
         default : i = 0; break; // space is empty
      }
  return i;
}


// returning all neighbours of the square
struct Neighbours getNeighbours (struct Coords sq){

c0.row = sq.row-1;
c0.column = sq.column-1;
nextTo.field [0]= c0;

c1.row = sq.row-1;
c1.column = sq.column;;
nextTo.field [1]= c1;

c2.row = sq.row-1;
c2.column = sq.column+1;
nextTo.field [2]= c2;

c3.row = sq.row;
c3.column = sq.column-1;
nextTo.field [3]= c3;

c4.row = sq.row;
c4.column = sq.column+1;
nextTo.field [4]= c4;

c5.row = sq.row+1;
c5.column = sq.column-1;
nextTo.field [5]= c5;

c6.row = sq.row+1;
c6.column = sq.column;
nextTo.field [6]= c6;

c7.row = sq.row+1;
c7.column = sq.column+1;
nextTo.field [7]= c7;

c8.row = sq.row;
c8.column = sq.column;
nextTo.field [8] = c8;

return nextTo;

}

char followRules (struct Neighbours neigh){
    int counter = 0;
    tempC = neigh.field[8];
    char temp = platform.inc[tempC.row][tempC.column];
    if (temp == '/') return '/';
    else {
         for (int i = 0; i < 8; i++){                 // filling the board with empty places
             tempC = neigh.field[i];
             if (platform.inc[tempC.row][tempC.column] == 'O') counter +=1;
             else counter +=0;

          }


         if (counter == 3 && temp == '.') return 'O';
          else if ((counter <= 1 || counter >= 4) && temp == 'O') return '.';
          else if ((counter == 2 || counter == 3) && temp == 'O') return 'O';
         else return '.'; // F for failure
        }

}


int calDensity (float i){
    float x = i / 100;
    return (SIZE-2)*(SIZE-2)*x;
}


struct Matrix iterateMatrix (struct Matrix plat){

        for (int row = 1; row < plat.row-1; row++){
         for(int column = 1; column < plat.column-1; column++){

            tempC.row = row;
            tempC.column = column;
            //char x =  plat.inc[row][column];
            nextTo = getNeighbours (tempC);
            char x = followRules (nextTo);
            plat.inc[row][column] = x;

         }
    }

    return plat;
}


struct Matrix fillMatrix (struct Matrix plat, int livingCells){

srand(time(0));             // generating seed for the rng
int crow;                   // current row for generating living cells
int ccolumn;                // current column for generating living cells

   for (int row = 1; row < plat.row-1; row++){                 // filling the board with empty places
        for(int column = 1; column < plat.column-1; column++){
            plat.inc[row][column] = '.';
        }
    }
//  plat.inc[SIZE][SIZE] = {'/'}               // filling the board with empty places (not working)

    for (int i = 0; i < livingCells; i++){      // generating living cells
            do {
                crow = irand(1,(SIZE-2));
                ccolumn = irand(1,(SIZE-2));
            } while (plat.inc[crow][ccolumn] == 'O');   // don't override already placed bacteria

        plat.inc[crow][ccolumn] = 'O'; // and placing them onto the board
    }




/*    for (int row = 1; row < plat.row-1; row++){        // filling the board exactly one line
            plat.inc[row][4] = 'O';
        }

*/
return plat;

}

void showMatrix (struct Matrix plat){

    for (int row = 1; row < plat.row-1; row++){
        printf ("\n");
        for(int column = 1; column < plat.column-1; column++){
            char x =  plat.inc[row][column];
            printf ("%c  |",x);
        }
    }
    printf ("\n");
}

void showRealMatrix (struct Matrix plat){

    for (int row = 0; row < plat.row; row++){
        printf ("\n");
        for(int column = 0; column < plat.column; column++){
            char x =  plat.inc[row][column];
            printf ("%c  |",x);
        }
    }
    printf ("\n");
}

bool compareMatricies (struct Matrix m1, struct Matrix m2){

bool isSame = true;


    for (int row = 1; row < m1.row-1; row++){
        for(int column = 1; column < m1.column-1; column++){
            if (m1.inc[row][column] == m2.inc[row][column]){}
             else {
                isSame = false;
                column = m1.column-1;
                row    = m1.row-1;
            }
        }
    }
return isSame;

}



int main(int argc, char *argv[]){


    int size; // not working, because of no support with unknown allocation at compile time with arrays in structs
    float density; // density of the platform
    int livingCells; // amount of calculated living cells based on the density and size (size*size*density/100)
    int steps = 1;
    platform.row = SIZE;
    platform.column = SIZE;

    cplat.row = SIZE;
    cplat.column = SIZE;
/*
    printf("Bitte geben Sie die Größe des Spielfelds (N x N) ein : "); //not working yet
    do {scanf("%i",&size);} while (getchar() != '\n');
*/
    printf("Bitte geben Sie die Dichte des Spielfelds (in Prozent) ein : ");
    do {scanf("%f",&density);} while (getchar() != '\n');

    livingCells = calDensity (density);
    printf("Returning number of living Cells %i", livingCells);     // calculating amount of cells

    platform = fillMatrix (platform, livingCells);  // filling matrix with random positioning of cells
    showMatrix (platform);                          // showing "zero" step






    clock_t last = clock();                         // timer function
    while(1) {                                      // wait one second
    clock_t current = clock();
    if (current >= (last + TIME_TO_WAIT * CLOCKS_PER_SEC)) {


         printf ("\nNach dem %i Schritt(en):\n", steps);    // counting steps
         steps++;
         cplat = platform;                                  // setting temp platform for check
         platform = iterateMatrix (platform);               // setting new platform

          /*If it's the same after two steps, stop it*/
          if (compareMatricies (platform, cplat)) {printf ("\nDie Matrix verändert sich nicht mehr!\n\n"); return EXIT_SUCCESS;}
          showMatrix (platform);
          // else - go on
        last = current;
    }
}
}

