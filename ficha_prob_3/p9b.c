// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void pr_exit(int status)
{
  if (WIFEXITED(status))
    printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
#ifdef WCOREDUMP /* nem sempre está definida em sys/wait.h */
           WCOREDUMP(status) ? " (core file generated)" : "");
#else
           "");
#endif
  else if (WIFSTOPPED(status))
    printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;
  int status;

  if (argc != 2)
  {
    printf("usage: %s dirname\n", argv[0]);
    exit(1);
  }
  pid = fork();
  if (pid > 0)
  {
    printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
    pid = waitpid(pid, &status, 0);
    if (pid == -1)
      perror("wait");
    else
    {
      printf("My child with pid %d fihished with a exit code %d\n", pid, status);
      pr_exit(status);
    }
  }
  else if (pid == 0)
  {
    char *args[] = {"ls", "-laR", argv[1], NULL};
    execve("/bin/ls", args, envp);
    printf("Command not executed !\n");
    exit(1);
  }
  exit(0);
}

// int execve(const char *pathname,
//            const char *argv[],
//            char * const envp[]);