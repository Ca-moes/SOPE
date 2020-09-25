// PROGRAMA p10c.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 128
#define SIZE_ARR 10
int main(int argc, char *argv[])
{
  char buf[BUF_LENGTH];
  char *token;
  char *arr[SIZE_ARR];
  int i = 0;
  printf("Write command: ");
  fgets(buf, BUF_LENGTH, stdin);

  token = strtok(buf, " ");
  while (token != NULL)
  {
    arr[i++] = token;
    token = strtok(NULL, " ");
  }

  for (int k = 0; k < i; k++)
  {
    printf("%s\n", arr[k]);
  }
  

  for (int j = 0; j < i; j++)
  {
    if (strchr(arr[j], ';') != NULL || strchr(arr[j], '|') != NULL)
    {
      //TODO: remove first whitespace in comand
      //      add comand to a array of commands
      arr[j][strlen(arr[j]) - 1] = 0;
      printf(" %s\n", arr[j]);
    }
    else{
      //TODO: cat arr[j] para uma string comand
      printf(" %s", arr[j]);
    }
  }

  return 0; // zero é geralmente indicativo de "sucesso"
}