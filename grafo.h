#include <stdbool.h>

#define AN -1 //aresta nula
#define VERTICE_INVALIDO -1 //vertice invalido

#define ANT_INICIO -1 //anterior do inicio do componente
#define DIST_INICIO 0 //destino do inicio para inicializacao

//Usado para indicar as passagens pelo vertice no Busca em Profundidade e Largura 
#define BRANCO 0
#define CINZA 1
#define PRETO 2
#define INFINITO 100

typedef int Peso; //definifindo tipo peso

//struct da aresta
typedef struct str_aresta {
    int vdest;
    Peso peso;
    struct str_aresta * prox;
    bool aresta; //aresta: feita para diferenciar a de ida e volta entre dois vertices
} Aresta;

typedef Aresta * Apontador; //definindo apontador como ponteiro de aresta

//struct do grafo
typedef struct {
    Apontador * listaAdj;
    int numVertices;
    int numArestas;
} Grafo;

//interfaces para estrutura do grafo
bool inicializaGrafo(Grafo * grafo, int nv);

bool verticeValido(Grafo * grafo, int v);

void insereAresta(Grafo * grafo, int v1, int v2, Peso peso);

bool existeAresta(Grafo * grafo, int v1, int v2);

void leGrafo(FILE * arquivoGrafo, Grafo* grafo);

bool removeAresta(Grafo * grafo, int v1, int v2, Peso * peso);

bool listaAdjVazia(Grafo * grafo, int v);

Apontador primeiroListaAdj(Grafo * grafo, int v);

Apontador proxListaAdj(Grafo * grafo, int v, Aresta * atual);

void liberaGrafo(Grafo * grafo);

void imprimeGrafo(Grafo* grafo);

//interfaces para busca em largura
void buscaLargura(Grafo *grafo);

void visitaLargura(int origem, Grafo *grafo, int cor[], int antecessor[], int distancia[]);

void caminhoLargura(int u, int v, int antecessor[], int distancia[]);

void imprimeCaminhoLargura(Grafo *grafo, int distancia[], int antecessor[], int inicioComponente);

//interfaces para busca em profundidade
void inicializaProfundidade(Grafo * grafo, int cor[], int antecessor[], int tempo, int tDescoberta[], int tTermino[]);

void buscaProfundidade(Grafo* grafo);

void visitaBP(Grafo* grafo, int vertice, int cor[], int antecessor[], int* tempo, int tDescoberta[], int tTermino[]);

void caminhoBP(int origem, int v, int antecessor[]);

void imprimeCaminhoBP(Grafo *grafo, int inicioComponente, int antecessor[]);

//interfaces para componentes conectados
void componenteConexa(Grafo * grafo);

void inicializaComponenteConexa(Grafo * grafo, int componente[]);

void verificaVerticeComponenteConexa(Grafo * grafo, int vertice, int idComponente, int componente[]);

void imprimeComponenteConexa(Grafo * grafo, int idComponente, int componente[]);

//interfaces para vertice de articulacao
void verticeArticulacao(Grafo* grafo);

void percorreBP(Grafo* grafo, int vertice, int cor[], int antecessor[], int* tempo, int tDescoberta[], int tTermino[], int tmenorRetorno[], int vArticulacao[]);

void imprimeVerticeArticulacao(Grafo* grafo, int vArticulacao[]);

