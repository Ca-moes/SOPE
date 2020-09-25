// PROGRAMA p02a_b.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>


// Após entrar no handler, apenas 1 (ou nenhuma) ocorrência de SIGINT é processada

// Como usa o default handler, o programa é Terminated

void sigint_handler(int signo)
{
  printf("\nEntering handler ...\n");
  sleep(10);
  printf("\nExiting handler ...\n");
}

int main(void)
{
  struct sigaction action;
  action.sa_handler = sigint_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;

  if (sigaction(SIGINT, &action, NULL) < 0)
  {
    fprintf(stderr, "Unable to install SIGINT handler\n");
    exit(1);
  }

  printf("Try me with CTRL-C ...\n");

  while (1)
    pause();

  exit(0);
}