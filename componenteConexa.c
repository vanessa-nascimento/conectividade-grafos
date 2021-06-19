#include <stdio.h>
#include <stdlib.h> 
#include "grafo.h"

void inicializaComponenteConexa(Grafo * grafo, int componente[]) {
  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componente[vertice] = -1;
   }
}

void componenteConexa(Grafo * grafo) {
  int idComponente = 0;
  int componente[grafo->numVertices];

  inicializaComponenteConexa(grafo, componente);

  fprintf(stdout, "\nComponentes Conectados:");
  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    if (componente[vertice] == -1) {
      idComponente++;
      verificaVerticeComponenteConexo(grafo, componente, vertice, idComponente);
    }
  }
  imprimeComponenteConexa(grafo, componente, idComponente);
  fprintf(stdout, "\n");
}

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente) {
  componenteConexo[vertice] = idComponente;
  Apontador atual = grafo->listaAdj[vertice];
  
  while (atual != NULL) {
    if(componenteConexo[atual->vdest] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vdest, idComponente);
    }
    atual = atual->prox;
  }
}

void imprimeComponenteConexa(Grafo * grafo, int componente[], int idComponente) {
  for (int id = 1; id <= idComponente; id++) {
    fprintf(stdout, "\nC%d: ", id);
    for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
      if (componente[vertice] == id) fprintf(stdout, "%d ", vertice);
    }
  }
}