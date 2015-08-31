/* Includes */
#include <unistd.h>     /* Symbolic Constants */
#include <sys/types.h>  /* Primitive System Data Types */ 
#include <errno.h>      /* Errors */
#include <stdio.h>      /* Input/Output */
#include <stdlib.h>     /* General Utilities */
#include <pthread.h>    /* POSIX Threads */
#include <string.h>     /* String handling */
#include <semaphore.h>  /* Semaphore */
#include <stdbool.h>    

/* Does not work with N-Threads, can't figure out how to declare the structs
 * needed as arguments for the n-th thread
 */

#define NUM_THREADS     4

/* struct for thread arguments*/
typedef struct t_args{
    unsigned long long guessed;
    unsigned long long boundsFrom;
    unsigned long long boundsTo;
    int tid;
}t_args;

/* prototype for thread routine */
void handler ( void *ptr );
/* checking for prime */
bool isPrimeIt (unsigned long long num, unsigned long long boundsFrom, unsigned long long boundsTo);

/* global vars */
/* semaphores are declared global so they can be accessed 
   in main() and in thread routine,
   here, the semaphore is used as a mutex */
sem_t mutex;
int counter; /* shared variable */



int 
main(){

    pthread_t thread_a;
    pthread_t thread_b;
    pthread_t thread_c;
    pthread_t thread_d;

    unsigned long long guessed;

    printf ("Please enter the possible (positive) prim value:\n");
    do {scanf("%llu",&guessed);} while (getchar() != '\n');

    clock_t start = clock(), diff;

t_args args1;
       args1.guessed = guessed;
       args1.boundsFrom = 2;
       args1.boundsTo = guessed/5;
       args1.tid = 1;

t_args args2;
       args2.guessed = guessed;
       args2.boundsFrom = guessed/5;
       args2.boundsTo = guessed/4;
       args2.tid = 2;

t_args args3;
       args3.guessed = guessed;
       args3.boundsFrom = guessed/4;
       args3.boundsTo = guessed/3;
       args3.tid = 3;

t_args args4;
       args4.guessed = guessed;
       args4.boundsFrom = guessed/3;
       args4.boundsTo = guessed/2;
       args4.tid = 4;


    sem_init(&mutex, 0, 1);      /* initialize mutex to 1 - binary semaphore */
                                 /* second param = 0 - semaphore is local */
                                 
    pthread_create (&thread_a, NULL, (void *) &handler, (void *) &args1);
    pthread_create (&thread_b, NULL, (void *) &handler, (void *) &args2);
    pthread_create (&thread_c, NULL, (void *) &handler, (void *) &args3);
    pthread_create (&thread_d, NULL, (void *) &handler, (void *) &args4);
    
    /* waiting for them to finish */

    pthread_join(thread_a, NULL);
    pthread_join(thread_b, NULL);
    pthread_join(thread_c, NULL);
    pthread_join(thread_d, NULL);

    sem_destroy(&mutex); /* destroy semaphore */

    /* if every thread returns 1 the counter should be the amount of threads*/
    switch (counter == NUM_THREADS){
        case true: printf ("\nIs prime!\n"); break;
        default  : printf ("\nSorry, not a prime!\n"); break;
    }

    /*returning the passed time*/
    diff = clock() - start;
    int msec = diff * 1000 / CLOCKS_PER_SEC;
    printf ("\nFunction took %ds and %d milliseconds to complete.", msec/1000, msec%1000);
   
    exit(0);
    
}


void
handler (void *ptr){

    /* casting pointer to struct pointer to access the information*/
    t_args *args;
    args = (t_args *) ptr;

    int c_tid = args -> tid; // <==> (*args).tid
    unsigned long long c_guessed = args -> guessed;
    unsigned long long c_boundsFrom = args -> boundsFrom;
    unsigned long long c_boundsTo = args -> boundsTo;

    printf("Thread %d: Calculating...\n", c_tid);

    int x = isPrimeIt(c_guessed, c_boundsFrom, c_boundsTo);

    sem_wait(&mutex);       /* down semaphore */
    
    /* START CRITICAL REGION */
    printf("Thread %d: Previous Counter Value: %d\n", c_tid, counter);
    printf("Thread %d: Adding the Value from my calculation...\n",c_tid);
    counter = counter + x;
    printf("Thread %d: New Counter Value: %d\n", c_tid, counter);
    printf("Thread %d: Shutting down...\n", c_tid);
    /* END CRITICAL REGION */    
    
    sem_post(&mutex);       /* up semaphore */

    pthread_exit(0); /* exit thread */
}


bool
isPrimeIt (unsigned long long num, unsigned long long boundsFrom, unsigned long long boundsTo){
  bool test = true;
  if (num == 1)              {test = false;}
  if (num == 2)              {test = true;}     // bugs when there is no else
  else{
  if (num % 2 == 0)          {test = false;}
  if (boundsFrom % 2 == 0)   {boundsFrom++;}
  if (boundsFrom <= 1)       {boundsFrom = 3;}
  
  for (unsigned long long i = boundsFrom; i < boundsTo; i++){
                if (num % i == 0){
                    test = false;
                    i = boundsTo;
                }   else {i +=1;}
  }
}
 return test;
}

