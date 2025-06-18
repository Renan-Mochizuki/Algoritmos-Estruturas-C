#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct nodeFila {
    TipoValor valor;
    struct nodeFila * proximo;
} itemNo;	

typedef struct {
    itemNo * primeiro;
    itemNo * ultimo;
    int tamanho;
} Fila;

// Função que retorna o ponteiro para uma fila
Fila * CriarFila(){
    Fila * fila = malloc(sizeof(Fila));
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->tamanho = 0;
    return fila;
}

// Função que limpa a fila
void LimparFila(Fila * fila){
    itemNo *itemAtual = fila->primeiro;

    // Loop que percorre a fila
    for(int i = 0; i < fila->tamanho; i++){
        itemNo *itemProximo = itemAtual->proximo;
        // Libera o itemAtual e avança para o próximo
        free(itemAtual);
        itemAtual = itemProximo;
    }

    // Resetando parâmetros
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->tamanho = 0;
}

// Função que destroi a fila
void DestruirFila(Fila * fila){
    LimparFila(fila);
    free(fila);
}

// Função que imprime os valores da fila
void ImprimirValoresFila(Fila * fila){
    if(fila->tamanho == 0){
        printf("\nA fila esta vazia\n");
        return;
    }

    itemNo * itemAtual = fila->primeiro;

    printf("\nFila: ");
    // Loop que percorre a fila
    for(int i = 0; i < fila->tamanho; i++){
        printf("%d, ", itemAtual->valor);
        itemAtual = itemAtual->proximo;
    }
    printf("\n\n");
}

// Função que vai inserir um valor no final da fila
Boolean InserirValorFila(Fila * fila, TipoValor valor){
    itemNo * novoItem = malloc(sizeof(itemNo));
    novoItem->valor = valor;
    novoItem->proximo = NULL;

    // Se a fila estiver vazia
    if(!fila->primeiro){
        fila->primeiro = novoItem;
        fila->ultimo = novoItem;
    } else { // Fila não está vazia
        itemNo * ultimoAtual = fila->ultimo;
        ultimoAtual->proximo = novoItem;

        // Atualiza o último item da fila
        fila->ultimo = novoItem;
    }

    fila->tamanho++;
    return TRUE;
}

// Função que vai remover o primeiro valor da fila
Boolean RemoverValorFila(Fila * fila) {
    // Se a fila estiver vazia
    if (fila->tamanho == 0) return FALSE;

    itemNo * primeiroItem = fila->primeiro;

    // Alterando o primeiro da fila
    fila->primeiro = primeiroItem->proximo;

    free(primeiroItem);
    fila->tamanho--;

    return TRUE;
}

// Função que busca um valor na fila
int BuscarValorFila(Fila * fila, TipoValor valor){
    itemNo * itemAtual = fila->primeiro;

    // Loop que percorre a fila
    for(int i = 0; i < fila->tamanho; i++){
        if(itemAtual->valor == valor){
            return i;
        }
        itemAtual = itemAtual->proximo;
    }

    return -1;
}

// Função que verifica se a fila está vazia
Boolean FilaVazia(Fila *fila) {
  if (fila->tamanho == 0) return TRUE;
  return FALSE;
}