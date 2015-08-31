#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <getopt.h>

#define WRITE 1
#define READ 0

struct point{
  int x;
  int y;
};


char* user_input(){

  char* input = NULL;
  input = malloc (sizeof(char) * 140);
  memset(input, 0, sizeof(input));

  if (!(scanf("%s", input)) || strlen(input) >= 141) {
    printf("Error while parsing user input...\n");
    return user_input();
  }

  return input;

}

void child_handler(int* fd, FILE* file){
  //char* output;
  //output = malloc (sizeof(char) * 140);
  struct point* b = NULL;
  b = malloc (sizeof(struct point));

  close(fd[WRITE]);

  read(fd[READ], b, (sizeof(struct point)));
  printf("Got from parent = %i | %i\n", b -> x, b -> y);
  //fputs(output, file);

  close(fd[READ]);
  fclose(file);
  //free(output);
  exit(EXIT_SUCCESS);
}

int main(int argc, char** argv){

  FILE* file = NULL;
  int fd[2];
  int pid;
  char* input = NULL;
  // A1

  struct point* a = NULL;
  a = malloc (sizeof(struct point));
  a -> x = 1;
  a -> y = 2;

  if (argc <= 1){
    printf("Not enough arguments...\n");
    return -1;
  }

  if ((file = fopen(argv[1], "w+")) == NULL){
    printf("File couldn't be opened...\n");
    return -1;
  }

  // A2

  if (pipe(fd) == -1){
    printf("Error while initialising pipe...\n");
    fclose(file);
    return -1;
  }

  switch (pid = fork()) {
    case -1:
      printf("Error while forking...\n");
      fclose(file);
      return -1;
    break;

    case 0: // child
      child_handler(fd, file);
    break;

    case 1 ... INT_MAX: // parent
      close(fd[READ]);
      //input = user_input();
      write(fd[WRITE], a, (sizeof(struct point)));
      close(fd[WRITE]);
      printf("Send to child = %i | %i\n", a -> x, a -> y);

      wait(NULL);
      free(input);
      printf("Child is done, parent checking out...\n");
      exit(EXIT_SUCCESS);
    break;

    default:
      printf("This should never happen...\n");
      fclose(file);
      return -1;
    break;

  }
  return 0;
}