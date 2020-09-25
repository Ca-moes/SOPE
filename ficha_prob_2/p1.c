//FOLHA 2 - p2b.c
//LEITURA DE PASSWORD, SEM ECOAR CARACTER LIDO

#include <termios.h>
#include <unistd.h>
#include <string.h>

#define MAX_PASSWD_LEN 20

/* 
  tcgetattr(STDIN_FILENO, &tms);          lê características actuais da consola 
  tms.c_oflag |= (IXON | IXOFF);          activa Xon/Xoff 
  tms.c_cflag &= ~(PARENB | CSTOPB);      desactiva paridade e 2 stop bits 
  tcsetattr(STDIN_FILENO, TCSANOW, &tms); escreve novas características  

  Definidas em <unistd.h>:
  STDIN_FILENO    standard input (teclado)
  STDOUT_FILENO   standard output (écran)
  STDERR_FILENO   standard error (também écran)

  ECHO    Executa o eco dos caracteres recebidos para o buffer de saída
  ECHOE   Apaga os caracteres visualmente (carácter de backspace - VERASE)
  ECHOK   Apaga as linhas visualmente (carácter VKILL)
  ECHONL  Ecoa o carácter de NL mesmo se ECHO estiver desactivad
  ICANON  Modo canónico (processa caracteres especiais) 

  TCSANOW   - A modificação é feita imediatamente
  TCSADRAIN - A modificação é feita depois de se esgotar o buffer de saída
  TCSAFLUSH - A modificação é feita depois de se esgotar o buffer de saída; quando isso acontece o buffer de entrada é esvaziado (flushed). 
*/

int main(void)
{
  struct termios term, oldterm;
  int i=0;
  char pass[MAX_PASSWD_LEN + 1], ch, echo = '*';

  write(STDOUT_FILENO, "\nPassword? ", 11);

  tcgetattr(STDIN_FILENO, &oldterm);
  term = oldterm;
  term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);

  while (i < MAX_PASSWD_LEN && read(STDIN_FILENO, &ch, 1) && ch != '\n')
  {
    pass[i++] = ch;
    write(STDOUT_FILENO, &echo, 1);
  }
  pass[i] = 0;

  tcsetattr(STDIN_FILENO, TCSANOW, &oldterm);
  write(STDOUT_FILENO, "\n\nPassword: ", 12);
  write(STDOUT_FILENO, pass, strlen(pass));
  write(STDOUT_FILENO, "\n", 1);

  return 0;
}
