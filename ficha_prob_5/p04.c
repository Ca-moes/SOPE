#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define MAXNAMELEN 500
#define READ 0
#define WRITE 1

int main(int argc, char *argv[])
{
  int fd1[2], fd2[2];
  pid_t pid1, pid2;

  if (argc != 3)
  {
    printf("Usage: prog dir arg");
    exit(1);
  }

  if (pipe(fd1) < 0)
  {
    perror("Pipe");
    exit(1);
  }
  if (pipe(fd2) < 0)
  {
    perror("Pipe");
    exit(1);
  }

  pid1 = fork();
  if (pid1 < 0)
  {
    perror("Fork");
    exit(1);
  }

  if (pid1 > 0)
  {
    close(fd1[READ]);
    dup2(fd1[WRITE], STDOUT_FILENO);
    if (execlp("ls", "ls", argv[1], "-laR", NULL) < 0)
    {
      perror("ExecParent");
      exit(1);
    }
  }
  else if (pid1 == 0)
  {
    pid2 = fork();
    if (pid2 < 0)
    {
      perror("Fork");
      exit(1);
    }
    close(fd1[WRITE]);
    if (pid2 > 0)
    {
      close(fd2[READ]);
      dup2(fd1[READ], STDIN_FILENO);
      dup2(fd2[WRITE], STDOUT_FILENO);
      if (execlp("grep", "grep", argv[2], NULL) < 0)
      {
        perror("ExecChild1");
        exit(1);
      }
    }
    else if (pid2 == 0)
    {
      close(fd2[WRITE]);
      dup2(fd2[READ], STDIN_FILENO);
      if (execlp("sort", "sort", NULL) < 0)
      {
        perror("ExecChild2");
        exit(1);
      }
    }
  }

  exit(0);
}