#include <stdio.h>
#include <stdbool.h>
#include "filaBuscaLargura.h"

PFILA inicializarFila() {
  PFILA fila = (PFILA) malloc(sizeof(FILA));
  PITEM item = (PITEM) malloc(sizeof(ITEM));
  
  fila->inicio = item;
  fila->qtdElementos = 0;

  item->idItem = -1;
  item->anterior = item;
  item->prox = item;

  return fila;
}

PITEM buscarElemento(PFILA f, int id){
  PITEM atual = f->inicio;

  while (atual != f->inicio) {
    if (atual->idItem == id) return atual;
    atual = atual->prox;
  }

  return NULL;
}

int tamanhoFila(PFILA fila) {
  return (fila->qtdElementos);
}

bool inserirElemento(PFILA f, int id) {
  if(id < 0 || buscarElemento(f,id) != NULL) return false;

  PITEM elemento = (PITEM)malloc(sizeof(ITEM));
  PITEM atual = f->inicio->prox;

  while (atual->idItem != -1) atual = atual->prox;

  elemento->idItem = id;
  elemento->anterior = atual->anterior;
  elemento->prox = atual;

  atual->anterior->prox = elemento;
  atual->anterior = elemento;

  f->qtdElementos++;
  return true;
}

PITEM atendePrimeiro(PFILA f) {
  if (tamanhoFila(f) == 0) {
    fprintf(stdout, "atendePrimeiro: Não há elementos para remover");
    return NULL;
  }
  
  PITEM res;
  PITEM primeiroFila = f->inicio->prox;

  primeiroFila->anterior->prox = primeiroFila->prox;
  primeiroFila->prox->anterior = primeiroFila->anterior;

  res = primeiroFila;
  f->qtdElementos--;

  return res;
}

void exibirFila(PFILA fila) {
  PITEM atual = fila->inicio->prox;

  fprintf(stdout, "\nexibirFila \n");
  while (atual != fila->inicio) {
    fprintf(stdout, "Elementos da fila: %d \n", atual->idItem);
    
    atual = atual->prox;
  }
}

void exibirLog(PFILA f) {
  fprintf(stdout, "exibirLog: Tamanho da fila: %d \n", tamanhoFila(f));
  exibirFila(f);
}