#include <stdlib.h>
#include <stdio.h>  /* for printf */
#include <string.h> /* for strlen */
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char *argv){

    int n;
    int fd[2];
    char buf[1025];
    char *data = "hello... this is sample data";

    pipe(fd);
    close(fd[0]);
    write(fd[1], data, strlen(data));
    close(fd[1]);
    if ((n = read(fd[0], buf, 1024)) >= 0) {
        buf[n] = 0; /* terminate the string */
        printf("read %d bytes from the pipe: \"%s\"\n", n, buf);
    }   
    else
        perror("read");
    exit(0);
}