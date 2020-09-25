#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>

int v = 0;
int cres = 0;
void sig_handler(int signo)
{
  //printf("\nEntering SIG handler ...\n");

  if (signo == SIGUSR1)
    cres = 0;
  else if (signo == SIGUSR2)
    cres = 1;
  else if (signo == SIGTERM)
    cres = 2;

  //printf("\nExiting SIG handler ...\n");
}

int main(void)
{

  struct sigaction action;
  pid_t pid;

  action.sa_handler = sig_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  if (sigaction(SIGUSR1, &action, NULL) < 0)
  {
    fprintf(stderr, "Unable to install SIGUSR1 handler\n");
    exit(1);
  }
  if (sigaction(SIGUSR2, &action, NULL) < 0)
  {
    fprintf(stderr, "Unable to install SIGUSR2 handler\n");
    exit(1);
  }
  if (sigaction(SIGTERM, &action, NULL) < 0)
  {
    fprintf(stderr, "Unable to install SIGTERM handler\n");
    exit(1);
  }

  pid = fork();

  if (pid == -1)
    printf("Fork Error");
  else if (pid > 0)
  {
    int i = 10;

    srand(time(0));

    while (i > 0)
    {
      int num = rand() % 2;
      if (num == 0)
        kill(pid, SIGUSR1);
      else
        kill(pid, SIGUSR2); 
      
      i--;
      sleep(5);
    }
  }
  else if (pid == 0)
  {
    int i = 50;
    while (i > 0)
    {
      printf("%d\n", v);
      if (cres == 0)
        v++;
      else if (cres == 1)
        v--;
      else if (cres == 2)
        return 0;

      //printf("i = %d\n", i);
      i--;
      sleep(1);
    }
  }

  return 0;
}