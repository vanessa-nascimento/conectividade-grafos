#include <stdio.h>
#include <stdlib.h> 
#include "grafo.h"

void componenteConexa(Grafo * grafo){
  int id = 0;
  int componenteConexo[grafo->numVertices];

  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componenteConexo[vertice] = -1;
  }
  
  fprintf(stdout, "\nComponentes Conexos:");
  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    if (componenteConexo[vertice] == -1) {
      id++;
      fprintf(stdout, "\nC%d: ", id);
      verificaVerticeComponenteConexo(grafo, componenteConexo, vertice, id);
    }
  }
  fprintf(stdout, "\n");
}

void verificaVerticeComponenteConexo(Grafo * grafo, int componenteConexo[], int vertice, int idComponente) {
  componenteConexo[vertice] = idComponente;
  fprintf(stdout, "%d ", vertice);
  Apontador atual = grafo->listaAdj[vertice];

  while (atual != NULL) {
    if(componenteConexo[atual->vdest] == -1) {
      verificaVerticeComponenteConexo(grafo, componenteConexo, atual->vdest, idComponente);
    }
    atual = atual->prox;
  }
}
