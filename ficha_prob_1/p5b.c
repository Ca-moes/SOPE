#include <stdio.h>
#include <stdlib.h>   
#include <string.h>

int main(int argc, char* argv[], char* envp[])
{
  for (size_t i = 0; envp[i] != NULL; i++)
  {
    if (strncmp("USER=", envp[i], 5) == 0)
    {      
      printf("Hello %s!\n", envp[i] + 5);
    }    
  }

  return 1;
}