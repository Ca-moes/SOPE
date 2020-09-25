// PROGRAMA p7.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// executa o comando gcc com argv["gcc", prog, "-Wall", "-o", argv[1]]
// argv[1] é o argumento de p7 com o nome do ficheiro, sem .c, para compilar
int main(int argc, char *argv[])
{
  char prog[20];
  int err;
  sprintf(prog, "%s.c", argv[1]); // prog fica com argv[1].c
  err = execlp("gcc", "gcc", prog, "-Wall", "-o", argv[1], NULL);
  if (err == -1)
    perror("exec");
  printf("ye");
  exit(0);
}
// int execlp(const char *filename, const char *arg0, … /* NULL */ ); 
