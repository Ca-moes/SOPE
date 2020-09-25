#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

struct Info {
  int a;
  int b;
};
typedef struct Info info;

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

    info inf;
    printf("Parent:\nx y ? ");
    scanf("%d %d", &inf.a, &inf.b);
    
    write(fd[WRITE], &inf, sizeof(info));
    close(fd[WRITE]);
  }
  else
  {               /* filho */
    close(fd[WRITE]); /* fecha lado emissor do pipe */
    
    info inf2;
    read(fd[READ], &inf2, sizeof(info));
    printf("Son:\n");
    printf("x + y = %d\n", inf2.a + inf2.b);
    printf("x - y = %d\n", inf2.a - inf2.b);
    printf("x * y = %d\n", inf2.a * inf2.b);
    if (inf2.b == 0)
    {
      printf("No division for you.\n");
      exit(1);
    }
    printf("x / y = %lf\n", (1.0 * inf2.a) / inf2.b);
  }
  exit(0);
}