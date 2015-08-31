#include <stdlib.h>
#include <stdio.h>  /* for printf */
#include <string.h> /* for strlen */
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

bool checkForPrimeIt (unsigned long long num, unsigned long long boundsFrom, unsigned long long boundsTo){
  bool test = true;
  if (boundsFrom % 2 == 0){
      boundsFrom++;
  }
  else {boundsFrom = boundsFrom;}

      for (unsigned long long i = boundsFrom; i < boundsTo; i++){
            if (num % i == 0){
                test = false;
                i = boundsTo;
            }   else {i +=1;}
      }
return test;
}
int main(int argc, char *argv){

    int fd[2]; // pipe
    int i;     // 0 is not a prime // 1 is a prime
    int test;

    int bytes; // count of bytes for debug

    pipe(fd);  // initialising pipe

    bool result;

    unsigned long long guessed;
    

    printf("Bitte geben sie ihre Zahl ein: ");
    
    do {scanf("%llu",&guessed);} while (getchar() != '\n');

    if (guessed % 2 == 0) {result = false;} 

    else {
        int pid = fork();
        if (pid == 0){  // KIND
            switch (checkForPrimeIt(guessed, 2, guessed/4)){
              case true: i = 1; write(fd[1], &i, sizeof(i)); //close(fd[1]);
                          printf ("Kind 1 sagt es ist %d\n", i); exit(0);    // isPrime
              default  : i = 0; write(fd[1], &i, sizeof(i)); //close(fd[1]);
                          printf ("Kind 1 sagt es ist %d\n", i); exit(0);   // isNotPrime
            }
        }
        else if (pid > 0){ // ELTERN
          waitpid(pid, NULL, 0);
          read(fd[0], &test, sizeof(test)man);
          printf ("Eltern sagt der Buffer ist %d\n", test);
            switch (test) {
              case 1  : result = checkForPrimeIt(guessed, guessed/4, guessed/2); break;
              default : result = false; break;
            }
        }
        else {
            printf ("error");
            result = false;
            exit(0);
        }

    }

    switch (result) {
        case true : printf ("Die Zahl %llu is eine Primzahl!\n", guessed); break;
         default  : printf ("Die Zahl %llu ist keine Primzahl!\n", guessed); break;

    }

    exit(0);
}
