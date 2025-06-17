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
// Esquema de Lomuto, com o último elemento como pivô
// Complexidade: O(m)
// Sendo m o número de elementos na subarray que está sendo particionada
// T(m) = mC + C
int ParticaoLomuto(TipoValor arr[], int inicio, int fim) {
  // Escolhendo o último elemento como pivô
  // Pode ser melhor escolher o pivô de forma aleatória ou usando a mediana
  TipoValor pivo = arr[fim];
  // Inicializando i para fora do array
  int i = inicio - 1;

  // Loop que anda com j percorrendo a array do início até o penúltimo elemento
  for (int j = inicio; j < fim; j++) {
    // Se o elemento atual for menor ou igual ao pivô, incrementa i e troca os elementos com i e j
    if (arr[j] <= pivo) {
      i++;
      Trocar(&arr[i], &arr[j]);
    }
  }

  // Após o loop, temos uma parte com elementos menores ou iguais ao pivô e outra com elementos maiores
  // Precisamos colocar o pivô no meio dessas duas partes
  // Trocamos a posição i+1 (primeiro item da partição maior) com o pivô e retornamos o novo índice do pivô
  Trocar(&arr[i + 1], &arr[fim]);
  return i + 1;
}


// Função de partição do Quick Sort
// Esquema de Hoare, com o primeiro elemento como pivô
// Complexidade: O(m)
// Sendo m o número de elementos na subarray que está sendo particionada
// T(m) = mC + C
int ParticaoHoare(int vet[], int inicio, int fim) {
  // Escolhendo o primeiro elemento como pivô
  // Pode ser melhor escolher o pivô de forma aleatória ou usando a mediana
  int pivot = vet[inicio];
  int esq = inicio;
  int dir = fim;

  // Enquanto os ponteiros 'esq' e 'dir' não se cruzarem
  while (esq < dir) {
    // Mova o ponteiro 'esq' para a direita até encontrar o primeiro elemento MAIOR que o pivô
    // esq < fim para garantir que não ultrapasse o limite do array
    while (vet[esq] <= pivot && esq < fim)
      esq++;

    // Mova o ponteiro 'dir' para a esquerda até encontrar o primeiro elemento menor ou igual que o pivô
    while (vet[dir] > pivot)
      dir--;

    // Agora temos ponteiros para dois elementos, um maior e outro menor ou igual ao pivô
    // Portanto, iremos trocar esses elementos
    // esq < dir para garantir que 'esq' e 'dir' não se cruzaram
    if (esq < dir) {
      Trocar(&vet[esq], &vet[dir]);
    }

    // Continuaremos até que tenhamos uma parte menor ou igual ao pivô e outra maior
  }

  // Trocaremos o pivô com o último elemento da parte menor ou igual que está em 'dir' e retornamos o novo índice do pivô
  Trocar(&vet[inicio], &vet[dir]);
  return dir;
}

// Função recursiva do Quick Sort
// Complexidade: O(n log n) no caso médio e O(n^2) no pior caso
// T(n) = T(n/2) + T(n/2) + O(n)
// Resolvendo: T(n) = Cn log_2(n) + Cn
// No pior caso, a partição é sempre o menor ou o maior elemento, resultando em T(n) = Cn^2
void QuickSort(TipoValor arr[], int inicio, int fim) {
  if (inicio >= fim) return;

  // Chamando partição para separar uma parte menor ou igual ao pivô e outra maior
  int indicePivo = ParticaoHoare(arr, inicio, fim);

  QuickSort(arr, inicio, indicePivo - 1);
  QuickSort(arr, indicePivo + 1, fim);
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

  QuickSort(arr, 0, tamanho - 1);

  fimTempo = clock();

  printf("\nArray depois da ordenacao:\n");
  ImprimirValores(arr, tamanho);

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao da Ordenacao Quick Sort: %.6f segundos\n", tempoGasto);

  return 0;
}