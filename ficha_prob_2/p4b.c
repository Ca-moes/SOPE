#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_NAME_LEN 50
#define MAX_NUM_LEN 5
#define TO_READ 3

typedef struct Record
{
  char name[MAX_NAME_LEN];
  int class;
} Record;

int main(int argc, char *argv[])
{
  int desc = open("records.txt", O_WRONLY | O_TRUNC);
  Record recs[TO_READ];
  Record temp;
  
  printf("Insert %d student records.\n", TO_READ);
  
  for (int i = 0; i < TO_READ; i++)
  {
    printf("Name of student %d? ",i+1);
    fgets(temp.name, MAX_NAME_LEN, stdin);
    printf("Classification? ");
    scanf("%d", &temp.class);
    getchar();
    recs[i] = temp;
  }

  for (int i = 0; i < TO_READ; i++)
  {
    write(desc, &recs[i], sizeof(Record));
  }
  close(desc);


  // Mostrar conteudo
  Record r;
  int desc2 = open("records.txt", O_RDONLY);
  while (read(desc2, &r, sizeof(Record))>0)
  {
    printf("Name : %sGrade: %d\n", r.name, r.class);
  }
  close(desc2);
  
  return 0;  
}