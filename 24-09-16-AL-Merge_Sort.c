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

// Função que mescla duas metades ordenadas de uma array
// Complexidade: O(m)
// Sendo m o número de elementos na subarray que está sendo mesclada
// T(m) = mC/2 + mC/2 + mC/2
void Merge(TipoValor arr[], int p, int q, int r) {
  int tamanhoE = q - p + 1; // Tamanho da primeira metade
  int tamanhoD = r - q;     // Tamanho da segunda metade

  TipoValor E[tamanhoE], D[tamanhoD]; // Arrays temporários para as metades

  // Copiando os valores de cada metade para os arrays temporários
  for (int i = 0; i < tamanhoE; i++)
    E[i] = arr[p + i];
  for (int j = 0; j < tamanhoD; j++)
    D[j] = arr[q + 1 + j];

  // Declarando os índices para primeira metade, segunda e o índice para a array final
  int iE = 0, iD = 0, iArr = p;

  // Loop que vai preencher a array final com os valores de cada metade ordenadamente
  while (iE < tamanhoE && iD < tamanhoD) {
    // Coloca na array final o menor valor entre as duas metades até acabar uma delas
    if (E[iE] <= D[iD]) {
      arr[iArr] = E[iE];
      iE++;
    } else {
      arr[iArr] = D[iD];
      iD++;
    }
    iArr++;
  }

  // Se ainda houver elementos na primeira metade, copie-os para a array final
  while (iE < tamanhoE) {
    arr[iArr] = E[iE];
    iE++;
    iArr++;
  }

  // Se ainda houver elementos na segunda metade, copie-os para a array final
  while (iD < tamanhoD) {
    arr[iArr] = D[iD];
    iD++;
    iArr++;
  }
}

// Função que ordena a array usando o algoritmo Merge Sort
// Complexidade: O(n log n)
// T(n) = T(n/2) + T(n/2) + O(n)
// Resolvendo a recorrência: T(n) = Cn log_2(n) + Cn
void MergeSort(TipoValor arr[], int p, int r) {
  // Se o índice inicial for maior que o final
  if (p >= r) return;

  int q = (p + r) / 2;      // Pegando o ponto médio
  MergeSort(arr, p, q);     // Ordena a primeira metade
  MergeSort(arr, q + 1, r); // Ordena a segunda metade
  Merge(arr, p, q, r);      // Mescla as duas metades ordenadas
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

  MergeSort(arr, 0, tamanho - 1);

  fimTempo = clock();

  printf("\nArray depois da ordenacao:\n");
  ImprimirValores(arr, tamanho);

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao da Ordenacao Heap Sort: %.6f segundos\n", tempoGasto);

  return 0;
}