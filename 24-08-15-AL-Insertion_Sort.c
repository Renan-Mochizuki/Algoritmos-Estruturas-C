#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamanhoArray 100

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
	int array[tamanhoArray];
	srand(time(NULL));

	// Loop para inserir valores aleatórios no array
	for (int i = 0; i < tamanhoArray; i++) {
		array[i] = rand() % 101;
	}

	// Loop para imprimir o array antes da ordenação
	for (int i = 0; i < tamanhoArray; i++) {
		printf("%d, ", array[i]);
	}

	InsertionSort(array, tamanhoArray);

	// Loop para imprimir o array depois da ordenação
	printf("\n\nArray ordenada:\n");
	for (int i = 0; i < tamanhoArray; i++) {
		printf("%d, ", array[i]);
	}

	return 0;
}