#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_NAME_LEN 50
#define MAX_NUM_LEN 5
#define TO_READ 3

int main(int argc, char *argv[])
{
  int desc = open("records.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
  printf("Insert %d student records.\n", TO_READ);

  char names[TO_READ][MAX_NAME_LEN];
  char clas[TO_READ][MAX_NUM_LEN];

  for (int i = 0; i < TO_READ; i++)
  {
    printf("Name of student %d? ",i+1);
    scanf("%s", names[i]);
    printf("Classification? ");
    scanf("%s", clas[i]);
  }

  for (int i = 0; i < TO_READ; i++)
  {
    write(desc, names[i], strlen(names[i]));
    write(desc , "  -  " , strlen("  -  "));
    write(desc, clas[i], strlen(clas[i]));
    write(desc , "\n" , strlen("\n"));
  }
  
  /* printf("\n\n");
  for (int i = 0; i < TO_READ; i++)
  {
    printf("Name of student %d - %s\n",i+1, names[i]);
    printf("Classification - %s\n", clas[i]);
  } */
  
  return 0;  
}