#include <stdio.h>
#include <stdlib.h>

static void exithand1 (void){
  printf("Executing exit handler 1\n");
}

static void exithand2 (void){
  printf("Executing exit handler 2\n");
  exit(2);
}

int main(int argc, char* argv[])
{
  printf("Main Done!\n");
  atexit(exithand1);
  atexit(exithand2);
  
  return 0;
} 

/*
Será possível instalar um handler mais do que uma vez ?    YES
O que acontece se fizer uma chamada abort() na função main, antes de escrever "Main done!" no ecrã ?   "Aborted (core dumped)"
E se algum dos handlers terminar com exit() ?  Executa todos os handlers e faz exit do ultimo handler

*/