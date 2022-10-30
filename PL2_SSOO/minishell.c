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

#include "internas.h"
#include "entrada_minishell.h"
#include "ejecutar.h"


int main(int argc, char *argv[])
{

   char buf[BUFSIZ];
   char entrada;

   while (1)
   {
   	imprimir_prompt();
   	scanf("%c", entrada);
	leer_linea_ordenes(*entrada);
	if (fgets(buf) == "exit") {
		break;
	}   
   }

   return 0;
}



