#include <stdio.h>
#include <stdlib.h>

#define TipoValor int
#define FormatoValor "%d"

typedef struct node {
  TipoValor valor;
  struct node *proximo;
} itemNo;

typedef struct {
  int tamanho;
  itemNo *primeiro;
} ListaLigada;

ListaLigada *CriarLista() {
  ListaLigada *lista = malloc(sizeof(ListaLigada));
  lista->tamanho = 0;
  lista->primeiro = NULL;
  return lista;
}

void InserirValorLista(ListaLigada *lista, TipoValor valor) {
  // Declarando o novo nó
  itemNo *itemNovo = malloc(sizeof(itemNo));
  itemNovo->valor = valor;

  // Se a lista estiver vazia, defina o próximo do itemNovo
  // como NULL e primeiro item como o novo nó
  if (lista->primeiro == NULL) {
    itemNovo->proximo = lista->primeiro;
    lista->primeiro = itemNovo;
    // Aumentando o tamanho
    lista->tamanho++;
    return;
  }

  itemNo *itemAtual = lista->primeiro;

  // Loop que percorre a lista até a posição correta ou o final da lista
  while (itemAtual->proximo != NULL && itemAtual->proximo->valor < valor) {
    itemAtual = itemAtual->proximo;
  }

  // Insere o itemNovo depois do itemAtual
  itemNovo->proximo = itemAtual->proximo;
  itemAtual->proximo = itemNovo;
  lista->tamanho++;
}

int RemoverValorLista(ListaLigada *lista, TipoValor valor) {
  // Se a lista estiver vazia
  if (lista->primeiro == NULL) return 0;

  itemNo *itemAtual = lista->primeiro;
  itemNo *itemProximo = itemAtual->proximo;

  // Se o primeiro item for o valor a ser removido
  if (itemAtual->valor == valor) {
    lista->primeiro = itemProximo;
    free(itemAtual);
    // Diminui o tamanho
    lista->tamanho--;
    return 1;
  }

  // Loop que percorre a lista até o próximo item ser NULL
  while (itemProximo != NULL) {
    // Se o valor do próximo item for o valor, altera o próximo do item
    // atual e libera o item com o valor
    if (itemProximo->valor == valor) {
      itemAtual->proximo = itemProximo->proximo;
      free(itemProximo);
      // Diminui o tamanho
      lista->tamanho--;
      return 1;
    }

    // Move os itens
    itemAtual = itemProximo;
    itemProximo = itemProximo->proximo;
  }
  return 0;
}

int BuscarValorLista(ListaLigada *lista, TipoValor valor) {
  itemNo *itemAtual = lista->primeiro;

  // Loop que percorre a lista até o NULL, armazenando o indice
  for (int i = 0; itemAtual != NULL && itemAtual->valor < valor; i++, itemAtual = itemAtual->proximo) {
    if (itemAtual->valor == valor) {
      return i;
    }
  }
  return -1;
}

void ImprimirLista(ListaLigada *lista) {
  // Se a lista estiver vazia
  if (lista->primeiro == NULL) {
    printf("\nA lista esta vazia\n");
    return;
  }

  itemNo *itemAtual = lista->primeiro;

  printf("\nA lista esta assim: \n");
  // Loop pra percorrer até o NULL
  while (itemAtual != NULL) {
    printf(FormatoValor " ", itemAtual->valor);
    itemAtual = itemAtual->proximo;
  }
  printf("\n\n");
}

void LimparLista(ListaLigada *lista) {
  itemNo *itemAtual = lista->primeiro;

  // Loop que percorre a lista até o NULL
  while (itemAtual != NULL) {
    itemNo *itemProximo = itemAtual->proximo;
    // Libera o itemAtual e avança para o próximo
    free(itemAtual);
    itemAtual = itemProximo;
  }
}

int main(void) {
  ListaLigada *lista = CriarLista();
  TipoValor valorDigitado = 0;
  int escolha = 0;

  while (escolha < 7) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores na lista\n");
    printf("2 - Remover valores\n");
    printf("3 - Buscar valores\n");
    printf("4 - Ver quantos itens a lista possui\n");
    printf("5 - Imprimir lista\n");
    printf("6 - Limpar lista\n");
    printf("7 - Sair\n");

    scanf("%d", &escolha);
    printf("\n");

    switch (escolha) {
    case 1:
      printf("Digite um numero negativo para parar\n");
      while (valorDigitado >= 0) {
        printf("Digite um numero para ser inserido\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) break;

        InserirValorLista(lista, valorDigitado);
        ImprimirLista(lista);
      }
      break;

    case 2:
      printf("Digite um numero negativo para parar\n");
      while (valorDigitado >= 0) {
        printf("Digite um valor para ser removido\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) break;

        int sucedido = RemoverValorLista(lista, valorDigitado);
        if (sucedido) {
          printf("O valor %d foi removido da lista\n", valorDigitado);
          ImprimirLista(lista);
        } else {
          printf("O valor não foi encontrado\n");
        }
      }
      break;

    case 3:
      printf("Digite um numero negativo para parar\n");
      while (valorDigitado >= 0) {
        printf("Digite um valor para ser buscado\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) break;

        int indiceEncontrado = BuscarValorLista(lista, valorDigitado);
        if (indiceEncontrado >= 0) {
          printf("O valor %d foi encontrado no indice %d\n", valorDigitado, indiceEncontrado);
        } else {
          printf("O valor nao foi encontrado\n");
        }
      }
      break;

    case 4:
      printf("A lista possui " FormatoValor " itens\n", lista->tamanho);
      break;

    case 5:
      ImprimirLista(lista);
      break;

    case 6:
      LimparLista(lista);
      break;
    }
  }

  LimparLista(lista);
  free(lista);

  return 0;
}
