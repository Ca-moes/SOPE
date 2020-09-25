// PROGRAMA p01bint.c
// Not working
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
#define NUMITER 500

void *thrfunc(void *arg)
{
  int i;
  int value = *(int *) arg;
  fprintf(stderr, "Starting thread %d\n", value);
  for (i = 1; i <= NUMITER; i++)
    write(STDERR, &value , 1);
  return NULL;
}

int main()
{
  pthread_t ta, tb;
  int a=1, b=2;
  pthread_create(&ta, NULL, thrfunc, &a);
  pthread_create(&tb, NULL, thrfunc, &b);
  pthread_join(ta, NULL);
  pthread_join(tb, NULL);
  return 0;
}