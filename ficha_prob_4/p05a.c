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
    n = 20; while ((n = sleep(n)) != 0);
    printf("PARENT: end of task no. %d\n", i);
    printf("PARENT: waiting for child no. %d ...\n", i);
    pid = wait(&status);
    if (pid != -1)
      printf("PARENT: child with PID=%d terminated with exit code %d\n", pid, WEXITSTATUS(status));
  }
  exit(0);
}

/*
Os primeiros 2 filhos já acabaram quando o pai 1 acaba, mas o pai 1 só apanha 1 filho
Há um pai 4 que não apanha nenhum filho

PARENT: working hard (task no. 1) ...
CHILD no. 1 (PID=9711) working ... 
CHILD no. 2 (PID=9712) working ... 
CHILD no. 3 (PID=9713) working ... 
CHILD no. 1 (PID=9711) exiting ... 
CHILD no. 2 (PID=9712) exiting ... 
PARENT: end of task no. 1
PARENT: waiting for child no. 1 ...
PARENT: child with PID=9711 terminated with exit code 0
PARENT: working hard (task no. 2) ...
CHILD no. 3 (PID=9713) exiting ... 
PARENT: end of task no. 2
PARENT: waiting for child no. 2 ...
PARENT: child with PID=9712 terminated with exit code 0
PARENT: working hard (task no. 3) ...
PARENT: end of task no. 3
PARENT: waiting for child no. 3 ...
PARENT: child with PID=9713 terminated with exit code 0
PARENT: working hard (task no. 4) ...
PARENT: end of task no. 4
PARENT: waiting for child no. 4 ...
*/