#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

// inicializaGrafo: verifica se numVertices é inválido e inicializa o grafo com zero arestas e lista de adjacentes para NULL
bool inicializaGrafo(Grafo * grafo, int numVertices){
  if (numVertices <= 0) {
      fprintf(stderr, "\nERRO em inicializaGrafo: Numero de vertices deve ser maior que zero.");
      return false;
  }
  if (numVertices > 100) {
    fprintf(stderr, "ERRO em inicializaGrafo: Numero de vertices deve ser menor que 100.\n");
    return false;
  }

  grafo->numVertices = numVertices;

  if (!(grafo->listaAdj = (Apontador*) calloc(numVertices + 1, sizeof(Apontador)))) {
      fprintf(stderr, "\nERRO em inicializaGrafo: Falha na alocacao de memoria");
      return false;
  }

  for (int i = 0; i < grafo->numVertices; i++) grafo->listaAdj[i] = NULL;

  grafo->numArestas = 0;
  return true;
};

// verificaValidadeVertice: verifica o vertice é maior do que numVertices e se é negativo
bool verificaValidadeVertice(Grafo * grafo, int v) {
  if (v > grafo->numVertices) {
      fprintf(stderr, "ERRO em verificaValidadeVertice: O vertice (%d) maior que o numero de vertices indicados no grafo (%d)", v, grafo->numVertices);
      return false;
  }
  if (v < 0) {
      fprintf(stderr, "ERRO em verificaValidadeVertice: O vertice (%d) precisa ser positivo", v);
      return false;
  }

  return true;
}

// existeAresta: retorna true se já possui aresta entre dois vertice no grafo e false caso contrário
bool existeAresta(Grafo * grafo, int v1, int v2) {
  Apontador aresta = grafo->listaAdj[v1];

  while (aresta != NULL && aresta->vdest != v2) aresta = aresta -> prox;
  if (aresta != NULL) return true;
  
  return false;
}

//insereAresta: insere uma aresta entre dois vértices com seu peso, inserindo a aresta no caminho inverso e indicando qual aresta considerar para utilizar em outras funções
void insereAresta(Grafo * grafo, int v1, int v2, Peso peso) {
  Apontador novaAresta;

  if(v1 == v2){
      fprintf(stderr, "\nERRO em insereAresta: Grafos nao-direcionados nao podem ter self-loops");
      return;
  }

  if (!(verificaValidadeVertice(grafo, v1) && verificaValidadeVertice(grafo, v2))) return;

  if (existeAresta(grafo, v1, v2)) {
      fprintf(stderr, "ERRO em insereAresta: Ja existe a aresta (%d, %d).\n", v1, v2);
      return;
  }

  if (!(novaAresta = (Apontador) calloc(1, sizeof(Apontador)))) {
      fprintf(stderr, "ERRO em insereAresta: Falha na alocacao de memoria\n");
      return;
  }

  novaAresta->vdest = v2;
  novaAresta->peso = peso;
  novaAresta->prox = grafo->listaAdj[v1];
  novaAresta->aresta = !existeAresta(grafo, v2, v1);
  grafo->listaAdj[v1] = novaAresta;

  if (!existeAresta(grafo, v2, v1)) grafo->numArestas++;
}

//removeAresta: remove uma aresta entre dois vértices, subtraindo de numArestas e atualizando o adjacente para NULL
bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso) {
  Apontador atual, anterior;
  atual = grafo->listaAdj[v1];

  if (!existeAresta(grafo, v1, v2)) return false;

  while (atual != NULL && atual->vdest != v2) {
    anterior = atual;
    atual = atual->prox;
  }

  if (atual != NULL) {
    if (grafo->listaAdj[v1] == atual) grafo->listaAdj[v1] = atual->prox;
    else anterior->prox = atual->prox;

    *peso = atual->peso;
    atual->prox = NULL;
    
    free(atual);
    atual = NULL;
    
    grafo->numArestas--;
    return true;
  }

  return false;
}

//leGrafo: le um arquivo de entrada, inicializa o grafo e insere as arestas de acordo
void leGrafo(FILE * arquivoEntrada, Grafo* grafo) {
  int nVertices, nArestas;
  int v1, v2;
  Peso peso;

  if(arquivoEntrada == NULL) {
    fprintf(stderr, "ERRO em leGrafo: O arquivo não existe!");
    return;
  }

  if (!fscanf(arquivoEntrada, "%d %d", &nVertices, &nArestas)) {
    fprintf(stderr, "ERRO em leGrafo: Problema ao ler os indices de nVertices e nArestas");
    return;
  }

  inicializaGrafo(grafo, nVertices);

  while(fscanf(arquivoEntrada, "%d %d %d", &v1, &v2, &peso) != EOF) {
    insereAresta(grafo, v1, v2, peso);
    insereAresta(grafo, v2, v1, peso);
  }

  fclose(arquivoEntrada);
  return;
}

//liberaGrafo: apaga o grafo liberando em memória
void liberaGrafo(Grafo * grafo) {
  int v;
  Apontador aresta;

  for (v = 0; v < grafo->numVertices; v++) {
    while ((aresta = grafo->listaAdj[v]) != NULL) {
      grafo->listaAdj[v] = aresta->prox;
      aresta->prox = NULL;
      free(aresta);
    }
  }
  grafo->numVertices = 0;
  free(grafo->listaAdj);
  grafo->listaAdj = NULL;

}

//listaAdjVazia: verifica se a lista de adjacencia de um vértice é vazia
bool listaAdjVazia(Grafo * grafo, int v) {
  if (!verificaValidadeVertice(grafo, v)) return false;
  if(grafo->listaAdj[v] == NULL) return true;
  
  return false;
}

//primeiroListaAdj: verifica o primeiro da lista de adjacencia de um vértice
Apontador primeiroListaAdj(Grafo * grafo, int v) {
  return (grafo->listaAdj[v]);
}

//proxListaAdj: verifica o proximo da lista de adjacencia de um vértice
Apontador proxListaAdj(Grafo * grafo, int v, Apontador atual) {
  if (atual == NULL) {
    fprintf(stderr, "ERRO em proxListaAdj: Aresta atual e igual a NULL");
    return false;
  }

  return (atual -> prox);
}

//imprimeGrafo: imprime o grafo atual com numVertices, numArestas os vertices, o vertice destino e o peso da aresta
void imprimeGrafo(Grafo* grafo) {
  Apontador atual;
  fprintf(stdout, "%d %d", grafo->numVertices, grafo->numArestas);
  
  for (int i = 0; i < grafo->numVertices; i++) {
    atual = grafo->listaAdj[i];

    if (!listaAdjVazia(grafo, i)) {
      while(atual != NULL) {
        if (atual->aresta) 
          fprintf (stdout, "\n%d %d %d", i, atual->vdest, atual->peso);
        atual = atual->prox;
      }
    }
    
  }
  return;
}
