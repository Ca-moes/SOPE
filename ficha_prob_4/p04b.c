// PROGRAMA p04a.c
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  pid_t pid;
  int i, n, status;
  for (i = 1; i <= 3; i++)
  {
    pid = fork();
    if (pid == 0)
    {
      printf("CHILD no. %d (PID=%d) working ... \n", i, getpid());
      sleep(i * 7); // child working ...
      printf("CHILD no. %d (PID=%d) exiting ... \n", i, getpid());
      exit(0);
    }
  }

  for (i = 1; i <= 4; i++)
  {
    printf("PARENT: working hard (task no. %d) ...\n", i);
    n = 20;
    while ((n = sleep(n)) != 0)
      ;
    printf("PARENT: end of task no. %d\n", i);
    printf("PARENT: waiting for child no. %d ...\n", i);
    do
    {
      pid = waitpid(-1, &status, WNOHANG);

      if (pid != -1 && pid != 0)
        printf("PARENT: child with PID=%d terminated with exit code %d\n", pid, WEXITSTATUS(status));
      else 
        break;
    } while (pid != -1);
  }
  exit(0);
}

/*
CHILD no. 1 (PID=13005) working ... 
PARENT: working hard (task no. 1) ...
CHILD no. 2 (PID=13006) working ... 
CHILD no. 3 (PID=13007) working ... 
CHILD no. 1 (PID=13005) exiting ... 
CHILD no. 2 (PID=13006) exiting ... 
PARENT: end of task no. 1
PARENT: waiting for child no. 1 ...
PARENT: child with PID=13005 terminated with exit code 0
PARENT: child with PID=13006 terminated with exit code 0
PARENT: working hard (task no. 2) ...
CHILD no. 3 (PID=13007) exiting ... 
PARENT: end of task no. 2
PARENT: waiting for child no. 2 ...
PARENT: child with PID=13007 terminated with exit code 0
PARENT: working hard (task no. 3) ...
PARENT: end of task no. 3
PARENT: waiting for child no. 3 ...
PARENT: working hard (task no. 4) ...
PARENT: end of task no. 4
PARENT: waiting for child no. 4 ...
*/