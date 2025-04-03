#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int OrdenarVetor(int vetor[], int tamanho) {
  int i = 0;
  int trocou = 0;
  do {
    trocou = 0;
    int criterioDoLoop = tamanho - 1 - i;
    for (int j = 0; j < criterioDoLoop; j++) {
      if (vetor[j] > vetor[j + 1]) {
        int auxiliar = vetor[j];
        vetor[j] = vetor[j + 1];
        vetor[j + 1] = auxiliar;
        trocou = 1;
      }
    }
    i++;
  } while (trocou == 1);

  return 0;
}

int main() {
  int tamanho = 100;
  int vetor[tamanho], i;

  // Preenchendo o vetor com números aleatórios
  srand(time(NULL));
  for (int j = 0; j < tamanho; j++) {
    // Gera números aleatórios entre 0 e 1000
    vetor[j] = rand() % 1001;
  }

  printf("Array nao ordenada:\n");
  for (i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }

  OrdenarVetor(vetor, tamanho);

  printf("\n\nArray ordenada: \n");
  for (i = 0; i < tamanho; i++) {
    printf("%d ", vetor[i]);
  }

  return 0;
}
