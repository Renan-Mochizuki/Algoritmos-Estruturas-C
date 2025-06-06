#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que ordena uma array usando o algoritmo Insertion Sort
// Complexidade: O(n^2)
// Pior caso: T(n) = (n-1) + (n-2) + ... + 1 = n(n-1)/2 = n^2/2 - n/2
void InsertionSort(int *array, int tamanho) {
	// Loop que percorre a array começando em 1
	for (int j = 1; j < tamanho; j++) {

		// Guardando o valor atual
		int auxiliar = array[j];

		// i pega o valor anterior
		int i = j - 1;
		
		// Enquanto o valor anterior for maior que o valor atual
		// mova os elementos maiores para a direita, até encontrar
		// a posição correta para o valor atual
		// i >= 0 para caso o valor atual for o menor de toda array
		while (i >= 0 && array[i] > auxiliar) {
			array[i + 1] = array[i];
			i--;
		}

		// Realize a troca
		// Se o while não acontecer, essa atribuição não tem efeito
		array[i + 1] = auxiliar;
	}
}

int main(void) {
  srand(time(NULL));
  clock_t inicioTempo, fimTempo;
  double tempoGasto;
  int tamanho;

  printf("Digite o tamanho da array que ira ser preenchida aleatoriamente:\n");
  scanf("%d", &tamanho);

	int array[tamanho];

	// Loop para inserir valores aleatórios no array
	for (int i = 0; i < tamanho; i++) {
		array[i] = rand() % 1001;
	}

	// Loop para imprimir o array antes da ordenação
	for (int i = 0; i < tamanho; i++) {
		printf("%d, ", array[i]);
	}

  inicioTempo = clock();

	InsertionSort(array, tamanho);

  fimTempo = clock();

	// Loop para imprimir o array depois da ordenação
	printf("\n\nArray ordenada:\n");
	for (int i = 0; i < tamanho; i++) {
		printf("%d, ", array[i]);
	}

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\n\nTempo de execucao para ordenar a array: %.6f segundos\n", tempoGasto);

	return 0;
}