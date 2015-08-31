#include <stdio.h>
#include <stdlib.h>



// allocating the memory for an 2D array
int** allocMem (int row, int column){

    int **array = malloc (row * sizeof(char*));     // array[0],array[1],array[2]...
    //**array = realloc (row * sizeof(char*) + 1);
    for (int i = 0; i < row; i++){
        array[i] = malloc ((sizeof(char)) * column); // array[0][0],array[0][1],array[0][2]...
    }
        //free(array);                                  don*t forget to free array after you're done with it
    return array;
}


int main (int argc, char *argv[]){


int **array = allocMem(3,3);                        // allocating 3 x 3 array

for(int j = 0; j < 3; j++){
    for(int l = 0; l < 3; l++){
        array[j][l] = (j+l);}                       // filling it
}


for(int j = 0; j < 3; j++){                         
        printf("\n");
    for(int l = 0; l < 3; l++){
        printf ("%i ",array[j][l]);                 // printing it
    }
}

for (int i = 0; i < 3; i++){                        // freeing & printing 2nd dimension

printf("Pointer : %p" , array[i]);
free(array[i]);

}

printf ("EndPointer: %p", array);                   // freeing 1st dimension

free (array);



return EXIT_SUCCESS; }

/*int i = 10;

int *p = malloc (i*sizeof(int));

for(int j = 0; j < 10; j++){
    p[j] = 1;
}

for(int l = 0; l < 10; l++){
    printf("%i\n", p[l]);
}*/



