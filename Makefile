all: testa_grafo

testa_grafo: grafo.o buscaLargura.o buscaProfundidade.o componenteConexa.o verticeArticulacao.o conectividade.o 
	gcc -o conectividade.exe grafo.o buscaLargura.o buscaProfundidade.o componenteConexa.o verticeArticulacao.o conectividade.o

grafo.o: grafo.c grafo.h
	gcc -c grafo.c

buscaLargura.o: buscaLargura.c grafo.h filaBuscaLargura.c filaBuscaLargura.h
	gcc -c buscaLargura.c

buscaProfundidade.o: buscaProfundidade.c grafo.h
	gcc -c buscaProfundidade.c

componenteConexa.o: componenteConexa.c grafo.h
	gcc -c componenteConexa.c

verticeArticulacao.o: verticeArticulacao.c grafo.h
	gcc -c verticeArticulacao.c

conectividade.o: conectividade.c grafo.h
	gcc -c conectividade.c

clean:
	rm -f *.o *.exe