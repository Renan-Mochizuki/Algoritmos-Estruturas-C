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
} Pilha;

// Função que retorna o ponteiro para uma pilha
Pilha * CriarPilha(){
    Pilha * pilha = malloc(sizeof(Pilha));
    pilha->primeiro = NULL;
    pilha->ultimo = NULL;
    pilha->tamanho = 0;
    return pilha;
}

// Função que limpa a pilha
void LimparPilha(Pilha * pilha){
    itemNo *itemAtual = pilha->primeiro;

    // Loop que percorre a pilha
    while (itemAtual != NULL) {
        itemNo *itemProximo = itemAtual->proximo;
        // Libera o itemAtual e avança para o próximo
        free(itemAtual);
        itemAtual = itemProximo;
    }

    // Resetando parâmetros
    pilha->primeiro = NULL;
    pilha->ultimo = NULL;
    pilha->tamanho = 0;
}

// Função que destroi a pilha
void DestruirPilha(Pilha * pilha){
    LimparPilha(pilha);
    free(pilha);
}

// Função que imprime os valores da pilha
void ImprimirValores(Pilha * pilha){
    if(pilha->tamanho == 0){
        printf("\nA pilha esta vazia\n");
        return;
    }

    itemNo * itemAtual = pilha->primeiro;

    printf("\nPilha: ");
    // Loop que percorre a pilha
    for(int i = 0; i < pilha->tamanho; i++){
        printf("%d, ", itemAtual->valor);
        itemAtual = itemAtual->proximo;
    }
    printf("\n\n");
}

// Função que vai inserir um valor no topo da pilha
Boolean InserirValor(Pilha * pilha, TipoValor valor){
    itemNo * novoItem = malloc(sizeof(itemNo));
    novoItem->valor = valor;
    novoItem->proximo = NULL;
    
    // Se a pilha estiver vazia
    if(!pilha->primeiro){
        pilha->primeiro = novoItem;
        pilha->ultimo = novoItem;
    } else { // pilha não está vazia
        itemNo * ultimoAtual = pilha->ultimo;
        ultimoAtual->proximo = novoItem;

        // Atualiza o último item da pilha
        pilha->ultimo = novoItem;
    }

    pilha->tamanho++;
    return TRUE;
}

// Função que vai remover o valor do topo da pilha
Boolean RemoverValor(Pilha * pilha) {
    // Se a pilha estiver vazia
    if (pilha->tamanho == 0) return FALSE;

    // Se a pilha tiver apenas um item
    if (pilha->tamanho == 1) {
        free(pilha->primeiro);
        pilha->primeiro = NULL;
        pilha->ultimo = NULL;
        pilha->tamanho = 0;
        return TRUE;
    }

    itemNo * itemAtual = pilha->primeiro;

    // Loop que percorre a pilha até o penúltimo item
    for(int i = 0; i < pilha->tamanho - 2; i++){
        itemAtual = itemAtual->proximo;
    }

    // Libera o último item da pilha
    free(itemAtual->proximo);
    itemAtual->proximo = NULL;
    pilha->ultimo = itemAtual;
    pilha->tamanho--;

    return TRUE;
}

// Função que busca um valor na pilha
int BuscarValor(Pilha * pilha, TipoValor valor){
    itemNo * itemAtual = pilha->primeiro;

    // Loop que percorre a pilha
    for(int i = 0; i < pilha->tamanho; i++){
        if(itemAtual->valor == valor){
            return i;
        }
        itemAtual = itemAtual->proximo;
    }

    return -1;
}

int main(void){
    TipoValor valorDigitado;
    int escolha = 1;

    Pilha * pilha = CriarPilha();

    while (escolha > 0 && escolha < 7) {
        printf("\nQual acao deseja realizar?\n");
        printf("1 - Inserir valores na pilha\n");
        printf("2 - Remover valor do topo da pilha\n");
        printf("3 - Buscar valores\n");
        printf("4 - Ver quantos itens a pilha possui\n");
        printf("5 - Imprimir pilha\n");
        printf("6 - Limpar pilha\n");
        printf("7 - Sair\n");

        scanf("%d", &escolha);
        printf("\n");

        valorDigitado = 0;

        switch (escolha) {
        case 1:
            printf("Digite um valor negativo para parar\n");
            while (valorDigitado >= 0) {
                printf("Digite um valor para ser inserido\n");
                scanf(FormatoValor, &valorDigitado);

                if (valorDigitado < 0) break;

                Boolean funcaoSucedida = InserirValor(pilha, valorDigitado);

                if (funcaoSucedida) {
                    ImprimirValores(pilha);
                } else {
                    printf("\nA capacidade da pilha foi ultrapassada\n");
                    break;
                }
            }
            break;

        case 2: {
            Boolean funcaoSucedida = RemoverValor(pilha);

            if (funcaoSucedida) {
                ImprimirValores(pilha);
            } else {
                printf("\nA pilha esta vazia\n");
            }

            break;
        }

        case 3:
            if (pilha->tamanho == 0) {
                printf("A pilha esta vazia\n");
                break;
            }

            printf("Digite um valor negativo para parar\n");
            while (valorDigitado >= 0) {
                printf("Digite um valor para ser buscado\n");
                scanf(FormatoValor, &valorDigitado);

                if (valorDigitado < 0) break;

                int posicaoEncontrada = BuscarValor(pilha, valorDigitado);

                if (posicaoEncontrada == -1) {
                    printf("\nO valor nao foi encontrado\n\n");
                } else {
                    printf("\nO valor foi encontrado na posicao %d\n\n", posicaoEncontrada);
                }
            }
            break;

        case 4:
            printf("A pilha possui %d itens\n", pilha->tamanho);
            break;

        case 5:
            ImprimirValores(pilha);
            break;

        case 6:
            LimparPilha(pilha);
            printf("A pilha foi limpa\n");
            break;
        }
    }

    DestruirPilha(pilha);

    return 0;
}