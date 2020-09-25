#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>

int main(int argc, char* argv[]){
  clock_t start, end;
  struct tms t; 
  long ticks; 

  start = times(&t); /* início da medição de tempo */
  ticks = sysconf(_SC_CLK_TCK);

  srand(time(0));
  int numb = 0, i=0;
  do
  {
    numb = rand()%atoi(argv[1]);
    printf("%d : %d \n", ++i, numb);
  } while (numb != atoi(argv[2]));
  

  printf("\nClock ticks per second: %ld\n", ticks);

  end = times(&t); /* fim da medição de tempo */
  
  printf("Clock: %4.2f s\n", (double)(end-start)/ticks);
  printf("User time: %4.2f s\n", (double)t.tms_utime/ticks);
  printf("System time: %4.2f s\n", (double)t.tms_stime/ticks);
  printf("Children user time: %4.2f s\n", (double)t.tms_cutime/ticks);
  printf("Children system time: %4.2f s\n", (double)t.tms_cstime/ticks);


  return 0;
}