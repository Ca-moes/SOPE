//FOLHA 2 - p2b.c
//FILE COPY
//USAGE: copy source destination

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#define BUFFER_SIZE 512

/* 
  int open(const char * pathname, int oflag, [mode_t mode]);  
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
  indica que se atingiu o fim do ficheiro. 

  void perror(const char *string);
    Imprime na consola (em standard error) a string passada no argumento string,
  seguida do sinal de dois pontos (:), seguida da descrição correspondente ao código que
  nesse momento se encontra em errno. A linha é terminada com ‘\n’. 

  int close(int filedes);
    Retorna 0 no caso de sucesso e –1 no caso de erro. 
*/

int main(int argc, char *argv[])
{
  int fd1, fd2, nr, nw;
  unsigned char buffer[BUFFER_SIZE];

  if (argc != 3)
  {
    printf("Usage: %s <source> <destination>\n", argv[0]);
    return 1;
  }
  fd1 = open(argv[1], O_RDONLY);
  if (fd1 == -1)
  {
    perror(argv[1]);
    return 2;
  }
  fd2 = open(argv[2], O_WRONLY | O_CREAT | O_EXCL, 0644);
  if (fd2 == -1)
  {
    perror(argv[2]);
    close(fd1);
    return 3;
  }
  while ((nr = read(fd1, buffer, BUFFER_SIZE)) > 0)
  {
    if ((nw = write(fd2, buffer, nr)) <= 0 || nw != nr)
    {
      perror(argv[2]);
      close(fd1);
      close(fd2);
      return 4;
    }
  }
  close(fd1);
  close(fd2);
  return 0;
}