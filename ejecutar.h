#ifndef EJECUTAR_H
#define EJECUTAR_H

pid_t ejecutar_orden(const char *orden,int entrada, int salida, int *pbackgr);
void ejecutar_linea_ordenes(const char *orden);
int ** crear_pipes(int ordenes);

#endif
