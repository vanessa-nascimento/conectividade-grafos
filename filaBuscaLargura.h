#include <stdlib.h>

typedef struct str_item {
  int idItem;
  struct str_item* anterior;
  struct str_item* prox;
} ITEM, * PITEM;

typedef struct {
  PITEM inicio;
  int qtdElementos;
} FILA, * PFILA;
