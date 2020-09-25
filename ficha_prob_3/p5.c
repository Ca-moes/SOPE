#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>

int main(int argc, char const *argv[])
{
  pid_t pid1, pid2;
  pid1 = fork();
  if (pid1 == -1)
    perror("forking");
  else if (pid1 != 0)
    write(STDOUT_FILENO, "Hello", 5);
  else
  {
    pid2 = fork();
    if (pid2 == -1)
      perror("forking");
    else if (pid2 != 0)
      write(STDOUT_FILENO, " my", 3);
    else
      write(STDOUT_FILENO, " friends!\n", sizeof(" friends!\n"));
  }
  
  return 0;
}
