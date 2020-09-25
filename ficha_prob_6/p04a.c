// PROGRAMA p03.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 10

void *PrintHello(void *threadnum)
{
  sleep(1);
  printf("Hello from thread no. %d!\n", *(int *)threadnum);
  free(threadnum);
  pthread_exit(threadnum);
}
int main()
{
  pthread_t threads[NUM_THREADS];
  int t;
  int *thrArg; 
  for (t = 0; t < NUM_THREADS; t++)
  {
    thrArg = (int *) malloc(sizeof(t));
    *thrArg = t; 
    pthread_create(&threads[t], NULL, PrintHello, thrArg);
    //pthread_join(threads[t], NULL);
  }
  pthread_exit(0);
}