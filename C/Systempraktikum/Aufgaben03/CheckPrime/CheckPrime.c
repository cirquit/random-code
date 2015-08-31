#include <stdlib.h>
#include <stdio.h>
#include <float.h>
#include <stdbool.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>


/* Recursively
 * max => 1*10^6
 */
bool isPrimeRec (unsigned long long num, unsigned long long boundsFrom, unsigned long long boundsTo){
    if (num % boundsFrom != 0 && boundsFrom >= boundsTo){
        return true;
    }
    else if (num % boundsFrom == 0){
        return false;
    }
    else {
        switch (boundsFrom % 2 == 0){
            case false: boundsFrom += 2;
            default   : boundsFrom += 1;
        }
     isPrimeRec(num, boundsFrom, boundsTo);
    }
}


/* Iterativly
 * 1*10^12 in ~ 100s
 */
bool isPrimeIt (unsigned long long num, unsigned long long boundsFrom, unsigned long long boundsTo){
  bool test = true;

  if (num % 2 == 0)          {test = false;}
  if (boundsFrom % 2 == 0)   {boundsFrom++;}
  if (boundsFrom <= 1)   {boundsFrom = 3;}
  for (unsigned long long i = boundsFrom; i < boundsTo; i++){
                if (num % i == 0){
                    test = false;
                    i = boundsTo;
                }   else {i +=1;}
  }
 
    
return test;
}


/*  isPrimeItIO asks the user to input a positive number
 *  after the number has been tested, the result is being shown on the console
 */
void isPrimeItIO(){

    unsigned long long guessed, boundsTo;
    unsigned long long boundsFrom = 2;

    bool result = true;
    bool r1 = false;
    bool r2 = false;
    bool r3 = false;
    bool r4 = false;
    bool r5 = false;
    bool r6 = false;

    printf("Bitte geben sie ihre Zahl ein: ");
    do {scanf("%llu",&guessed);} while (getchar() != '\n');

    int pid = fork();
    if (pid == 0){  // pid == 0 ==> KIND
       r1 = isPrimeIt (guessed, boundsFrom, guessed/7);   // DOES NOT WORK
       printf("\nr1 = %d | boundsFrom = %llu | guessed/7 = %llu \n",r1, boundsFrom, guessed/7);
       printf("KIND 1 : %d\n",getpid());
       exit(0);

    }
    else if (pid > 0){ // pid > 0 ==> ELTERN
       r2 = isPrimeIt (guessed, guessed/7, guessed/6);
       
       waitpid(pid, NULL, 0);  
       printf("ELTERN 1 : %d\n",getpid());

       printf("\nr2 = %d | guessed/7 = %llu | guessed/6 = %llu \n",r2, guessed/7, guessed/6);
       printf ("\nErster Fork ist fertig. R1 = %d und R2: %d\n", r1, r2);
       int pid2 = fork();

                        if (pid2 == 0){  // pid == 0 ==> KIND

                          r3 = isPrimeIt (guessed, guessed/6, guessed/5);
                          printf("\nr3 = %d | guessed/6 = %llu | guessed/7 = %llu \n",r3, guessed/6, guessed/5);
                          exit(0);
                        }
                        else if (pid2 > 0){
                          r4 = isPrimeIt (guessed, guessed/5, guessed/4);
                          printf("\nr4 = %d | guessed/5 = %llu | guessed/4 = %llu \n",r4, guessed/5, guessed/4);
                          
                          waitpid(pid, NULL, 0);  
                          waitpid(pid2, NULL, 0);
                          
                          printf ("\nZweiter Fork ist fertig. R3 = %d und R4: %d\n", r3, r4);
                          int pid3 = fork();
                                                if (pid3 == 0){  // pid == 0 ==> KIND
                                                    r5 = isPrimeIt (guessed, guessed/4, guessed/3);
                                                    printf("\nr5 = %d | guessed/4 = %llu | guessed/3 = %llu \n",r5, guessed/4, guessed/3);
                                                    exit(0);
                                                }
                                                else if (pid3 > 0){
                                                    r6 = isPrimeIt (guessed, guessed/3, guessed/2);
                                                    printf("\nr6 = %d | guessed/3 = %llu | guessed/2 = %llu \n",r6, guessed/3, guessed/2);
                                                    
                                                    waitpid(pid, NULL, 0);  
                                                    waitpid(pid2, NULL, 0);
                                                    waitpid(pid3, NULL, 0);
                                                    
                                                    printf ("\nDritter Fork ist fertig. R5 = %d und R6: %d\n\n", r5, r6);

                                                }
                                                else {printf("\n Es ist ein Fehler aufgetreten! \n");}
                        }
                        else {printf("\n Es ist ein Fehler aufgetreten! \n"); exit(0);}



    }
    else {printf("\n Es ist ein Fehler aufgetreten! \n");}
    
    printf ("R1 = %d | R2 = %d | R3 = %d | R4 = %d | R5 = %d | R6 = %d | \n ", r1,r2,r3,r4,r5,r6);

    result = r1 && r2 && r3 && r4 && r5 && r6;
   
    switch (result) {
        case true : printf ("Die Zahl %llu is eine Primzahl!\n\n", guessed); break;
         default  : printf ("Die Zahl %llu ist keine Primzahl!\n\n", guessed); break;

    }

}
/* Recursivly - 1*10^6
 * Iterativly - 1*10^12 ~ 100s with 6 processes
 */
int main (int argc, char *argv[]){

    printf ("R1 = %d \n", isPrimeIt(11, 2, (11/7)));
    printf ("R2 = %d \n", isPrimeIt(11, (11/7), (11/6)));
    printf ("R3 = %d \n", isPrimeIt(11, (11/6), (11/5)));
    printf ("11/6 = %d und 11/5 = %d \n", (11/6), (11/5));
    printf ("R4 = %d \n", isPrimeIt(11, (11/5), (11/4)));
    printf ("R5 inc => 11/4 = %d und 11/3 = %d \n", (11/4), (11/3));
    printf ("R5 = %d \n", isPrimeIt(11, (11/4), (11/3)));
    printf ("R6 = %d \n", isPrimeIt(11, (11/3), (11/2)));
    clock_t start = clock(), diff;

    isPrimeItIO();

    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf ("Function took %ds and %d milliseconds to complete.", msec/1000, msec%1000);
    return EXIT_SUCCESS;
}