#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;
typedef float Peso;

typedef struct {
  int id;
  Peso peso;
} ElementoFila;

typedef struct {
  ElementoFila *Arr;
  int *posicoes;
  int numElementos;
  int tamanho;
} FilaDePrioridade;

// Função que troca dois valores
void TrocarElementoFila(FilaDePrioridade *fila, int idA, int idB) {
  // Verificar se os parametros são válidos
  if (!fila || idA < 0 || idB < 0 || idA >= fila->numElementos || idB >= fila->numElementos) return;

  ElementoFila temp = fila->Arr[idA];
  fila->Arr[idA] = fila->Arr[idB];
  fila->Arr[idB] = temp;

  // Atualiza as posições dos elementos trocados
  fila->posicoes[fila->Arr[idA].id] = idA;
  fila->posicoes[fila->Arr[idB].id] = idB;
}

// Função que miniminiza o heap, trocando o valor da raiz com o maior filho recursivamente
void HeapifyFila(FilaDePrioridade *fila, int raiz) {
  int menor = raiz;            // Inicializa o menor como raiz
  int esquerda = 2 * raiz + 1; // Filho da esquerda
  int direita = 2 * raiz + 2;  // Filho da direita

  // Verificando se o filho da esquerda ou direita é menor e se o índice não ultrapassou o tamanho
  if ((esquerda < fila->numElementos) && (fila->Arr[esquerda].peso < fila->Arr[menor].peso))
    menor = esquerda;

  if ((direita < fila->numElementos) && (fila->Arr[direita].peso < fila->Arr[menor].peso))
    menor = direita;

  // Se um dos filhos for menor que a raiz, troque com a raiz e execute Heapify novamente para esse filho
  if (menor != raiz) {
    TrocarElementoFila(fila, raiz, menor);

    HeapifyFila(fila, menor);
  }
}

// Função que reorganiza a array em um heap (dos nós de baixo para cima)
void MinHeapify(FilaDePrioridade *fila) {
  // Executando Heapify para cada nó, começando do último nó não folha (pois as folhas não precisam de heapify)
  int indiceUltimoNo = fila->numElementos / 2 - 1;
  for (int i = indiceUltimoNo; i >= 0; i--)
    HeapifyFila(fila, i);
}

// Função que cria e retorna o ponteiro para uma fila de prioridade com o tamanho especificado
FilaDePrioridade *CriarFilaDePrioridade(int tamanho) {
  FilaDePrioridade *fila = malloc(sizeof(FilaDePrioridade));

  // Se a alocação não foi bem sucedida ou foi passado menos de um elemento
  if (!fila || tamanho < 1) return NULL;

  fila->Arr = malloc(sizeof(ElementoFila) * tamanho);
  fila->posicoes = malloc(sizeof(int) * tamanho);

  if (!fila->Arr || !fila->posicoes) {
    free(fila->Arr);
    free(fila->posicoes);
    free(fila);
    return NULL;
  }

  fila->numElementos = 0;
  fila->tamanho = tamanho;

  // Inicializa a array de posições com valores inválidos
  for (int i = 0; i < tamanho; i++) {
    fila->posicoes[i] = -1;
  }

  return fila;
}

// Função que cria e retorna o ponteiro para uma fila de prioridade com o número de elementos e peso especificado
FilaDePrioridade *CriarFilaDePrioridadeComPesos(int numElementos, Peso peso) {
  FilaDePrioridade *fila = malloc(sizeof(FilaDePrioridade));

  // Se a alocação não foi bem sucedida ou foi passado menos de um elemento
  if (!fila || numElementos < 1) return NULL;

  fila->Arr = malloc(sizeof(ElementoFila) * numElementos);
  fila->posicoes = malloc(sizeof(int) * numElementos);

  if (!fila->Arr || !fila->posicoes) {
    free(fila->Arr);
    free(fila->posicoes);
    free(fila);
    return NULL;
  }

  fila->numElementos = numElementos;
  fila->tamanho = numElementos;

  // Inicializa as arrays com o peso passado
  for (int i = 0; i < numElementos; i++) {
    fila->Arr[i].id = i;
    fila->Arr[i].peso = peso;
    fila->posicoes[i] = i;
  }

  return fila;
}

// Função que retorna TRUE se a fila de prioridade estiver vazia
Boolean VerificarSeFilaDePrioridadeEstaVazia(FilaDePrioridade *fila) {
  if (!fila || fila->numElementos == 0) return TRUE;
  return FALSE;
}

// Função que verifica se o elemento existe na fila de prioridade
Boolean VerificarExistenciaElemento(FilaDePrioridade *fila, int id) {
  // Verificar se os parametros são válidos
  if (!fila || id < 0 || id >= fila->tamanho) return FALSE;

  // Verifica se o elemento existe
  if (fila->posicoes[id] != -1) return TRUE;

  return FALSE;
}

