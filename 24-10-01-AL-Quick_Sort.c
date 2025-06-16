#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

// Função que imprime a array
void ImprimirValores(const TipoValor arr[], int tamanho) {
  printf("\n");
  for (int i = 0; i < tamanho; i++) {
    printf("%d, ", arr[i]);
  }
  printf("\n");
}

// Função que preenche com valores aleatórios entre 0 e 1000
void PreencherValores(TipoValor arr[], int tamanho) {
  for (int i = 0; i < tamanho; i++) {
    arr[i] = rand() % 1001;
  }
}

// Função que troca dois valores
void Trocar(TipoValor *a, TipoValor *b) {
  TipoValor temp = *a;
  *a = *b;
  *b = temp;
}

// Função de partição do Quick Sort
int Particao(TipoValor arr[], int inicio, int fim) {
  TipoValor pivo = arr[fim];
  int i = inicio - 1;

  for (int j = inicio; j < fim; j++) {
    if (arr[j] <= pivo) {
      i++;
      Trocar(&arr[i], &arr[j]);
    }
  }
  Trocar(&arr[i + 1], &arr[fim]);
  return i + 1;
}

// Função recursiva do Quick Sort
void QuickSort(TipoValor arr[], int tamanho) {
  if (tamanho < 2) {
    return; // Array já está ordenada
  }

  int inicio = 0;
  int fim = tamanho - 1;

  int indicePivo = Particao(arr, inicio, fim);

  // Ordena as duas metades
  QuickSort(arr, indicePivo);
  QuickSort(arr + indicePivo + 1, tamanho - indicePivo - 1);
}

int main(void) {
  srand(time(NULL));
  clock_t inicioTempo, fimTempo;
  double tempoGasto;
  int tamanho;

  printf("Digite o tamanho da array que ira ser preenchida aleatoriamente:\n");
  scanf("%d", &tamanho);

  TipoValor arr[tamanho];

  PreencherValores(arr, tamanho);

  printf("\nArray antes da ordenacao:\n");
  ImprimirValores(arr, tamanho);

  inicioTempo = clock();

  QuickSort(arr, tamanho);

  fimTempo = clock();

  printf("\nArray depois da ordenacao:\n");
  ImprimirValores(arr, tamanho);

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao da Ordenacao Quick Sort: %.6f segundos\n", tempoGasto);

  return 0;
}