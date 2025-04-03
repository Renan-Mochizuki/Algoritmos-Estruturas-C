#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct {
    TipoValor * valores;
    int inicio;
    int fim;
    int capacidade;
} Fila;

// Função que retorna o ponteiro para uma fila sendo passado a capacidade
Fila * CriarFila(int capacidade){
    Fila * fila = malloc(sizeof(Fila));
    fila->valores = malloc(capacidade * sizeof(TipoValor));
    fila->capacidade = capacidade;
    fila->inicio = 0;
    fila->fim = 0;
    return fila;
}

// Função que limpa a fila
void LimparFila(Fila * fila){
    fila->inicio = 0;
    fila->fim = 0;
}

// Função que destroi a fila
void DestruirFila(Fila * fila){
    free(fila->valores);
    free(fila);
}

// Função que imprime os valores da fila
void ImprimirValores(Fila * fila){
    if(fila->inicio == fila->fim){
        printf("\nA fila esta vazia\n");
        return;
    }

    printf("\nFila: ");
    // Loop que percorre a fila
    for(int i = fila->inicio; i < fila->fim; i++){
        printf("%d, ", fila->valores[i % fila->capacidade]);
    }
    printf("\n\n");
}

// Função que retorna o tamanho da fila
int RetornarTamanho(Fila * fila){
    return fila->fim - fila->inicio;
}

// Função que vai inserir um valor no final da fila
Boolean InserirValor(Fila * fila, TipoValor valor){
    int tamanhoFila = RetornarTamanho(fila);

    // Se a fila estiver cheia, não é possível adicionar mais elementos
    if(tamanhoFila == fila->capacidade) return FALSE;

    // Insire o valor no fim da fila
    // fila->fim % fila->capacidade garante que sempre utilizemos a array devidamente
    // O próximo item depois do último da array, é o primeiro da array (como uma lista circular)
    fila->valores[fila->fim % fila->capacidade] = valor;
    fila->fim++;
    return TRUE;
}

// Função que vai remover o primeiro valor da fila
Boolean RemoverValor(Fila * fila) {
    // Se a fila estiver vazia
    if (fila->inicio == fila->fim) return FALSE;

    // Incrementa o índice de início para "remover"/ignorar o valor
    fila->inicio++;
    return TRUE;
}

// Função que busca um valor na fila
int BuscarValor(Fila * fila, TipoValor valor){
    // Loop que percorre as posições armazenadas da fila
    for(int i = fila->inicio; i < fila->fim; i++){
        // i % fila->capacidade, pois a fila é circular
        if(fila->valores[i % fila->capacidade] == valor){
            // Subtraindo fila->inicio e 1 para retornar 0 se o item estiver primeira posição
            return i - fila->inicio;
        }
    }

    return -1;
}

int main(void){
    int capacidade;
    TipoValor valorDigitado;
    int escolha = 1;

    printf("Digite a capacidade da fila\n");
    scanf("%d", &capacidade);

    Fila* fila = CriarFila(capacidade);

    while (escolha > 0 && escolha < 7) {
        printf("\nQual acao deseja realizar?\n");
        printf("1 - Inserir valores na fila\n");
        printf("2 - Remover proximo valor da fila\n");
        printf("3 - Buscar valores\n");
        printf("4 - Ver quantos itens a fila possui\n");
        printf("5 - Imprimir fila\n");
        printf("6 - Limpar fila\n");
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

                Boolean funcaoSucedida = InserirValor(fila, valorDigitado);

                if (funcaoSucedida) {
                    ImprimirValores(fila);
                } else {
                    printf("\nA capacidade da fila foi ultrapassada\n");
                    break;
                }
            }
            break;

        case 2: {
            Boolean funcaoSucedida = RemoverValor(fila);

            if (funcaoSucedida) {
                ImprimirValores(fila);
            } else {
                printf("\nA fila esta vazia\n");
            }

            break;
        }

        case 3:
            if (RetornarTamanho(fila) == 0) {
                printf("A fila esta vazia\n");
                break;
            }

            printf("Digite um valor negativo para parar\n");
            while (valorDigitado >= 0) {
                printf("Digite um valor para ser buscado\n");
                scanf(FormatoValor, &valorDigitado);

                if (valorDigitado < 0) break;

                int posicaoEncontrada = BuscarValor(fila, valorDigitado);

                if (posicaoEncontrada == -1) {
                    printf("\nO valor nao foi encontrado\n");
                } else {
                    printf("\nO valor foi encontrado na posicao %d\n", posicaoEncontrada);
                }
            }
            break;

        case 4:
            printf("A fila possui %d itens\n", RetornarTamanho(fila));
            break;

        case 5:
            ImprimirValores(fila);
            break;

        case 6:
            LimparFila(fila);
            printf("A fila foi limpa\n");
            break;
        }
    }

    DestruirFila(fila);

    return 0;
}