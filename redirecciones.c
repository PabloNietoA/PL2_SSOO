#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

#include "redirecciones.h"


/* funcion que abre el archivo situado en la posicion indice_entrada+1 */
/* de la orden args y elimina de ella la redireccion completa          */
                                  
void redirec_entrada(char **args, int indice_entrada, int *entrada)
{
	*entrada = open(args[indice_entrada+1],O_RDONLY); //usamos la flag RDONLY
	if (*entrada == -1) {
		printf("Error al abrir el archivo"); //open devuelve -1 si hay error
		exit(-1);
	}
}

/* funcion que abre el archivo situado en la posicion indice_salida+1 */
/* de la orden args y elimina de ella la redireccion completa         */

void redirec_salida(char **args, int indice_salida, int *salida)
{
	*salida = open(args[indice_salida+1],O_RDWR | O_CREAT | O_TRUNC, 0666); //le damos permisos de write y read y 
										//si no existe lo crea, si existe lo trunca 
}

