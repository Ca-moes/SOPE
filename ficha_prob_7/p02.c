#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR 2
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER; // mutex p/a sec.critica
int NUMITER = 100;

void *thrfunc(void *arg)
{
  fprintf(stderr, "Starting thread %s\n", (char *)arg);

  while (1)
  {
    pthread_mutex_lock(&mut);
    if (NUMITER != 0)
    {
      write(STDERR, arg, 1);
      NUMITER--;
    }
    else
    {
      pthread_mutex_unlock(&mut);
      return NULL;
    }
    pthread_mutex_unlock(&mut);
  }
  return NULL;
}
int main()
{
  pthread_t ta, tb;

  pthread_create(&ta, NULL, thrfunc, "1");
  pthread_create(&tb, NULL, thrfunc, "2");

  pthread_join(ta, NULL);
  pthread_join(tb, NULL);

  return 0;
}