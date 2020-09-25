// PROGRAMA p8.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LENGTH 100

void decompose(char *str, char *tokens[], int *nargs){
  char *token = strtok(str, " ");;
  *nargs = 0;

  while (token != NULL)
  {
    tokens[(*nargs)++] = token;
    token = strtok (NULL, " ,.-");
  }
}

int main(int argc, char *argv[], char *envp[])
{
  char cmd[MAX_LENGTH];
  char *args[MAX_LENGTH];
  pid_t pid;
  int nArgs=0;

  do
  {
    printf("%sminish > %s", "\x1B[32m", "\x1B[37m");
    fgets(cmd, MAX_LENGTH, stdin);

    if ((strlen(cmd) > 0) && (cmd[strlen(cmd) - 1] == '\n'))
      cmd[strlen(cmd) - 1] = '\0';

    if (strcmp(cmd, "quit") == 0)
      return 0;
    else
    {
      pid = fork();

      if (pid > 0)
        printf("My child is going to execute command \"%s\"\n", cmd);
      else if (pid == 0)
      {
        decompose(cmd, args, &nArgs);
        args[nArgs] = NULL;
        execvp(args[0],args);
        printf("Command not executed !\n");
        exit(1);
      }
    }

  } while (strcmp(cmd, "quit") != 0);

  return 0;



  if (argc != 2 && argc != 3)
  {
    printf("usage: %s dirname\nOR     %s dirname filename\n", argv[0], argv[0]);
    exit(1);
  }
}

// int execlp(const char *filename, const char *arg0, … /* NULL */ );

/* dup2(fd, STDOUT_FILENO);
A partir deste momento qualquer escrita em STDOUT_FILENO, neste programa, passa a
ser feita no ficheiro representado pelo descritor fd.  */

/* int open(const char * pathname, int oflag, [mode_t mode]);  
    A função retorna um descritor de ficheiros ou –1 no caso de erro. 
  oflag :
    O_RDONLY  – abertura para leitura
    O_WRONLY  – abertura para escrita
   O_RDWR    – abertura para leitura e escrita 
   O_APPEND – acrescenta ao fim do ficheiro
    O_CREAT – Cria o ficheiro se não existe; requer o parâmetro mode
    O_EXCL – Origina um erro se o ficheiro existir e se O_CREAT estiver presente
   O_TRUNC – Coloca o comprimento do ficheiro em 0, mesmo se já existir
   O_SYNC – as operações de escrita só retornam depois dos dados terem sido fisicamente
  transferidos para o disco

  ssize_t read(int filedes, void *buffer, size_t nbytes); 
  ssize_t write(int filedes, const void *buffer, size_t nbytes);
    nbytes indica o número de bytes a tranferir enquanto que buffer é o endereço do local
  que vai receber ou que já contém esses bytes.
  As funções retornam o número de bytes efectivamente transferidos, que pode ser menor
  que o especificado. O valor –1 indica um erro, enquanto que o valor 0, numa leitura,
  indica que se atingiu o fim do ficheiro.  */