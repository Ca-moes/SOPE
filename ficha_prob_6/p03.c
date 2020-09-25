// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
  printf("Hello from thread no. %d!\n", *(int *)threadnum);
  free(threadnum);
  pthread_exit(NULL);
}
int main()
{
  pthread_t threads[NUM_THREADS];
  int t;
  int *thrArg; 
  for (t = 0; t < NUM_THREADS; t++)
  {
    printf("Creating thread %d\n", t);
    thrArg = (int *) malloc(sizeof(t));
    *thrArg = t; 
    pthread_create(&threads[t], NULL, PrintHello, thrArg);
    pthread_join(threads[t], NULL);
  }
  pthread_exit(0);
}

/*Creating thread 0
  Hello from thread no. 1!
  Creating thread 1
  Creating thread 2
  Hello from thread no. 2!
  Creating thread 3
  Creating thread 4
  Hello from thread no. 4!
  Hello from thread no. 4!
  Creating thread 5
  Hello from thread no. 5!
  Creating thread 6
  Creating thread 7
  Hello from thread no. 7!
  Hello from thread no. 7!
  Creating thread 8
  Hello from thread no. 8!
  Creating thread 9
  Hello from thread no. 10!
  Hello from thread no. 10!
*/
// a) Entra na thread, o valor de t é alterado no ciclo for antes de escrever a partir da thread. 
// No momento da escrita faz print de um valor de t acima

/* c)
Outra dúvida comum é o uso de return  vs exit() vs pthread_exit() :
  pthread_exit mata uma thread (a calling thread) enquanto que o exit() termina o programa normalmente. 
  O main do vosso programa é também uma thread. O pthread_exit termina apenas assim apenas a thread respectiva e as outras continuam.

  (...) in main(), return will implicitly call exit(), and thus terminate the program, 
  whereas pthread_exit() will merely terminate the thread, and the program will remain running until all threads 
  have terminated or some thread calls exit(), abort() or another function that terminates the program.
*/