#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

#include "parser.h"
#include "ejecutar.h"
#include "libmemoria.h"


pid_t ejecutar_orden(const char *orden, int *pbackgr)
{
   char **args;
   pid_t pid;
   int indice_ent = -1, indice_sal = -1; /* por defecto, no hay < ni > */
  
   if ((args = parser_orden(orden, &indice_ent, &indice_sal, pbackgr)) == NULL)
   {
      return(-1);
   } else {
   	pid = fork();
   	if(pid == -1) {
		perror("Error en el fork");
		exit(-1);
   	} else if (pid == 0) { // si es la minishell hija ejecuta la orden
   		execvp(orden, args);
   		return(-1);
   	} else {
   		free_argumentos(args); //si es la minishell padre devuelve el pid de la hija
   		return(pid);
   	}
   }

   /* Si la linea de ordenes posee tuberias o redirecciones, podra incluir */
   /* aqui, en otras fases de la practica, el codigo para su tratamiento.  */
	
	
	
	
	
	
	
	
	
	
}
 
void ejecutar_linea_ordenes(const char *orden)
{
   pid_t pid;
   int backgr;
   int estado;


   /* Si la orden es compuesta, podra incluir aqui, en otra fase de la */
   /* practica, el codigo para su tratamiento                          */
 

   pid = ejecutar_orden(orden, &backgr);
   if (!backgr) {
	wait(&estado);
   } else {
   	printf("segundo plano\n"); //se queda zombie, no pasara cuando este el waitpid
   }
   

      
       
 


}   
