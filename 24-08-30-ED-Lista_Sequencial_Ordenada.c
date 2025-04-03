#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1

typedef int Boolean;
typedef int TipoValorLista;

// Declarando struct da lista, com um ponteiro para uma array, um inteiro para a
// posição que está livre, que é equivalente ao tamanho e um inteiro para a
// capacidade da array
typedef struct {
  TipoValorLista *a;
  int livre;
  int capacidade;
} ListaSequencial;

// Função que retorna o ponteiro para a lista
ListaSequencial *CriarLista(int capacidade) {
  ListaSequencial *lista = (ListaSequencial *)malloc(sizeof(ListaSequencial));
  // Alocando memória para a array
  lista->a = malloc(capacidade * sizeof(TipoValorLista));
  lista->livre = 0;
  lista->capacidade = capacidade;

  return lista;
}

void LimparLista(ListaSequencial *lista) {
  // Libera a array primeiro
  free(lista->a);
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
// Busca binária
int BuscarValor(ListaSequencial *lista, TipoValorLista valor) {
  int tamanho = lista->livre;
  int inicio = 0;
  // Como o índice começa em 0, fazemos tamanho - 1, para pegar o último índice
  int fim = tamanho - 1;

  // Para o loop quando o fim
  while (inicio <= fim) {
    // Pega o índice do meio e seu valor
    int meio = (inicio + fim) / 2;
    int valorMeio = lista->a[meio];

    // Se o valor do meio for o valor procurado, retorne o índice
    if (valorMeio == valor) return meio;

    // Se o valor do meio for maior que o valor procurado, então o valor está
    // na metade esquerda. Se o valor for menor, o valor está na metade direita
    if (valorMeio > valor) fim = meio - 1;
    if (valorMeio < valor) inicio = meio + 1;
  }

  return -1;
}

// Função que retorna TRUE (1) caso o valor seja inserido com sucesso
Boolean InserirValor(ListaSequencial *lista, TipoValorLista valor) {
  int i;
  int tamanho = lista->livre;
  int capacidade = lista->capacidade;

  // Verifica se o tamanho está válido
  if (tamanho >= capacidade) {
    return FALSE;
  }

  // Inserir valor ordenadamente
  // Loop que começa pelo fim da lista e vai até quando o valor anterior for
  // menor que o valor a ser inserido, i > 0 necessário, para caso o valor a ser inserido
  // seja menor que o menor valor da lista
  for (i = lista->livre; i > 0 && lista->a[i - 1] > valor; i--) {
    // Move todos os itens para a direita
    // para liberar espaço para o novo valor naquele indice
    lista->a[i] = lista->a[i - 1];
  }

  // Atribui o valor e aumenta o tamanho
  lista->a[i] = valor;
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
  int capacidade = 1000;
  ListaSequencial *listaNova = CriarLista(capacidade);
  int escolha = 1;

  while (escolha < 5) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores\n");
    printf("2 - Buscar valores\n");
    printf("3 - Remover valores\n");
    printf("4 - Imprimir lista\n");
    printf("5 - Sair\n");
    scanf("%d", &escolha);

    int numeroDigitado = 1;

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

          Boolean funcaoSucedida = InserirValor(listaNova, numeroDigitado);

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
          printf("O valor %d esta na posição %d\n", numeroDigitado, indiceValor);
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