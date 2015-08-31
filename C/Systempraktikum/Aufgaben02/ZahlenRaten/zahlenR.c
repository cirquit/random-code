#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define NAMESPACE 20
#define SCORELL   10// SCORELISTLENGTH

typedef struct {
    int score;
    char name [NAMESPACE];
}   ScoreNname;



// generating random numbers
int irand( int a, int e){
    double r = e - a + 1;
    return a + (int)(r * rand()/(RAND_MAX+1.0));
}


// copied BubbleSort (added 2D-functionality)
ScoreNname* bubbleSort(ScoreNname a[], int array_size){

 int i, j, tempI;
 char tempC [NAMESPACE];

 ScoreNname temp;

    for (i = 0; i < (array_size - 1); ++i) {
         for (j = 0; j < array_size - 1 - i; ++j )      {
              if (a[j].score > a[j+1].score)           {
                  temp = a[j+1];
                  a[j+1] = a[j];
                  a[j] = temp;
                 
              }
         }
    }
return a; 
}   



/* reading amount (SCOREELL) lines from a .txt-file
   - line is the current line (string)

   - allNames is an array where I save all the information about the scoreboard and
     (SCORELL + 1) to get some space for the new name to be able to sort it

   - counter is the index from the allNames array (int)
*/
ScoreNname* readLog (){

    char *temp;
    FILE *file = fopen("listOfTheVeryBest.txt","r");

    int counter = 0;   // arraycounter
    char line [128]; // linelength

    ScoreNname *allNames = malloc (sizeof (ScoreNname) * (SCORELL+1)); // allocating SCORELL+1 spaces to append the new name 


    while (fgets ( line, sizeof line, file ) != NULL && counter < (SCORELL)){ // reading a line till
         sscanf (line, "%i = %s", &allNames[counter].score, allNames[counter].name);    // "(int) = (string)"
         counter++;                                                      // counting up to match array
      }

    fclose ( file );                                     // closing handle

    return allNames;
}



ScoreNname* sortNdropLog (ScoreNname allNames[], ScoreNname newName){

allNames[SCORELL] = newName;    // adding the newName to the unsorted array
/*
for (int counter = 0; counter < SCORELL; counter ++){
printf ("beforeSort : %i = %s \n",allNames[counter].score, allNames[counter].name);
}

*/
allNames = bubbleSort (allNames, SCORELL+1);    

/*for (int counter = 0; counter < SCORELL; counter ++){
printf ("afterSort : %i = %s \n",allNames[counter].score, allNames[counter].name);
}*/


return allNames;

}


void printLog (ScoreNname allNames[]){

FILE * file = fopen("listOfTheVeryBest.txt","w");


    for (int counter = 0; counter < SCORELL+1; counter++){
       fprintf(file,"%i = %s\n", allNames[counter].score, allNames[counter].name);
    }
    

fclose(file);
}

void addNameToScore (ScoreNname newName){

    printLog (sortNdropLog (readLog(), newName));

}




void askForSave (int counter){

   char yorN;

   ScoreNname newName;

   newName.score = counter;

    printf("Wollen sie ihr Ergebnis mit %i Versuchen speichern? (Y/N) ", counter);
    do {scanf("%c",&yorN);} while (getchar() != '\n');

switch (yorN) {
    case 'Y': printf("Wollen heißen sie?");
              do {scanf("%s", newName.name);} while (getchar() != '\n');
              addNameToScore (newName);
              break;
    case 'y': printf("Wollen heißen sie?");
              do {scanf("%s", newName.name);} while (getchar() != '\n');
              addNameToScore (newName);
              break;
    case 'N': printf ("Danke, dass sie das Spiel gekauft haben!"); break;
    case 'n': printf ("Danke, dass sie das Spiel gekauft haben!"); break;
    default : printf ("Keine gültige Antwort. "); break;
}
}


void checkAnswer (int toguess, int counter){

int guessed;

    printf("Bitte geben sie ihre Zahl ein: ");
    do {scanf("%i",&guessed);} while (getchar() != '\n');

    if (guessed < toguess)        {printf("Die Zahl ist größer!\n"); checkAnswer (toguess,counter+1);}
      else if (guessed > toguess) {printf("Die Zahl ist kleiner!\n"); checkAnswer (toguess,counter+1);}
    else                          {printf("Du hast die Zahl erraten!\n"); askForSave(counter); }
}




int main(int argc, char *argv[]){

    int counter = 0;

    srand(time(0));
    checkAnswer ((irand(0,100)),0);

    return EXIT_SUCCESS;
}