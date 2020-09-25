#include <stdio.h>
#include <stdlib.h>   
#include <string.h>

int main(int argc, char* argv[], char* envp[])
{
  //export USER_NAME="André Daniel Alves Gomes"   na consola
  printf("Hello %s!\n", getenv("USER_NAME"));
  return 1;
}