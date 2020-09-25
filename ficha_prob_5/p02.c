#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

struct Results {
  int sum;
  int dif;
  int mul;
  /*0 - inteiro
    1 - float
    2 - invalido */
  unsigned int tipo:2;
  int divint;
  double divdoub;
};
typedef struct Results results;

int main(void)
{
  int fdsend[2];
  int fdreceive[2];
  pid_t pid;
  
  if (pipe(fdsend) < 0)
  {
    fprintf(stderr, "pipe error\n");
    exit(1);
  }
  if (pipe(fdreceive) < 0)
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
    /* pai recebe info de fdreceive e manda info para fdsend */
    close(fdsend[READ]); /* fecha lado receptor do pipe que manda */
    close(fdreceive[WRITE]); // fecha lado emissor do pipe que recebe

    int a[2];
    printf("Parent:\nx y ? ");
    scanf("%d %d", &a[0], &a[1]);
    
    write(fdsend[WRITE], a, 2*sizeof(int));
    close(fdsend[WRITE]); // fim de pipe para mandar

    results res;
    read(fdreceive[READ], &res, sizeof(res));
    printf("x + y = %d\n", res.sum);
    printf("x - y = %d\n", res.dif);
    printf("x * y = %d\n", res.mul); 
    if (res.tipo == 2)
    {
      printf("No division for you buckaroo");
      exit(1);
    } else if (res.tipo == 1)
    {
      printf("x / y = %lf\n", res.divdoub);
    } else
      printf("x / y = %d\n", res.divint);

  }
  else
  {               /* filho */
    /* filho recebe info de fdsend e manda info para fdreceive */
    close(fdsend[WRITE]); /* fecha lado emissor do pipe que recebe */
    close(fdreceive[READ]); // fecha lado de ler do pipe que o pai recebe
    
    int b[2];
    read(fdsend[READ], b, 2*sizeof(int));
    printf("Son:\n");
    results res;
    res.sum = b[0] + b[1];
    res.dif = b[0] - b[1];
    res.mul = b[0] * b[1];
    if (b[1] == 0)
    {
      res.tipo = 2;
      res.divint = 0;
      res.divdoub = 0;
    } else if (b[0] % b[1] != 0)
    {
      res.tipo = 1;
      res.divdoub = (1.0 * b[0]) / b[1];
    } else
      res.divint = b[0] / b[1];
    
    write(fdreceive[WRITE], &res, sizeof(res));
  }
  exit(0);
}