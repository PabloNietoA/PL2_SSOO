#include <stdlib.h>

#include "libmemoria.h"


void free_argumentos(char **args)
{
   int i = 0;

   while(args[i])
      free(args[i++]);
   free(args);
}

void free_ordenes_pipes(char **ordenes, int **fds, int nordenes)
{
   int i = 0;

   for (i = 0; i < nordenes; i++)
   {
      free(ordenes[i]);
      if (i < (nordenes - 1))
         free(fds[i]);
   }

   free(ordenes);
   free(fds);
}