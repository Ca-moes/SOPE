// PROGRAMA p8.c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[], char *envp[])
{
  pid_t pid;int status;
  if (argc != 2 && argc != 3)
  {
    printf("usage: %s dirname\nOR     %s dirname filename\n", argv[0], argv[0]);
    exit(1);
  }

  pid = fork();

  if (pid > 0){
    printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
    wait(&status);
  }
  else if (pid == 0)
  {
    
    if (argc == 3)
    {
      int fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
      dup2(fd, STDOUT_FILENO);
    }
    execlp("ls", "ls", "-laR", argv[1], NULL );
    printf("Command not executed !\n");
    exit(1);
  }
  exit(0);
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