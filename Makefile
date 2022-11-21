CFLAGS = -g -Wall
minishell: ejecutar.o entrada_minishell.o libmemoria.o minishell.o redirecciones.o libshell.a
	gcc $(CFLAGS) ejecutar.o entrada_minishell.o libmemoria.o minishell.o redirecciones.o libshell.a -o minishell
ejecutar.o: ejecutar.c parser.h ejecutar.h libmemoria.h internas.h
	gcc $(CFLAGS) -c ejecutar.c
entrada_minishell.o: entrada_minishell.c entrada_minishell.h
	gcc $(CFLAGS) -c entrada_minishell.c
libmemoria.o: libmemoria.c libmemoria.h
	gcc $(CFLAGS) -c libmemoria.c
minishell.o: minishell.c ejecutar.h entrada_minishell.h internas.h libmemoria.h parser.h
	gcc $(CFLAGS) -c minishell.c
redirecciones.o: redirecciones.c
	gcc $(CFLAGS) -c redirecciones.c
libshell.a: parser.o internas.o
	ar rcs libshell.a parser.o internas.o

.PHONY: clean
clean:
	rm -f ejecutar.o entrada_minishell.o libmemoria.o minishell.o redirecciones.o minishell libshell.a
