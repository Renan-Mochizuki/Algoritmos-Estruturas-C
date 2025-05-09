#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

// Função que imprime a array
void ImprimirValores(const TipoValor arr[], int tamanho){
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

// Função que máxima o heap, trocando o valor da raiz com o maior filho recursivamente
void Heapify(TipoValor arr[], int tamanho, int raiz) {
  int maior = raiz; // Inicializa o maior como raiz
  int esquerda = 2 * raiz + 1; // Filho da esquerda
  int direita = 2 * raiz + 2; // Filho da direita

  // Verificando se o filho da esquerda ou direita é maior e se o índice não ultrapassou o tamanho
  if (esquerda < tamanho && arr[esquerda] > arr[maior])
    maior = esquerda;

  if (direita < tamanho && arr[direita] > arr[maior])
    maior = direita;

  // Se um dos filhos for maior que a raiz, troque e execute Heapify novamente para esse filho
  if (maior != raiz) {
    Trocar(&arr[raiz], &arr[maior]);
    Heapify(arr, tamanho, maior);
  }
}

// Função que reorganiza a array em um heap (dos nós de baixo para cima)
void MaxHeapify(TipoValor arr[], int tamanho) {
  // Executando Heapify para cada nó, começando do último nó não folha (pois as folhas não precisam de heapify)
  int indiceUltimoNo = tamanho / 2 - 1;
  for (int i = indiceUltimoNo; i >= 0; i--)
    Heapify(arr, tamanho, i);
}

// Função que ordena a array usando o algoritmo Heap Sort
void HeapSort(TipoValor arr[], int tamanho) {
  // Converte a array em um max-heap
  MaxHeapify(arr, tamanho);

  // Já sabemos que a primeira posição da array (Raiz do heap) é o maior valor
  // Portanto, trocamos a raiz com o último item da array
  // Agora, a raiz não é mais um max-heap, então chamamos Heapify para a raiz

  // Loop que começa da última posição da array até a primeira
  for (int i = tamanho - 1; i >= 0; i--) {
    Trocar(&arr[0], &arr[i]);
    Heapify(arr, i, 0);
  }
}

int main(void){
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

  HeapSort(arr, tamanho);

  fimTempo = clock();

  printf("\nArray depois da ordenacao:\n");
  ImprimirValores(arr, tamanho);

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao da Ordenacao Heap Sort: %.6f segundos\n", tempoGasto);

  return 0;
}