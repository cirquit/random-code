#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

#define BUFFER 50

int main(int argc, char *argv[]){


    char *hw = "Hello World!\n"; // testphrase
    char readBuffer[BUFFER];     // buffer to store the output
    int placeHolder;             // placeholder for read (?) / probably the counter for bytes
    int fd[2];                   // fd[0] is for reading, fd[1] is for writing 
                                 // visually speaking the output of fd[1] is the input of fd[0]
    pipe(fd);                    // creating pipe (?)
    pid_t pid;                   // current prozessID

    if (pid = fork() == -1) { // error if it's negative
        perror ("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {      // if it's zero, it's the child prozess
        close (fd[0]);        // if child wants to recieve data from the parent, it's to close fd[0]
        dup(fd[0]);
        execlp("sort", "sort", NULL);
        write (fd[1], hw, (strlen(hw) + 1)); // sending the teststring throught the output side of pipe
        exit(EXIT_SUCCESS);                  // terminating child prozess
    }
    else {                    // else it's to be the partents prozess
        close (fd[1]);        // if the parent wants to recieve data from the child, it's to close fd[1]
        read(fd[0], readBuffer, sizeof(readBuffer)); // reading a string from the pipe
        printf ("Recieved string %s", readBuffer);
    } 
    exit(EXIT_SUCCESS);
}