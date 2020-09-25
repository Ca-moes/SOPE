#include <stdio.h>
#include <stdlib.h>
#define BUF_LENGTH 256

int main(int argc, char *argv[])
{
  FILE *src, *dst;
  char buf[BUF_LENGTH];

  if ((src = fopen(argv[1], "r")) == NULL){
    perror(argv[1]);
    exit(1);
  }

  if ((dst = fopen(argv[2], "w")) == NULL){
    perror(argv[1]);
    exit(2);
  }


  while (fread(buf, 1, 1, src) != 0)
  {
    fwrite(buf,1, 1, dst);
  }
  
  /* while ((fgets(buf, BUF_LENGTH, src)) != NULL)
  {
    fputs(buf, dst);
  } */

  fclose(src);
  fclose(dst);
  exit(0); // zero é geralmente indicativo de "sucesso"
}