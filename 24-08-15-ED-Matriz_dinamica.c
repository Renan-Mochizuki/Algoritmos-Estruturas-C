#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define nLinhas 10
#define nColunas 10

int main(void) {
	// Definindo um ponteiro para um vetor de ponteiros
	int **m = (int **)malloc(nLinhas * sizeof(int *));

	// Loop que aloca memória para cada linha da matriz
	for (int linha = 0; linha < nLinhas; linha++) {
		m[linha] = (int *)malloc(nColunas * sizeof(int));
	}

	// m é um ponteiro que aponta para um vetor
	// esse vetor é composto por ponteiros
	// e cada um deles aponta para um vetor de inteiros

	srand(time(NULL));

	// Inserindo valores aleatórios na matriz de maneira diferente
	for (int i = 0; i < nLinhas; i++) {
		// Armazenando o valor de m[i], que é um ponteiro,
		// na variável a
		int *a = m[i];
		for (int j = 0; j < nColunas; j++) {
			// Acessando um bloco de memória no vetor apontado por a
			a[j] = rand() % 101;
			// m[i][j] = rand() % 101; funcionaria da mesma maneira
		}
	}

	// Loop para imprimir a matriz
	for (int i = 0; i < nLinhas; i++) {
		for (int j = 0; j < nColunas; j++) {
			printf("%d ",m[i][j]);
		}
		printf("\n");
	}

	return 0;
}