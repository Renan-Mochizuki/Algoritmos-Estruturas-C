#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct {
  TipoValor *valores;
  int tamanho;
  int capacidade;
} Pilha;

// Função que retorna o ponteiro para uma pilha sendo passado a capacidade
Pilha *CriarPilha(int capacidade) {
  Pilha *pilha = malloc(sizeof(Pilha));
  pilha->valores = malloc(capacidade * sizeof(TipoValor));
  pilha->capacidade = capacidade;
  pilha->tamanho = 0;
  return pilha;
}

// Função que limpa a pilha
void LimparPilha(Pilha *pilha) {
  pilha->tamanho = 0;
}

// Função que destroi a pilha
void DestruirPilha(Pilha *pilha) {
  free(pilha->valores);
  free(pilha);
}

// Função que imprime os valores da pilha
void ImprimirValoresPilha(Pilha *pilha) {
  if (pilha->tamanho == 0) {
    printf("\nA pilha esta vazia\n");
    return;
  }

  printf("\nPilha: ");
  // Loop que percorre a pilha
  for (int i = 0; i < pilha->tamanho; i++) {
    printf("%d, ", pilha->valores[i]);
  }
  printf("\n\n");
}

// Função que vai inserir um valor no topo da pilha
Boolean InserirValorPilha(Pilha *pilha, TipoValor valor) {
  // Se a pilha estiver cheia, não é possível adicionar mais elementos
  if (pilha->tamanho == pilha->capacidade) return FALSE;

  // Insire o valor no topo da pilha
  pilha->valores[pilha->tamanho] = valor;
  pilha->tamanho++;
  return TRUE;
}

// Função que vai remover o valor do topo da pilha
Boolean RemoverValorPilha(Pilha *pilha) {
  // Se a pilha estiver vazia
  if (pilha->tamanho == 0) return FALSE;

  // Diminue o índice do topo para "remover"/ignorar o valor
  pilha->tamanho--;
  return TRUE;
}

// Função que busca um valor na pilha
int BuscarValorPilha(Pilha *pilha, TipoValor valor) {
  // Loop que percorre a pilha
  for (int i = 0; i < pilha->tamanho; i++) {
    if (pilha->valores[i] == valor) {
      return i;
    }
  }

  return -1;
}

// Função que verifica se a pilha está vazia
Boolean PilhaVazia(Pilha *pilha) {
  if (pilha->tamanho == 0) return TRUE;
  return FALSE;
}

int main(void) {
  int capacidade;
  TipoValor valorDigitado;
  int escolha = 1;

  printf("Digite a capacidade da pilha\n");
  scanf("%d", &capacidade);

  Pilha *pilha = CriarPilha(capacidade);

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

        Boolean funcaoSucedida = InserirValorPilha(pilha, valorDigitado);

        if (funcaoSucedida) {
          ImprimirValoresPilha(pilha);
        } else {
          printf("\nA capacidade da pilha foi ultrapassada\n");
          break;
        }
      }
      break;

    case 2: {
      Boolean funcaoSucedida = RemoverValorPilha(pilha);

      if (funcaoSucedida) {
        ImprimirValoresPilha(pilha);
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

        int posicaoEncontrada = BuscarValorPilha(pilha, valorDigitado);

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
      ImprimirValoresPilha(pilha);
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