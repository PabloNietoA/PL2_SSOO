#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

#include "ejecutar.h"
#include "entrada_minishell.h"
#include "internas.h"
#include "libmemoria.h"
#include "parser.h"

static void manejar_sigchild(int signo)
{
	int estado;
	waitpid(-1, &estado, WNOHANG);
}

int main(int argc, char *argv[])
{

   char buf[BUFSIZ];
   char entrada;
   struct sigaction sa;
   
   memset(&sa, 0, sizeof(sa));
   sa.sa_handler = manejar_sigchild;
   sa.sa_flags = SA_NOCLDSTOP | SA_RESTART;
   
   sigaction(SIGCHLD, &sa, NULL);
   
   while (1)
   {
   	imprimir_prompt();
	leer_linea_ordenes(buf);
	if (!strcmp(buf, "exit")) { //strcmp devuelve 0 si dos strings son iguales
		exit(0);
	}
	if (es_ord_interna(buf)) {
		ejecutar_ord_interna(buf);
	} else {
		ejecutar_linea_ordenes(buf);
	}
   }
   exit(EXIT_SUCCESS);
   return 0;
}



