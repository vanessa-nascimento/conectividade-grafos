#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// inicializaProfundidade: Setar todos os vertices como brancos, sem antecessor e tempo de de descoberta e término igual a zero
void inicializaProfundidade(Grafo * grafo, int cor[], int antecessor[], int tempo, int tDescoberta[], int tTermino[]) {
  tempo = 0;
  
  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    cor[vertice] = BRANCO;
    tDescoberta[vertice] = tTermino[vertice] = 0;
    antecessor[vertice] = ANT_INICIO;
  }
}

// buscaProfundidade: cria as variáveis e chama o inicializaProfundidade, faz a verificacao se um vértice é branco para percorrer o visitaBP e imprime o caminho da busca em profundidade
void buscaProfundidade(Grafo* grafo) {
  int inicioComponente, tempo, cor[grafo->numVertices], tDescoberta[grafo->numVertices], tTermino[grafo->numVertices], antecessor[grafo->numVertices];

  inicializaProfundidade(grafo, cor, antecessor, tempo, tDescoberta, tTermino);

  fprintf(stdout, "\nBP:\n");
  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    if (cor[vertice] == BRANCO) visitaBP(grafo, vertice, cor, antecessor, &tempo, tDescoberta, tTermino);
  }
  fprintf(stdout, "\n");

  imprimeCaminhoBP(grafo, inicioComponente, antecessor);
}

// visitaBP: percorre os vertices para indicar seu tempo de descoberta, o ternando cinza e término, o tornando preto
void visitaBP(Grafo* grafo, int vertice, int cor[], int antecessor[], int* tempo, int tDescoberta[], int tTermino[]) {
  cor[vertice] = CINZA; 
  tDescoberta[vertice] = ++(*tempo);
  Apontador atual = grafo->listaAdj[vertice];
  
  fprintf(stdout, "%d ", vertice);

  if (!listaAdjVazia(grafo, vertice)) {

    while(atual != NULL) {

      if (cor[atual->vdest] == BRANCO) {
        antecessor[atual->vdest] = vertice;
        visitaBP(grafo, atual->vdest, cor, antecessor, tempo, tDescoberta, tTermino);
      }

      atual = atual->prox;
    }
  }

  tTermino[vertice] = ++(*tempo);
  cor[vertice] = PRETO;
}

//caminhoBP: percorre os vertices na ordem feita pela ordem de descobrimento
void caminhoBP(int inicioComponente, int vertice, int antecessor[]) {
  if (inicioComponente == vertice) {
    fprintf (stdout, "%d", inicioComponente);
    return;
  } 
  if (antecessor[vertice] == ANT_INICIO) return;
  else {
    caminhoBP(inicioComponente, antecessor[vertice], antecessor);
    fprintf (stdout, " %d" , vertice);
  }
}

//imprimeCaminhoBP: percorre os vertices e faz a impressão do caminhoBP
void imprimeCaminhoBP(Grafo* grafo, int inicioComponente, int antecessor[]) {
  fprintf(stdout, "\nCaminhos BP:\n");
  for (int vertice = 0; vertice < grafo->numVertices; vertice++) {
    if(antecessor[vertice] == ANT_INICIO) inicioComponente = vertice;
    
    caminhoBP(inicioComponente, vertice, antecessor);
    fprintf(stdout, "\n");
  }
}