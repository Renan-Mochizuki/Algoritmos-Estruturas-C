#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define TAMANHO_MAXIMO 1000

typedef int Boolean;
typedef int TipoValorLista;

// Declarando struct da lista, com uma array, e um inteiro para a posição que
// está livre, que é equivalente ao tamanho
typedef struct {
  TipoValorLista a[TAMANHO_MAXIMO];
  int livre;
} ListaSequencial;

// Função que retorna o ponteiro para a lista
ListaSequencial *CriarLista() {
  ListaSequencial *lista = (ListaSequencial *)malloc(sizeof(ListaSequencial));
  lista->livre = 0;

  return lista;
}

void LimparLista(ListaSequencial *lista) {
  // Libera o bloco
  free(lista);
}

void ImprimirLista(ListaSequencial *lista) {
  int tamanho = lista->livre;

  if (tamanho == 0) {
    printf("\nA lista esta vazia\n");
    return;
  }

  printf("\nA lista esta assim:\n");
  // Loop que percorre a lista inteira
  for (int i = 0; i < tamanho; i++) {
    printf("%d, ", lista->a[i]);
  }
  printf("\n");
}

// Função que retorna o indice do valor caso encontrado, ou retorna -1
int BuscarValor(ListaSequencial *lista, TipoValorLista valor) {
  int tamanho = lista->livre;
  // Loop que percorre a lista inteira
  for (int i = 0; i < tamanho; i++) {
    if (lista->a[i] == valor) {
      return i;
    }
  }

  return -1;
}

// Função que retorna TRUE (1) caso o valor seja inserido com sucesso
Boolean InserirValor(ListaSequencial *lista, TipoValorLista valor, int indice) {
  int tamanho = lista->livre;

  // Verifica se o tamanho e o indice estão válidos
  if (tamanho >= TAMANHO_MAXIMO || indice < 0 || indice > tamanho) {
    return FALSE;
  }

  // Loop que começa pelo fim da lista e vai até o indice que foi passado
  for (int i = lista->livre; i > indice; i--) {
    // Move todos os itens para a direita
    // para liberar espaço para o novo valor naquele indice
    lista->a[i] = lista->a[i - 1];
  }

  // Atribui o valor e aumenta o tamanho
  lista->a[indice] = valor;
  lista->livre++;

  return TRUE;
}

// Função que retorna TRUE (1) caso o valor seja removido com sucesso
Boolean RemoverValor(ListaSequencial *lista, TipoValorLista valor) {
  int indice = BuscarValor(lista, valor);

  // Se não for encontrado o valor, retorna FALSE
  if (indice < 0) {
    return FALSE;
  }

  // Diminuindo o tamanho da lista
  lista->livre--;
  int tamanho = lista->livre;

  // Loop que começa no indice encontrado e vai até o final da lista
  for (int i = indice; i < tamanho; i++) {
    // Move todos os itens para a esquerda
    // para ocupar espaço do valor removido
    lista->a[i] = lista->a[i + 1];
  }

  return TRUE;
}

int main(void) {
  ListaSequencial *listaNova = CriarLista();
  int escolha = 1;

  while (escolha < 5) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores\n");
    printf("2 - Buscar valores\n");
    printf("3 - Remover valores\n");
    printf("4 - Imprimir lista\n");
    printf("5 - Sair\n");
    scanf("%d", &escolha);

    int numeroDigitado = 1, indiceDigitado = 1;
    int tamanho;

    switch (escolha) {
      case 1:
        printf("Digite um valor para ser inserido na lista:\n");
        printf("Digite um valor negativo para parar:\n");

        // Loop que para caso for digitado um valor negativo
        while (numeroDigitado >= 0) {
          scanf("%d", &numeroDigitado);

          if (numeroDigitado < 0) {
            break;
          }

          // Pega o tamanho e reseta o indiceDigitado
          tamanho = listaNova->livre;
          indiceDigitado = TAMANHO_MAXIMO;

          // Loop que para caso o indiceDigitado for menor que o tamanho da lista
          // ou menor que 0
          while (indiceDigitado > tamanho && indiceDigitado > 0) {
            printf("Digite um indice ate %d \n", tamanho);
            printf("Ou um indice negativo para inserir automaticamente:\n");

            scanf("%d", &indiceDigitado);
          }
          // Se o indiceDigitado for negativo, atribui o tamanho no indiceLista
          int indiceLista = indiceDigitado;
          if (indiceDigitado < 0) {
            indiceLista = tamanho;
          }

          Boolean funcaoSucedida =
              InserirValor(listaNova, numeroDigitado, indiceLista);

          if (funcaoSucedida) {
            ImprimirLista(listaNova);
          } else {
            printf("\nO valor nao foi inserido:\n");
          }

          printf("\nDigite um valor para ser inserido na lista:\n");
        }

        break;
      case 2:
        printf("Digite um valor para ser buscado na lista:\n");
        scanf("%d", &numeroDigitado);
        int indiceValor = BuscarValor(listaNova, numeroDigitado);

        // Se for encontrado o valor
        if (indiceValor >= 0) {
          printf("O valor %d esta na posicao %d\n", numeroDigitado, indiceValor);
        } else {
          printf("Valor nao encontrado");
        }
        break;
      case 3:
        printf("Digite um valor para ser removido na lista:\n");
        printf("Digite um valor negativo para parar:\n");

        // Loop que para caso for digitado um valor negativo
        while (numeroDigitado >= 0) {
          scanf("%d", &numeroDigitado);

          Boolean funcaoSucedida = RemoverValor(listaNova, numeroDigitado);

          // Se o valor tiver sido removido
          if (funcaoSucedida) {
            ImprimirLista(listaNova);
          } else {
            printf("\nO valor nao foi removido:\n");
          }

          printf("Digite um valor para ser removido na lista:\n");
        }
        break;
      case 4:
        ImprimirLista(listaNova);
        break;
    }
  }

  ImprimirLista(listaNova);

  LimparLista(listaNova);
}