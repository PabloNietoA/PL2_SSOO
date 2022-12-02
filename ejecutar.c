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

int ** crear_pipes (int nordenes)
{
	int ** pipes = NULL ;
	int i ;
	pipes = (int **) malloc(sizeof(int *) * (nordenes - 1)); //reservamos memoria dinámica para los pipes que tengamos que hacer
	
	for (i = 0;i < (nordenes - 1);i++)
	{
		pipes[i] = (int *) malloc(sizeof(int ) * 2); //reservamos memoria para insertar los descriptores de lectura y escritura
		pipe(pipes[i]);	//creamos un pipe por cada espacio libre
	}
	return (pipes);
}

pid_t ejecutar_orden(const char *orden, int entrada, int salida, int *pbackgr)
{
   	char **args;
   	pid_t pid;
   	int indice_ent = -1, indice_sal = -1; /* por defecto, no hay < ni > */
  
  
   	if (es_ord_interna(orden)) { // no lo requiere, pero comprobamos si es una orden interna
   				     // para poder ejecutarla (como añadido :D )
   			ejecutar_ord_interna(orden);
   			return(-1);
   	}
   	else if ((args = parser_orden(orden, &indice_ent, &indice_sal, pbackgr)) == NULL)
   	{
   		return(-1);
   	} 
   	else {
   		if(indice_ent != -1) redirec_entrada(args, indice_ent, &entrada); // tratamos la redirección de entrada si existe 
   		if(indice_sal != -1) redirec_salida(args, indice_sal, &salida); // tratamos la redirección de salida si existe
   		pid = fork();
   		if(pid == -1) {
			perror("Error en el fork");
			exit(-1);
   		}
   		else if (pid == 0) { // si es la minishell hija ejecuta la orden
   			if (entrada != 0) {
   				dup2(entrada, STDIN_FILENO); // duplicamos la entrada en STDIN_FILENO
   				if(indice_ent != -1) args[indice_ent] = NULL-0; // con estas dos líneas borramos
   				if(indice_ent != -1) args[indice_ent+1] = NULL-0; // la redirección y el archivo
   				close(entrada);
   			}
   			if (salida != 1) {
   				dup2(salida, STDOUT_FILENO); // duplicamos la salida en STDOUT_FILENO
   				if(indice_sal != -1) args[indice_sal] = NULL-0; // con estas dos líneas borramos
   				if(indice_sal != -1) args[indice_sal+1] = NULL-0; // la redirección y el archivo
   				close(salida);
   			}
   			execvp(args[0], args);
   			exit(-1);
   		}
   		else {
   			free_argumentos(args); //si es la minishell padre devuelve el pid de la hija
   			if (entrada != 0) { 
   				close(entrada); //cerramos la entrada si hay redirección
   			}
   			if (salida != 1) {
   				close(salida); //cerramos la salida si hay redirección
   			}
   			return(pid);
   		}
   	}	
}
 
void ejecutar_linea_ordenes(const char *orden)
{
   int backgr;
   int nordenes;
   int estado;
   char * aux = (char*)orden;
   char * token;
   const char * delim = ";";
   int ** pipes;
   char ** ordenes;
   int entrada;
   int salida;
   
   token = strtok(aux, delim); 	//dividimos la línea de órdenes con ";" y las separamos 
   while (token !=NULL) { 	//mientras que siga habiendo caracteres que separar sigue ejecutando
      	ordenes = parser_pipes(token, &nordenes);
   	pipes = crear_pipes(nordenes); 
	for (int i = 0; i<=(nordenes-1); i++) { 	//hacemos un bucle con el numero de ordenes que devuelve el parser
		if (i == 0) {
			if (nordenes > 1) {
				salida = pipes[0][1]; 	//si es la primera orden y hay más se redirecciona la salida
			}
			else {
				salida = STDOUT_FILENO; //si es la primera y única orden se ejecuta tal cual
			}
			ejecutar_orden(ordenes[i], STDIN_FILENO, salida, &backgr);
		} else if ((i == (nordenes - 1)) && (nordenes > 1)) { 	//si es la última orden y hay varias (si no sería ejecutar tal cual)
			entrada = pipes[nordenes-2][0];			//redireccionamos la entrada y ejecutamos la orden
			ejecutar_orden(ordenes[i], entrada, STDOUT_FILENO, &backgr);
		} else {
			entrada = pipes[i-1][0];	//si es una orden intermedia redireccionamos la
			salida = pipes[i][1];		//entrada y la salida y la ejecutamos
			ejecutar_orden(ordenes[i], entrada, salida, &backgr);
		} if (!backgr || errno == -1) {		//por cada orden esperamos a que el proceso hijo acabe
			wait(&estado);			//antes de ejecutar el siguiente
		}
	}
	token = strtok(NULL, delim);	//la función strtok sigue funcionando con la entrada original si le pasamos NULL
   }
   free_ordenes_pipes (ordenes, pipes, nordenes); //liberamos la memoria dinámica que estábamos usando
}   
