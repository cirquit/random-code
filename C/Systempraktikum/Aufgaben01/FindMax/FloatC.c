#include <stdio.h>
#include <stdlib.h>



float compare (float a, float b){
    if (a > b) return a;
               else return b; 
}

float compareArr (float arr[], int c){

    float max = 0.00;

    for (int i = 0; i < c; i++){
          max = compare (arr[i], max);
      }

    return max;

}


int main (int argc, char *argv[]){


static char fileName [1024];

float max = 0;     // returning value

int counter = 0;   // arraycounter

float arr [10000]; // arraylength

FILE *file;        // filehandle

char line [ 128 ]; // linelength

   if(argc < 2) {   // If there is no second argument, ask for file name
      printf("Bitte geben sie den Dateinamen ein: ");
      do {scanf("%s", &fileName[0]);} while (getchar() != '\n');
      file=fopen(fileName, "r");
   }
   else {           // If the filename is given
      file=fopen(argv[1], "r");
    }

    if (file == NULL) {  // If the filehandle is broken -> error
        return EXIT_FAILURE;
    }

    while ( fgets ( line, sizeof line, file ) != NULL ){ // reading a line


         arr[counter] = atof(line);                      // from string to float
         counter++;                                      // counting up to match array
      }

    fclose ( file );                                     // closing handle

    max = compareArr (arr, 10000);                       // comparing the array in O(n)
    printf ("Die größte Floatzahl lautet: %0.2f", max);  // returning the max float value with two floating points

   return EXIT_SUCCESS;
}



