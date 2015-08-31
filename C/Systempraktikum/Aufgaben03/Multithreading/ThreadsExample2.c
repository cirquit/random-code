
#define _BSD_SOURCE // for usleep - has to be the first thing to declare
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

/* This is our thread function.  It is like main(), but for a thread*/
void *threadFunc(void *arg)
{
    char *str;
    int i = 0;

    str=(char*)arg;

    while(i < 15 )
    {
        usleep(1);
        printf("threadFunc says: %s\n",str);
        ++i;
    }

    return NULL;
}

int main(void)
{
    pthread_t pth;  // this is our thread identifier
    int i = 0;

    pthread_create(&pth,NULL,threadFunc,"foo");

    while(i < 10)
    {
        usleep(1);
        printf("main is running...\n");
        ++i;
    }

    printf("main waiting for thread to terminate...\n");
    pthread_join(pth,NULL);




    

    return 0;
}
