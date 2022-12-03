CFLAGS = -g -Wall
minishell: ejecutar.o entrada_minishell.o libmemoria.o minishell.o redirecciones.o libshell.a #objetos y librerías de todo el código
	gcc $(CFLAGS) ejecutar.o entrada_minishell.o libmemoria.o minishell.o redirecciones.o libshell.a -o minishell #comando para generar el ejecutable de la minishell
redirecciones.o: redirecciones.c #archivo necesario para redirecciones
	gcc $(CFLAGS) -c redirecciones.c #comando para compilar redirecciones
ejecutar.o: ejecutar.c parser.h ejecutar.h libmemoria.h internas.h  #archivos necesarios para ejecutar
	gcc $(CFLAGS) -c ejecutar.c #comando para compilar ejecutar
entrada_minishell.o: entrada_minishell.c entrada_minishell.h #archivos necesarios para entrada_minishell
	gcc $(CFLAGS) -c entrada_minishell.c #comando para compilar entrada_minishell
libmemoria.o: libmemoria.c libmemoria.h #archivos necesarios para libmemoria
	gcc $(CFLAGS) -c libmemoria.c #comando para compilar libmemoria
minishell.o: minishell.c ejecutar.h entrada_minishell.h internas.h libmemoria.h parser.h #archivos necesarios para el objeto de minishell
	gcc $(CFLAGS) -c minishell.c #comando para compilar minishell
libshell.a: parser.o internas.o #archivos necesarios para la librería libshell
	ar rcs libshell.a parser.o internas.o #rcs: r: reemplaza archivos viejos por nuevos, c: crea la librería si no existía, s: ordena e indexa la librería 

.PHONY: clean 
clean:
	rm -f ejecutar.o entrada_minishell.o libmemoria.o minishell.o redirecciones.o minishell libshell.a #se deshace de todos los archivos inservibles
