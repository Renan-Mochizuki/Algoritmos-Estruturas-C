#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct node {
    TipoValor valor;
    struct node * proximo;
} itemNo;	

typedef struct {
    itemNo * primeiro;
    itemNo * ultimo;
    int tamanho;
} Fila;

// Função que retorna o ponteiro para uma fila
Fila * CriarFila();

// Função que limpa a fila
void LimparFila(Fila * fila);

// Função que destroi a fila
void DestruirFila(Fila * fila);

// Função que imprime os valores da fila
void ImprimirValoresFila(Fila * fila);

// Função que vai inserir um valor no final da fila
Boolean InserirValorFila(Fila * fila, TipoValor valor);

// Função que vai remover o primeiro valor da fila
Boolean RemoverValorFila(Fila * fila);

// Função que busca um valor na fila
int BuscarValorFila(Fila * fila, TipoValor valor);

// Função que verifica se a fila está vazia
Boolean FilaVazia(Fila *fila);