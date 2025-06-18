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
} listaLigada;

listaLigada *CriarLista() {
  listaLigada *lista = malloc(sizeof(listaLigada));
  lista->tamanho = 0;
  lista->primeiro = NULL;
  return lista;
}

void InserirInicioLista(listaLigada *lista, TipoValor valor) {
  // Declarando o novo nó com o valor
  itemNo *itemNovo = malloc(sizeof(itemNo));
  itemNovo->valor = valor;
  // Aumentando o tamanho
  lista->tamanho++;

  // Definindo o proximo do itemNovo como o primeiro item da lista (pode ser
  // NULL) e alterando o primeiro item da lista como o item novo
  itemNovo->proximo = lista->primeiro;
  lista->primeiro = itemNovo;
}

void InserirFimLista(listaLigada *lista, TipoValor valor) {
  // Declarando o novo nó
  itemNo *itemNovo = malloc(sizeof(itemNo));
  itemNovo->valor = valor;
  itemNovo->proximo = NULL;
  // Aumentando o tamanho
  lista->tamanho++;

  // Se a lista estiver vazia, defina o primeiro item como o novo nó
  if (lista->primeiro == NULL) {
    lista->primeiro = itemNovo;
    return;
  }

  itemNo *itemAtual = lista->primeiro;

  // Loop para percorrer até o próximo item ser NULL
  while (itemAtual->proximo != NULL) {
    itemAtual = itemAtual->proximo;
  }

  // Atribuindo o último item como o itemNovo
  itemAtual->proximo = itemNovo;
}

void InserirMeioLista(listaLigada *lista, TipoValor valor, int indice) {
  // Declarando o novo nó
  itemNo *itemNovo = malloc(sizeof(itemNo));
  itemNovo->valor = valor;

  // Se a lista estiver vazia, defina o próximo do itemNovo
  // como NULL e primeiro item como o novo nó
  if (lista->primeiro == NULL || indice == 0) {
    itemNovo->proximo = lista->primeiro;
    lista->primeiro = itemNovo;
    // Aumentando o tamanho
    lista->tamanho++;
    return;
  }

  itemNo *itemAtual = lista->primeiro;

  // Loop que percorre a lista até o índice desejado ou o final da lista
  for (int i = 0; i < indice - 1 && itemAtual->proximo != NULL; i++) {
    itemAtual = itemAtual->proximo;
  }

  // Insere o itemNovo depois do itemAtual
  itemNovo->proximo = itemAtual->proximo;
  itemAtual->proximo = itemNovo;
  lista->tamanho++;
}

int RemoverValorLista(listaLigada *lista, TipoValor valor) {
  // Se a lista estiver vazia
  if (lista->primeiro == NULL) {
    return 0;
  }

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

int BuscarValorLista(listaLigada *lista, TipoValor valor) {
  itemNo *itemAtual = lista->primeiro;

  // Loop que percorre a lista até o NULL, armazenando o indice
  for (int i = 0; itemAtual != NULL; i++, itemAtual = itemAtual->proximo) {
    if (itemAtual->valor == valor) {
      return i;
    }
  }
  return -1;
}

void ImprimirLista(listaLigada *lista) {
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

void LimparLista(listaLigada *lista) {
  itemNo *itemAtual = lista->primeiro;

  // Loop que percorre a lista até o NULL
  while (itemAtual != NULL) {
    itemNo *itemProximo = itemAtual->proximo;
    // Libera o itemAtual e avança para o próximo
    free(itemAtual);
    itemAtual = itemProximo;
  }
  // Libera a lista
  free(lista);
}

int main(void) {
  listaLigada *lista = CriarLista();
  TipoValor valorDigitado = 0;
  int indiceDigitado = 0;
  int escolha = 1;

  while (escolha < 8 && escolha > 0) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores no inicio da lista\n");
    printf("2 - Inserir valores no fim da lista\n");
    printf("3 - Inserir valores na lista com indice\n");
    printf("4 - Remover valores\n");
    printf("5 - Buscar valores\n");
    printf("6 - Ver quantos itens a lista possui\n");
    printf("7 - Imprimir lista\n");
    printf("8 - Sair\n");

    scanf("%d", &escolha);
    printf("\n");

    switch (escolha) {
    case 1:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um numero para ser inserido\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) {
          break;
        }

        InserirInicioLista(lista, valorDigitado);
        ImprimirLista(lista);
      } while (valorDigitado > 0);
      break;

    case 2:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um numero para ser inserido\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) {
          break;
        }

        InserirFimLista(lista, valorDigitado);
        ImprimirLista(lista);
      } while (valorDigitado > 0);
      break;

    case 3:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um numero para ser inserido\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) {
          break;
        }

        printf("Digite um indice para inserir o valor\n");
        scanf("%d", &indiceDigitado);

        InserirMeioLista(lista, valorDigitado, indiceDigitado);
        ImprimirLista(lista);
      } while (valorDigitado > 0);
      break;

    case 4:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um valor para ser removido\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) {
          break;
        }

        int sucedido = RemoverValorLista(lista, valorDigitado);
        if (sucedido) {
          printf("O valor %d foi removido da lista\n", valorDigitado);
          ImprimirLista(lista);
        } else {
          printf("O valor não foi encontrado\n");
        }
      } while (valorDigitado > 0);
      break;

    case 5:
      printf("Digite um numero negativo para parar\n");
      do {
        printf("Digite um valor para ser buscado\n");
        scanf(FormatoValor, &valorDigitado);

        if (valorDigitado < 0) {
          break;
        }

        int indiceEncontrado = BuscarValorLista(lista, valorDigitado);
        if (indiceEncontrado >= 0) {
          printf("O valor %d foi encontrado no indice %d\n", valorDigitado, indiceEncontrado);
        } else {
          printf("O valor nao foi encontrado\n");
        }
      } while (valorDigitado > 0);
      break;

    case 6:
      printf("A lista possui " FormatoValor " itens\n", lista->tamanho);
      break;

    case 7:
      ImprimirLista(lista);
      break;
    }
  }

  LimparLista(lista);

  return 0;
}
