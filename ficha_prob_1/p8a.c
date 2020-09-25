#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]){
  srand(time(0));
  int numb = 0, i=0;
  do
  {
    numb = rand()%atoi(argv[1]);
    printf("%d : %d \n", ++i, numb);
  } while (numb != atoi(argv[2]));
  
  return 0;
}