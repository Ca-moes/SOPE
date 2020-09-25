// PROGRAMA p10a.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 35

int main(int argc, char* argv[])
{
  char buf[BUF_LENGTH];
  char* token;

  printf("Write command: ");
  fgets(buf, BUF_LENGTH, stdin);

  token = strtok(buf, " ");
  while (token != NULL)
  {
    printf("%s\n",token);
    token = strtok(NULL, " ");
  }
  
  return 0; // zero é geralmente indicativo de "sucesso"
}