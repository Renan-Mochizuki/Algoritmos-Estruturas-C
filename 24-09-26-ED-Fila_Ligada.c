#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct nodeFila {
  TipoValor valor;
  struct nodeFila *proximo;
} itemNo;

typedef struct {
  itemNo *primeiro;
  itemNo *ultimo;
  int tamanho;
} Fila;

// Função que retorna o ponteiro para uma fila
Fila *CriarFila() {
  Fila *fila = malloc(sizeof(Fila));
  fila->primeiro = NULL;
  fila->ultimo = NULL;
  fila->tamanho = 0;
  return fila;
}

// Função que limpa a fila
void LimparFila(Fila *fila) {
  itemNo *itemAtual = fila->primeiro;

  // Loop que percorre a fila
  for (int i = 0; i < fila->tamanho; i++) {
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
void DestruirFila(Fila *fila) {
  LimparFila(fila);
  free(fila);
}

// Função que imprime os valores da fila
void ImprimirValoresFila(Fila *fila) {
  if (fila->tamanho == 0) {
    printf("\nA fila esta vazia\n");
    return;
  }

  itemNo *itemAtual = fila->primeiro;

  printf("\nFila: ");
  // Loop que percorre a fila
  for (int i = 0; i < fila->tamanho; i++) {
    printf("%d, ", itemAtual->valor);
    itemAtual = itemAtual->proximo;
  }
  printf("\n\n");
}

// Função que vai inserir um valor no final da fila
Boolean InserirValorFila(Fila *fila, TipoValor valor) {
  itemNo *novoItem = malloc(sizeof(itemNo));
  novoItem->valor = valor;
  novoItem->proximo = NULL;

  // Se a fila estiver vazia
  if (!fila->primeiro) {
    fila->primeiro = novoItem;
    fila->ultimo = novoItem;
  } else { // Fila não está vazia
    itemNo *ultimoAtual = fila->ultimo;
    ultimoAtual->proximo = novoItem;

    // Atualiza o último item da fila
    fila->ultimo = novoItem;
  }

  fila->tamanho++;
  return TRUE;
}

// Função que vai remover o primeiro valor da fila
Boolean RemoverValorFila(Fila *fila) {
  // Se a fila estiver vazia
  if (fila->tamanho == 0) return FALSE;

  itemNo *primeiroItem = fila->primeiro;

  // Alterando o primeiro da fila
  fila->primeiro = primeiroItem->proximo;

  free(primeiroItem);
  fila->tamanho--;

  return TRUE;
}

// Função que busca um valor na fila
int BuscarValorFila(Fila *fila, TipoValor valor) {
  itemNo *itemAtual = fila->primeiro;

  // Loop que percorre a fila
  for (int i = 0; i < fila->tamanho; i++) {
    if (itemAtual->valor == valor) {
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

int main(void) {
  TipoValor valorDigitado;
  int escolha = 1;

  Fila *fila = CriarFila();

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

        Boolean funcaoSucedida = InserirValorFila(fila, valorDigitado);

        if (funcaoSucedida) {
          ImprimirValoresFila(fila);
        } else {
          printf("\nA capacidade da fila foi ultrapassada\n");
          break;
        }
      }
      break;

    case 2: {
      Boolean funcaoSucedida = RemoverValorFila(fila);

      if (funcaoSucedida) {
        ImprimirValoresFila(fila);
      } else {
        printf("\nA fila esta vazia\n");
      }

      break;
    }

    case 3:
      if (fila->tamanho == 0) {
        printf("A fila esta vazia\n");
        break;
      }

      printf("Digite um valor negativo para parar\n");
      while (valorDigitado >= 0) {
        printf("Digite um valor para ser buscado\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) break;

        int posicaoEncontrada = BuscarValorFila(fila, valorDigitado);

        if (posicaoEncontrada == -1) {
          printf("\nO valor nao foi encontrado\n\n");
        } else {
          printf("\nO valor foi encontrado na posicao %d\n\n", posicaoEncontrada);
        }
      }
      break;

    case 4:
      printf("A fila possui %d itens\n", fila->tamanho);
      break;

    case 5:
      ImprimirValoresFila(fila);
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