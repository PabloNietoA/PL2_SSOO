#ifndef INTERNAS_H
#define INTERNAS_H

struct tipo_interna
{
  char *nombre;
  void (*func)(const char *);
};


int es_ord_interna(const char *);

void ejecutar_ord_interna(const char *);

#endif
