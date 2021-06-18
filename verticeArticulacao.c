#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

void verticeArticulacao(Grafo* grafo) {
    int inicioComponente, tempo, cor[grafo->numVertices], tDescoberta[grafo->numVertices], tTermino[grafo->numVertices], antecessor[grafo->numVertices], vArticulacao[grafo->numVertices], tmenorRetorno[grafo->numVertices];

    tempo = 0;
    
    for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
        cor[vertice] = BRANCO;
        tDescoberta[vertice] = tTermino[vertice] = 0;
        antecessor[vertice] = ANT_INICIO;
        tmenorRetorno[vertice] = 0;
        vArticulacao[vertice] = false;
    }
    
    for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
        if (cor[vertice] == BRANCO) percorreBP(grafo, vertice, cor, antecessor, &tempo, tDescoberta, tTermino, tmenorRetorno, vArticulacao);
    }

    imprimeVerticeArticulacao(grafo, vArticulacao);
}


void percorreBP(Grafo* grafo, int vertice, int cor[], int antecessor[], int* tempo, int tDescoberta[], int tTermino[], int tmenorRetorno[], int vArticulacao[]) {
  cor[vertice] = CINZA; 
  tDescoberta[vertice] = tmenorRetorno[vertice] = ++(*tempo);
  Apontador atual = grafo->listaAdj[vertice];

  if (!listaAdjVazia(grafo, vertice)) {
    while(atual != NULL) {

      if (cor[atual->vdest] == BRANCO) {
        antecessor[atual->vdest] = vertice;
        percorreBP(grafo, atual->vdest, cor, antecessor, tempo, tDescoberta, tTermino, tmenorRetorno, vArticulacao);

        tmenorRetorno[vertice] = tmenorRetorno[vertice] < tmenorRetorno[atual->vdest] ? tmenorRetorno[vertice] : tmenorRetorno[atual->vdest];
        if(antecessor[vertice] != ANT_INICIO && tmenorRetorno[atual->vdest] >= tDescoberta[vertice]) vArticulacao[vertice] = true;
      }

      else if (atual->vdest != antecessor[vertice]) {
        tmenorRetorno[vertice] = tmenorRetorno[vertice] < tDescoberta[atual->vdest] ? tmenorRetorno[vertice] : tDescoberta[atual->vdest];
      }
      
      atual = atual->prox;
    }
  }

  tTermino[vertice] = ++(*tempo);
  cor[vertice] = PRETO;
}

void imprimeVerticeArticulacao(Grafo* grafo, int vArticulacao[]) {
    fprintf(stdout, "\nVertices de articulacao:\n");
    for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
        if (vArticulacao[vertice]) fprintf(stdout, "%d ", vertice);
    }
}
