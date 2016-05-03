#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** words(char* input)
{
  int i             = 0;
  int curWord       = 0;
  int curWordStart  = 0;
  int curWordLength = 0;
  char** result = (char*) malloc(sizeof(char*) * (curWord + 1));

  while(input[i] != '\0')
  {
    if(input[i] != ' ')
    {
      i++;
      curWordLength++;
    }
    else
    {
      realloc(result[curWord], sizeof(char) * (curWordLength + 1));
      strcpy(result[curWord], substring(curWordStart, curWordLength, input));

      i++;
      curWord++;
      curWordLength = 0;
      curWordStart  = i;
      realloc(result, sizeof(char*) * (curWord + 1));
    }
  }
}

const char* substring(int start, int end, char* input)
{
  int strlength = end - start;
  const char* result = (char*) malloc(sizeof(char) * (strlength + 1));

  for(int i = start; i <= end; i++)
  {
    result[i - start] = input[i];
  }

  result[end + 1] = '\0';

  return result;
}


int main(int argc, char const *argv[])
{

  char t0[] = "";                 // 0
  char t1[] = "    ";             // 0
  char t2[] = "hello";            // 1
  char t3[] = "hello world";      // 2
  char t4[] = "hello world !";    // 3
  char t5[] = "hello  world !";   // 3
  char t6[] = "hello  world ! ";  // 3

  printf("%s\n", words(t2));

  return 0;
}












