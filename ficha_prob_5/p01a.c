#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main(void)
{
  int fd[2];
  pid_t pid;
  
  if (pipe(fd) < 0)
  {
    fprintf(stderr, "pipe error\n");
    exit(1);
  }
  if ((pid = fork()) < 0)
  {
    fprintf(stderr, "fork error\n");
    exit(2);
  }
  else if (pid > 0)
  {               /* pai */
    close(fd[READ]); /* fecha lado receptor do pipe */

    int a[2];
    printf("Parent:\nx y ? ");
    scanf("%d %d", &a[0], &a[1]);
    
    write(fd[WRITE], a, 2*sizeof(int));
    close(fd[WRITE]);
  }
  else
  {               /* filho */
    close(fd[WRITE]); /* fecha lado emissor do pipe */
    int b[2];
    read(fd[READ], b, 2*sizeof(int));
    printf("Son:\n");
    printf("x + y = %d\n", b[0] + b[1]);
    printf("x - y = %d\n", b[0] - b[1]);
    printf("x * y = %d\n", b[0] * b[1]);
    if (b[1] == 0)
    {
      printf("No division for you.\n");
      exit(1);
    }
    printf("x / y = %lf\n", (1.0 * b[0]) / b[1]);
  }
  exit(0);
}