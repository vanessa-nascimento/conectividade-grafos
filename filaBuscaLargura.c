#include <stdio.h>
#include <stdbool.h>
#include "filaBuscaLargura.h"

//inicializarFila: inicializa alocando a fila e o item
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

//buscarItem: busca o item da fila
PITEM buscarItem(PFILA f, int id){
  PITEM atual = f->inicio;

  while (atual != f->inicio) {
    if (atual->idItem == id) return atual;
    atual = atual->prox;
  }

  return NULL;
}

//tamanhoFila: retorna a quantidade de elementos da fila
int tamanhoFila(PFILA fila) {
  return (fila->qtdElementos);
}

//inserirItem: insere um item no final da fila
bool inserirItem(PFILA f, int id) {
  if(id < 0 || buscarItem(f,id) != NULL) return false;

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

//atendePrimeiro: retira o primeiro item da fila
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

//exibirFila: mostra itens da fila por ordem de chegada
void exibirFila(PFILA fila) {
  PITEM atual = fila->inicio->prox;

  fprintf(stdout, "\nexibirFila \n");
  while (atual != fila->inicio) {
    fprintf(stdout, "Elementos da fila: %d \n", atual->idItem);
    
    atual = atual->prox;
  }
}

//exibirLog: instancia o exibirFila alem de mostrar o tamanho da fila
void exibirLog(PFILA f) {
  fprintf(stdout, "exibirLog: Tamanho da fila: %d \n", tamanhoFila(f));
  exibirFila(f);
}