#include <stdio.h>
#include <stdlib.h> 
#include "grafo.h"

void inicializaComponenteConexa(Grafo * grafo, int componente[]) {
  for(int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componente[vertice] = -1;
   }
}

void componenteConexa(Grafo * grafo) {
  int idComponente = 0;
  int componente[grafo->numVertices];

  inicializaComponenteConexa(grafo, componente);

  for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    if (componente[vertice] == -1) {
      idComponente++;
      verificaVerticeComponenteConexa(grafo, vertice, idComponente, componente);
    }
  }

  imprimeComponenteConexa(grafo, idComponente, componente);
  fprintf(stdout, "\n");
}

void verificaVerticeComponenteConexa(Grafo * grafo, int vertice, int idComponente, int componente[]) {
  Apontador atual = grafo->listaAdj[vertice];
  componente[vertice] = idComponente;
 
  while(atual != NULL) {
    if(componente[atual->vdest] == ANT_INICIO) verificaVerticeComponenteConexa(grafo, atual->vdest, idComponente, componente);
    
    atual = atual->prox;
  }
}

void imprimeComponenteConexa(Grafo * grafo, int idComponente, int componente[]) {
  fprintf(stdout, "\nComponentes Conectados:");
  
  for (int id = 1; id <= idComponente; id++) {
    fprintf(stdout, "\nC%d:", id);
   
   for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
      if (componente[vertice] == id) fprintf(stdout, " %d", vertice);
    }
  }
}