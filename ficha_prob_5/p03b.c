#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXNAMELEN 500
#define SORT "/usr/bin/sort"
#define CAT "/bin/cat"
#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
  int fd[2];
  pid_t pid;

  if (pipe(fd)<0)
  {
    perror("Pipe");
    exit(1);
  }

  pid = fork();
  if (pid < 0)
  {
    perror("Fork");
    exit(1);
  }
  
  if (pid > 0)
  {
    close(fd[READ]);
    dup2(fd[WRITE], STDOUT_FILENO);
    if (execl(CAT, CAT, argv[1], NULL)<0){
      perror("ExecParent");
      exit(1);
    }
  }
  if (pid == 0)
  {
    close(fd[WRITE]);
    dup2(fd[READ], STDIN_FILENO);
    if(execl(SORT, SORT, NULL)<0){
      perror("ExecChild");
      exit(1);
    }
  }
  
  exit(0);
}