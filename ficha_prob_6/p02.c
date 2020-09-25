// PROGRAMA p02.c
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
int NUMITER=1000;

void *thrfunc(void *arg)
{
  int count=0;
  fprintf(stderr, "Starting thread %s\n", (char *)arg);
  while (NUMITER > 0)
  {
    NUMITER--;
    write(STDERR, "1", 1);
    count++;
  }
  return ((void *) count);
}

int main()
{
  pthread_t ta, tb;
  void *ret1, *ret2;
  pthread_create(&ta, NULL, thrfunc, "1");
  pthread_create(&tb, NULL, thrfunc, "2");
  pthread_join(ta, &ret1);
  pthread_join(tb, &ret2);

  printf("\n%d\n",(int)ret1);  
  printf("%d\n",(int)ret2);  
  return 0;
}