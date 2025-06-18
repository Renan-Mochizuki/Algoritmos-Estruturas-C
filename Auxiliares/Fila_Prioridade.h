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
void TrocarElementoFila(FilaDePrioridade *fila, int idA, int idB);

// Função que miniminiza o heap, trocando o valor da raiz com o maior filho recursivamente
void HeapifyFila(FilaDePrioridade *fila, int raiz);

// Função que reorganiza a array em um heap (dos nós de baixo para cima)
void MinHeapify(FilaDePrioridade *fila);

// Função que cria e retorna o ponteiro para uma fila de prioridade com o tamanho especificado
FilaDePrioridade *CriarFilaDePrioridade(int tamanho);

// Função que cria e retorna o ponteiro para uma fila de prioridade com o número de elementos e peso especificado
FilaDePrioridade *CriarFilaDePrioridadeComPesos(int numElementos, Peso peso);

// Função que retorna TRUE se a fila de prioridade estiver vazia
Boolean VerificarSeFilaDePrioridadeEstaVazia(FilaDePrioridade *fila);

// Função que verifica se o elemento existe na fila de prioridade
Boolean VerificarExistenciaElemento(FilaDePrioridade *fila, int id);
// Função que imprime os valores da fila de prioridade
void ImprimirValores(FilaDePrioridade *fila);

// Função que garante que a fila de prioridade esteja em heap mínimo
void AtualizarPosicao(FilaDePrioridade *fila, int posicao);

// Função que altera a prioridade de um dos elementos da fila
Boolean AlterarPrioridade(FilaDePrioridade *fila, int id, Peso peso);

// Função que verifica se a prioridade pode ser diminuida
Boolean DiminuirPrioridade(FilaDePrioridade *fila, int id, Peso peso);

// Função que verifica se a prioridade pode ser aumentada
Boolean AumentarPrioridade(FilaDePrioridade *fila, int id, Peso peso);
// Função que adiciona um elemento na fila de prioridade
Boolean AdicionarElemento(FilaDePrioridade *fila, int id, Peso peso);

// Função que remove o elemento da fila de prioridade
int RemoverElemento(FilaDePrioridade *fila);

// Função que limpa os valores da fila de prioridade
void LimparFilaDePrioridade(FilaDePrioridade *fila);

// Função que destroi a fila de prioridade
void DestruirFilaDePrioridade(FilaDePrioridade *fila);