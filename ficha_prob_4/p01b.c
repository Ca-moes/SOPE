// PROGRAMA p01a.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo)
{
  printf("\nIn SIGINT handler ...\n");
}

int main(void)
{
  //signal(SIGINT, SIG_IGN);
  //signal(SIGUSR1, SIG_IGN);
  int remain;

  if (signal(SIGINT, sigint_handler) < 0)
  {
    fprintf(stderr, "Unable to install SIGINT handler\n");
    exit(1);
  }

  printf("Sleeping for 30 seconds ...\n");
  remain = sleep(30);
  while (remain > 0)
  {
    printf("Sleeping for %d seconds ...\n",remain);
    remain = sleep(remain);
  }

  printf("Waking up ...\n");
  exit(0);
}