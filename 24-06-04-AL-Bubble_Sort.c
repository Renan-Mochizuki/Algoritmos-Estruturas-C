#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que ordena uma array usando o algoritmo Bubble Sort
// Complexidade: O(n^2)
// Pior caso: T(n) = (n-1) + (n-2) + ... + 1 = n(n-1)/2 = n^2/2 - n/2
int BubbleSort(int vetor[], int tamanho) {
  int i = 0, trocou = 0;
  do {
    trocou = 0;
    // Subtrai 1 pois fazemos a comparação por pares e
    // - i pois a cada iteração i elementos já estão ordenados
    int criterioDoLoop = tamanho - 1 - i;
    for (int j = 0; j < criterioDoLoop; j++) {
      if (vetor[j] > vetor[j + 1]) {
        // Troca os elementos de lugar
        int auxiliar = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = auxiliar;
        trocou = 1;
      }
    }
    i++;
    // Caso não tenha acontecido nenhuma troca durante toda iteração atual
    // então, o vetor já está ordenado
  } while (trocou == 1);

  return 0;
}

// Complexidade: Θ(n^2)
int BubbleSortSimples(int vetor[], int tamanho) {
  for (int i = 0; i < tamanho - 1; i++) {
    for (int j = 0; j < tamanho - 1 - i; j++) {
      if (vetor[j] > vetor[j + 1]) {
        // Troca os elementos de lugar
        int auxiliar = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = auxiliar;
      }
    }
  }
  return 0;
}

int main() {
  srand(time(NULL));
  clock_t inicioTempo, fimTempo;
  double tempoGasto;
  int tamanho;

  printf("Digite o tamanho da array que ira ser preenchida aleatoriamente:\n");
  scanf("%d", &tamanho);

  int vetor[tamanho];

  // Preenchendo o vetor com números aleatórios
  srand(time(NULL));
  for (int j = 0; j < tamanho; j++) {
    // Gera números aleatórios entre 0 e 1000
    vetor[j] = rand() % 1001;
  }

  printf("Array nao ordenada:\n");
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }

  inicioTempo = clock();

  BubbleSort(vetor, tamanho);

  fimTempo = clock();

  printf("\n\nArray ordenada: \n");
  for (int i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\n\nTempo de execucao para ordenar a array: %.6f segundos\n", tempoGasto);

  return 0;
}