// Função que imprime os valores da fila de prioridade
void ImprimirValores(FilaDePrioridade *fila) {
  if (VerificarSeFilaDePrioridadeEstaVazia(fila)) {
    printf("Fila de prioridade vazia\n");
    return;
  }
  printf("\nFila de prioridade:\n");
  for (int i = 0; i < fila->numElementos; i++) {
    printf("%i (%3.2f) ", fila->Arr[i].id, fila->Arr[i].peso);
  }
  printf("\n\n");
}

// Função que garante que a fila de prioridade esteja em heap mínimo
void AtualizarPosicao(FilaDePrioridade *fila, int posicao) {
  // Verificar se os parametros são válidos
  if (!fila || posicao <= 0 || posicao >= fila->numElementos) return;

  Peso peso = fila->Arr[posicao].peso;
  int posicaoPai = (posicao - 1) / 2;

  if (fila->Arr[posicaoPai].peso > peso) {
    TrocarElementoFila(fila, posicao, posicaoPai);
    AtualizarPosicao(fila, posicaoPai);
  }
}

// Função que altera a prioridade de um dos elementos da fila
Boolean AlterarPrioridade(FilaDePrioridade *fila, int id, Peso peso) {
  // Verificar se os parametros são válidos
  if (!fila || id < 0 || id >= fila->tamanho) return FALSE;
  if (!VerificarExistenciaElemento(fila, id)) return FALSE;

  int posicao = fila->posicoes[id];
  Peso pesoAtual = fila->Arr[posicao].peso;
  fila->Arr[posicao].peso = peso;

  if (peso < pesoAtual) {
    // Se diminuiu o peso, sobe no heap
    AtualizarPosicao(fila, posicao);
  } else if (peso > pesoAtual) {
    // Se aumentou o peso, desce no heap
    HeapifyFila(fila, posicao);
  }

  return TRUE;
}

// Função que verifica se a prioridade pode ser diminuida
Boolean DiminuirPrioridade(FilaDePrioridade *fila, int id, Peso peso) {
  // Verificar se os parametros são válidos
  if (!fila || id < 0 || id >= fila->tamanho) return FALSE;
if (!VerificarExistenciaElemento(fila, id)) return FALSE;

  int posicao = fila->posicoes[id];
  if (fila->Arr[posicao].peso <= peso) return FALSE;

  return AlterarPrioridade(fila, id, peso);
}

// Função que verifica se a prioridade pode ser aumentada
Boolean AumentarPrioridade(FilaDePrioridade *fila, int id, Peso peso) {
  // Verificar se os parametros são válidos
  if (!fila || id < 0 || id >= fila->tamanho) return FALSE;
if (!VerificarExistenciaElemento(fila, id)) return FALSE;

  int posicao = fila->posicoes[id];
  if (fila->Arr[posicao].peso >= peso) return FALSE;

  return AlterarPrioridade(fila, id, peso);
}

// Função que adiciona um elemento na fila de prioridade
Boolean AdicionarElemento(FilaDePrioridade *fila, int id, Peso peso) {
  // Verificar se os parametros são válidos
  if (!fila || fila->numElementos == fila->tamanho || id < 0 || id >= fila->tamanho) return FALSE;

  if (VerificarExistenciaElemento(fila, id)) return FALSE;

  fila->Arr[fila->numElementos].id = id;
  fila->Arr[fila->numElementos].peso = peso;
  fila->posicoes[id] = fila->numElementos;
  fila->numElementos++;
  AtualizarPosicao(fila, fila->numElementos - 1);
  return TRUE;
}

// Função que remove o elemento da fila de prioridade
int RemoverElemento(FilaDePrioridade *fila) {
  // Verificar se os parametros são válidos
  if (!fila || fila->numElementos == 0) return -1;

  ElementoFila temp = fila->Arr[0];
  fila->posicoes[fila->Arr[0].id] = -1;
  fila->Arr[0] = fila->Arr[fila->numElementos - 1];
  fila->numElementos--;
  if (fila->numElementos > 0)
    fila->posicoes[fila->Arr[0].id] = 0;
  HeapifyFila(fila, 0);
  return temp.id;
}

// Função que limpa os valores da fila de prioridade
void LimparFilaDePrioridade(FilaDePrioridade *fila) {
  if (fila == NULL) return;

  for (int i = 0; i < fila->tamanho; i++) {
    fila->Arr[i].id = -1;
    fila->Arr[i].peso = FLT_MAX;
    fila->posicoes[i] = -1;
  }
  fila->numElementos = 0;
}

// Função que destroi a fila de prioridade
void DestruirFilaDePrioridade(FilaDePrioridade *fila) {
  if (fila == NULL) return;

  free(fila->Arr);
  free(fila->posicoes);
  free(fila);
}