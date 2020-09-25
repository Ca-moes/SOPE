#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
  DIR *dirp;
  struct dirent *direntp;
  struct stat stat_buf;
  char *str;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
    exit(1);
  }

  if ((dirp = opendir(argv[1])) == NULL)
  {
    perror(argv[1]);
    exit(2);
  }

  while ((direntp = readdir(dirp)) != NULL)
  {
    if (lstat(direntp->d_name, &stat_buf) == -1) // testar com stat()
    {
      perror("lstat ERROR");
      exit(3);
    }
    if (S_ISREG(stat_buf.st_mode))
      str = "regular";
    else if (S_ISDIR(stat_buf.st_mode))
      str = "directory";
    else
      str = "other";
    printf("%-25s - %s\n", direntp->d_name, str);
  }

  closedir(dirp);
  exit(0);
}


/*   usada como arg em stat, fstat, lstat
struct stat
{
  mode_t st_mode;    tipo de ficheiro e permissões 
  ino_t st_ino;      número do i-node correspondente 
  nlink_t st_nlink;  contagem de links 
  uid_t st_uid;      identificador do dono 
  gid_t st_gid;      identificador do grupo do dono 
  off_t st_size;     tamanho em bytes (ficheiros normais) 
  time_t st_atime;   último acesso 
  time_t st_mtime;   última modificação 
  time_t st_ctime;   último mudança de estado 
  long st_blocks;    número de blocos alocados 
} */

/*  retornada pelo readdir()
struct dirent {
  ino_t d_ino;               número do i-node que descreve o ficheiro 
  char d_name[NAME_MAX+1];   string com o nome do ficheiro 
} */

/* 
struct dirent *readdir(DIR *dp);
Lê a próxima entrada do directório (começa na primeira) retornando um apontador para
uma estrutura dirent. No caso de erro ou fim do directório retorna NULL.  
*/

/* 
int lstat(const char *pathname, struct stat *buf); 
Todos estes serviços preenchem uma estrutura stat, cujo endereço é passado em buf,
com informação acerca de um nome que apareça num directório (especificado em
pathname), ou através do seu descritor (filedes) se já estiver aberto.
O serviço lstat() difere de stat() apenas no facto de retornar informação acerca de um
link simbólico, em vez do ficheiro que ele referencia (que é o caso de stat()).
Retornam 0 no caso de sucesso e –1 no caso de erro.  
*/