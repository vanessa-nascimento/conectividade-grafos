#include <stdio.h>
#include "grafo.h"

int main() {
  Grafo grafo;

  stdin = fopen("./entrada.txt", "r");
  stdout = fopen("./saida.txt", "w+");
  stderr = fopen("./erro.txt", "w+");

  leGrafo(stdin,&grafo);
  imprimeGrafo(&grafo);
  buscaLargura(&grafo);
  buscaProfundidade(&grafo);
  componenteConexa(&grafo);
  verticeArticulacao(&grafo);
  liberaGrafo(&grafo);

  return 0;
}