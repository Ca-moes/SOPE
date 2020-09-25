#include <stdio.h>
#include <stdlib.h>   
#include <string.h>

int main(int argc, char* argv[], char* envp[])
{
  int i = 0;
  while (envp[i] != NULL)
  {
    printf("%s\n", envp[i++]);
  }
  
  /* for (size_t i = 0; i < 52; i++)
  {    
    printf("%s\n", envp[i]);
  } */
  return 1;
}