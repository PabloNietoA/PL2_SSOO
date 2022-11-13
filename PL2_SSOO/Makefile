CFLAGS = -g -Wall
minishell: ejecutar.o entrada_minishell.o internas.o libmemoria.o minishell.o parser.o redirecciones.o
	gcc $(CFLAGS) ejecutar.o entrada_minishell.o internas.o libmemoria.o minishell.o parser.o redirecciones.o -o minishell
ejecutar.o: ejecutar.c parser.h ejecutar.h libmemoria.h
	gcc $(CFLAGS) -c ejecutar.c
entrada_minishell.o: entrada_minishell.c entrada_minishell.h
	gcc $(CFLAGS) -c entrada_minishell.c
libmemoria.o: libmemoria.c libmemoria.h
	gcc $(CFLAGS)-c libmemoria.c
minishell.o: minishell.c ejecutar.h entrada_minishell.h internas.h libmemoria.h parser.h
	gcc $(CFLAGS) -c minishell.c
redirecciones.o: redirecciones.c
	gcc $(CFLAGS) -c redirecciones.c
