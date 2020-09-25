#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

int v = 0;
int cres = 0;
void sig_handler(int signo)
{
  printf("\nEntering SIG handler ...\n");

  if (signo == SIGUSR1)
    cres = 0;
  else if (signo == SIGUSR2)
    cres = 1;
  else if (signo == SIGTERM)
    cres = 2;
  
  printf("\nExiting SIG handler ...\n");
}

int main(void){

  struct sigaction action;
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

  while (1)
  {
    printf("%d\n", v);
    if (cres == 0)
      v++;
    else if (cres == 1)
      v--;
    else if (cres == 2)
      return 0;
    
    sleep(1);
  }

  return 0;
}