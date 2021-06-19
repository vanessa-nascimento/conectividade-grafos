#include <stdio.h>
#include <stdlib.h> 
#include "grafo.h"

//inicializaComponenteConexa: inicializa o componente com -1
void inicializaComponenteConexa(Grafo * grafo, int componente[]) {
  for(int vertice = 0; vertice < grafo->numVertices; ++vertice) {
    componente[vertice] = ANT_INICIO;
   }
}

//componenteConexa: cria variaveis necessarias, chama o inicializaComponenteConexa, cria componentes novas e insere vertices pertinentes com o verificaVerticeComponenteConexa
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

//verificaVerticeComponenteConexa: percorre os vertices, verificando se faz parte daquele componente
void verificaVerticeComponenteConexa(Grafo * grafo, int vertice, int idComponente, int componente[]) {
  Apontador atual = grafo->listaAdj[vertice];
  componente[vertice] = idComponente;
 
  while(atual != NULL) {
    if(componente[atual->vdest] == ANT_INICIO) verificaVerticeComponenteConexa(grafo, atual->vdest, idComponente, componente);
    
    atual = atual->prox;
  }
}

//imprimeComponenteConexa: faz a impressão dos componentes em ordem crescente
void imprimeComponenteConexa(Grafo * grafo, int idComponente, int componente[]) {
  fprintf(stdout, "\nComponentes Conectados:");
  
  for (int id = 1; id <= idComponente; id++) {
    fprintf(stdout, "\nC%d:", id);
   
   for (int vertice = 0; vertice < grafo->numVertices; ++vertice) {
      if (componente[vertice] == id) fprintf(stdout, " %d", vertice);
    }
  }
}