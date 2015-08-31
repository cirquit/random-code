#include <stdlib.h>
#include <unistd.h>
#include  <stdio.h>
#include <sys/wait.h>


int main () 
{ 
  int pid; 
  printf("\nHello World \n"); 
  pid = fork(); 

  if(pid != 0) 
    printf("\nI'm the Father and my son's PID is %d\n",pid); 
  else 
    printf("\nI'm the Son\n"); 

  printf("\nGoodbye Cruel World\n"); 
}




/*int main () 
{ 
  int pid, status; 

  if(fork()) 
    { 
      printf("I'm the Father, and waiting\n"); 
      pid = wait(&status); 
      printf("I'm the Father :n - my son's PID is %dn \n- my son's exit status is %d\n", pid, status); 
    }else{ 
      printf("I'm the Son, and sleepingn\n"); 
      sleep(1); 
      printf("I'm the Son, and exiting\n"); 
      exit(0); 
    } 

  printf("Goodbye Cruel World\n"); 
}*/


/*int main () 
{ 
  printf("Calling execl...\n\n"); 
  execl("/bin/cat", "cat", "./MyFork.c", NULL); 
  printf("Useless call to printf"); 
}
*/

// ./MyFork /bin/echo aaaa bbbbb ccccc 
/*int main (int argc, char * args[]) 
{ 
  if(argc < 3) 
    { 
      printf("Syntax : Filename Shellcommand arg1 arg2.."); 
      exit(EXIT_FAILURE); 
    }else{ 
      int i; 
      char * command = args[1], * arg; 
      for(i = 2; i < argc; i++) 
        { 
          arg = args[i]; 
          if(!fork()) 
            execl(command, "", arg, NULL); 
        } 
      for(i = 2; i < argc; i++) 
        { 
          int status; 
          wait(&status); 
        } 
      exit(EXIT_SUCCESS); 
    } 
}*/

int main (int argc, char *args[]){

    int pid, i, j;

    pid = fork();
       //prozessid // 2 prozesses are being generated    
    if (pid == 0){  // pid == 0 ==> KIND
        printf ("\nHey ich bin der Kindprozess und meine PID ist %i!\n", getpid());
        sleep(1);   // 1s
    }
    else if (pid > 0){ // pid > 0 ==> ELTERN
         printf ("\nHey ich bin der Elternprozess und meine PID ist %i!\n", getpid());
         sleep(1);  // 1s
         
    }
    else { // pid is negative ==> ERROR
        printf("\n Es ist ein Fehler aufgetreten! \n");
    }
    exit(EXIT_SUCCESS);
}