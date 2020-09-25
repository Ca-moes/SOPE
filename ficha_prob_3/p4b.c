#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
  pid_t pid;
  pid = fork();
  if (pid == -1)
  {
    perror("forking");
  } else if (pid != 0)
  {
    write(STDOUT_FILENO, "Hello", 5);
  } else
  {
    write(STDOUT_FILENO, " world!\n", sizeof(" world!\n"));
  }
  
  return 0;
}
