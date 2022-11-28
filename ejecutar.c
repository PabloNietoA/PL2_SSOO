#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "parser.h"
#include "ejecutar.h"
#include "libmemoria.h"
#include "internas.h"
#include "redirecciones.h"


pid_t ejecutar_orden(const char *orden, int *pbackgr)
{
   	char **args;
   	pid_t pid;
   	int entrada = 0, salida = 1; //Se guardan los descriptores de archivo (por defecto 0 y 1)
   	int indice_ent = -1, indice_sal = -1; /* por defecto, no hay < ni > */
  
  
   	if (es_ord_interna(orden)) {
   			ejecutar_ord_interna(orden);
   			return (-1);
   	}
   	else if ((args = parser_orden(orden, &indice_ent, &indice_sal, pbackgr)) == NULL)
   	{
   		return(-1);
   	} 
   	else {
   		if(indice_ent != -1) redirec_entrada(args, indice_ent, &entrada);
   		if(indice_sal != -1) redirec_salida(args, indice_sal, &salida);
   		pid = fork();
   		if(pid == -1) {
			perror("Error en el fork");
			exit(-1);
   		}
   		else if (pid == 0) { // si es la minishell hija ejecuta la orden
   			if (entrada != 0) {
                   dup2(entrada, STDIN_FILENO); // duplicamos la entrada en STDIN_FILENO
                   args[indice_ent] = NULL-0; // con estas dos líneas borramos
                   args[indice_ent+1] = NULL-0; // la redirección y el archivo
                   close(entrada);
               }
               if (salida != 1) {
                   dup2(salida, STDOUT_FILENO); // duplicamos la salida en STDOUT_FILENO
                   args[indice_sal] = NULL-0; // con estas dos líneas borramos
                   args[indice_sal+1] = NULL-0; // la redirección y el archivo
                   close(salida);
               }
               execvp(args[0], args);
               exit(-1);
        }
   		else {
   			free_argumentos(args); //si es la minishell padre devuelve el pid de la hija
   			if (entrada != 0) close(entrada); //cerramos la entrada si hay redireccion
   			if (salida != 1) close(salida); //cerramos la salida si hay redireccion
   			return(pid);
   		}
   	}

   	/* Si la linea de ordenes posee tuberias o redirecciones, podra incluir */
   	/* aqui, en otras fases de la practica, el codigo para su tratamiento.  */
   
	
	
	
	
	
	
	
	
	
}
 
void ejecutar_linea_ordenes(const char *orden)
{
   int backgr;
   int estado;
<<<<<<< HEAD
   char * aux = (char*) orden;
=======
   char * aux = (char*)orden;
>>>>>>> fdd5c030a96575eae98ef64eea54adfa66b281ec
   char * token;
   const char * delim = ";";
   
   token = strtok(aux, delim);
   while (token !=NULL) {
	ejecutar_orden(token, &backgr);
   	if (!backgr || errno == -1) {
		wait(&estado);
	}
	token = strtok(NULL, delim);
   }
}   
