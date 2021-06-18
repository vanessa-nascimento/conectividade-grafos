#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "filaBuscaLargura.c"

// inicializaLargura: Setar todos os vertices como brancos, sem antecessor e distancia infinita
void inicializaLargura(Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
  for(int vertice = 0; vertice < grafo->numVertices; vertice++) {
    cor[vertice] = BRANCO;
    antecessor[vertice] = ANT_INICIO;
    distancia[vertice] = INFINITO;
  }
}

// buscaLargura: Definimos cor, antecessor distancia e printamos o visitaLargura e Caminhos da BL percorrendo todos os vertices
void buscaLargura(Grafo *grafo) {
  int cor[grafo->numVertices], antecessor[grafo->numVertices], distancia[grafo->numVertices];
  int inicioComponente;

  inicializaLargura(grafo, cor, antecessor, distancia);
  
  fprintf(stdout, "\n\nBL: \n");
  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    if (cor[vertice] == BRANCO) visitaLargura(vertice, grafo, cor, antecessor, distancia);
  }

  fprintf(stdout, "\n\nCaminhos BL: \n");
  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    if(distancia[vertice] == DIST_INICIO) inicioComponente = vertice;
    
    caminhoLargura(inicioComponente, vertice, antecessor, distancia);
    fprintf(stdout, "\n");
  }
}

// visitaLargura: Aqui visitamos os vertices de um componente inseridos em uma fila, e mudando cor para cinza quem for branco e preto para quem ja for cinza, atualizando sua distancia e antecessor
void visitaLargura(int inicioComponente, Grafo *grafo, int cor[], int antecessor[], int distancia[]) {
  cor[inicioComponente] = CINZA;
  distancia[inicioComponente] = DIST_INICIO;
  antecessor[inicioComponente] = inicioComponente;

  PFILA Fila = inicializarFila();
  PITEM retiraPrimeiraFila;
  Apontador vAtual;
  inserirElemento(Fila, inicioComponente);

  while(Fila->qtdElementos != 0) {
    retiraPrimeiraFila = atendePrimeiro(Fila);
    fprintf(stdout, "%d ", retiraPrimeiraFila->idItem);

    if(!listaAdjVazia(grafo, retiraPrimeiraFila->idItem)) {
      vAtual = grafo->listaAdj[retiraPrimeiraFila->idItem];
      
      while(vAtual != NULL) {
        
        if(cor[vAtual->vdest] == BRANCO) {
          cor[vAtual->vdest] = CINZA;
          antecessor[vAtual->vdest] = retiraPrimeiraFila->idItem;
          distancia[vAtual->vdest] = distancia[retiraPrimeiraFila->idItem] + 1;
          inserirElemento(Fila, vAtual->vdest);
        }
        vAtual = vAtual->prox;
      }
    }
    cor[retiraPrimeiraFila->idItem] = PRETO;
  }
}

//caminhoLargura: percorre os vertices de um componente
void caminhoLargura(int inicioComponente, int vertice, int antecessor[], int distancia[]) {
  if (inicioComponente == vertice) {
    fprintf (stdout, "%d ", inicioComponente);
    return;
  } 
  if (distancia[vertice] == 0) return;
  
  caminhoLargura(inicioComponente, antecessor[vertice], antecessor, distancia);
  fprintf(stdout, "%d ", vertice);
}