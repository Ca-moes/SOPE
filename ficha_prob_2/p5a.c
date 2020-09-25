#include <sys/types.h>  //a completar
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(void)
{
  int fd;
  char *text1="AAAAA";
  char *text2="BBBBB";

  fd = open("f1.txt", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC|O_SYNC,0600);
  
  write(fd,text1,5);
  write(fd,text2,5);
  close(fd);
  return 0;
}

