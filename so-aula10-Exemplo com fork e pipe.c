/** Programa que cria processo pesado usando fork. Usa pipe para 
    comunicação entre os processos. Processo filho faz algo (no
    exemplo ele só dorme) e envia o tempo que levou para fazer
    este algo para o pai. Além disto cada um incrementa uma
    variável i.

    Author: Avelino F. Zorzo - Operating Systems
    avelino.zorzo@pucrs.br

    Date: 10.03.2012

    Qual o valor de i no pai e no filho? Por que este valor?

**/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

#define TAMMSG 80

int main() {
    int     fd[2], nbytes, i = 0;
    pid_t   pid;
    char    string[TAMMSG];
    char    buffer[TAMMSG];
    time_t  begin_t, end_t;


     pipe(fd);

     if ( (pid = fork()) == -1) {
                 printf("Erro ao criar processo = %d.\n",pid);
                 return(1);
      }

      if(pid == 0) { /* Código para o processo filho. */
               
               begin_t = time(NULL);
               sleep(3); /* Faz algo, no caso dorme. */
               end_t = time(NULL);

               sprintf(string, "%3.0f", difftime(end_t,begin_t));

               write(fd[1], string, (strlen(string)+1));
       
               i++; 
               printf("Filho: valor de i é %d\n", i);

        }
        else {     /* Código para o processo pai.*/                             
                   /* Leia algo que foi enviado pelo filho. */

                  nbytes = read(fd[0], buffer, 8);

                  printf("Pai: recebeu: %s\n", buffer);
                  i++; 
                  printf("Pai: valor de i é %d\n", i);             
        }
        
        return(0);
}