#include <stdio.h>
#include <stdlib.h> 
#include "grafo.h"

void inicializaComponenteConexa(Grafo * grafo, int componente[]) {
   for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componente[vertice] = -1;
  }
}

void componenteConexa(Grafo * grafo) {
  int componente[grafo->numVertices];
  int idComponente = 0;
  
 inicializaComponenteConexa(Grafo * grafo, componente[grafo->numVertices]);
  
  fprintf(stdout, "\nComponentes Conexos:");
  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    if (componente[vertice] == ANT_INICIO) {
      idComponente++;
      fprintf(stdout, "\nC%d: ", idComponente);
      verificaVerticeComponenteConexo(grafo, vertice, componente, idComponente);
    }
  }
  fprintf(stdout, "\n");
}

void verificaVerticeComponenteConexo(Grafo * grafo, int vertice, int componente[], int idComponente) {
  Apontador atual = grafo->listaAdj[vertice];
  componente[vertice] = idComponente;

  fprintf(stdout, "%d ", vertice);

  while (atual != NULL) {
    if(componente[atual->vdest] == ANT_INICIO) {
      verificaVerticeComponenteConexo(grafo, componente, atual->vdest, idComponente);
    }
    atual = atual->prox;
  }
}
