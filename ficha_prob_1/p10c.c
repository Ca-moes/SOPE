// PROGRAMA p10b.c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_LENGTH 35
#define SIZE_ARR 5
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

  for (int j = 0; j < i; j++)
  {
    if (strchr(arr[j], ';') != NULL || strchr(arr[j], '|') != NULL)
    {
      arr[j][strlen(arr[j]) - 1] = 0;
      printf(" %s\n", arr[j]);
    }
    else
      printf(" %s", arr[j]);
  }

  return 0; // zero é geralmente indicativo de "sucesso"
}