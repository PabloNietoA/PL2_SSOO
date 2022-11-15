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
	waitpid(-1, &estado, WNOHANG); /*espera a que le pase algo a un hijo (muera, se detenga, se reanude) -1 es para que afecte a todos los procesos hijos, &estado al haberlo declarado antes no es nulo por lo que guardará la información en el entero al que apunta. WNOHANG devuelve inmediatamente si ningún hijo se ha muerto DEVUELVE -1 si ha habido un error. 0 si ningún hijo ha cambiado el estado y el PID del hijo que ha cambiado si funciona correctamente*/
}

int main(int argc, char *argv[])
{

   char buf[BUFSIZ];
   char entrada;
   struct sigaction sa;
   
   memset(&sa, 0, sizeof(sa)); /*memset establece la memoria a partir de &sa con 0 un total de sizeof(sa) bits*/
   sa.sa_handler = manejar_sigchild; /*hacemos que el manejador (handler) de la estructura sa apunte a la función manejar_sigchild, declarada anteriormente*/
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



