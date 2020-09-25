// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

// Com SIGINT exit code = 0
// Com SIGUSR1 exit code = 100

void sigint_handler(int signo)
{
  printf("\nIn SIGINT handler ...\n");
}

int main(void)
{
  struct sigaction action;
  // prepare the 'sigaction struct'
  action.sa_handler = sigint_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  if (sigaction(SIGINT,&action,NULL) < 0)
  {
    fprintf(stderr, "Unable to install SIGINT handler\n");
    exit(1);
  }
  
  printf("Sleeping for 30 seconds ...\n");
  sleep(30);
  printf("Waking up ...\n");
  exit(0);
}