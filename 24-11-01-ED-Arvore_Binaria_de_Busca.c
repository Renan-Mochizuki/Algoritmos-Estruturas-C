#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

// Declarando struct de um nó da árvore
typedef struct arvoreNo {
  TipoValor valor;
  struct arvoreNo* esq;
  struct arvoreNo* dir;
} itemNo;

// Declarando struct da árvore
typedef struct arvore {
  itemNo* raiz;
} Arvore;

// Função recursiva que imprime os elementos da árvore
void ImprimirValoresRecursiva(Arvore* arvore, itemNo* no) {
  if (!no) return;

  // Faça o percurso in-ordem
  ImprimirValoresRecursiva(arvore, no->esq);
  // Destacando a raiz na impressão
  if (no == arvore->raiz)
    printf("*%d* ", no->valor);
  else
    printf("%d ", no->valor);
  ImprimirValoresRecursiva(arvore, no->dir);
}

// Função que imprime os elementos da árvore
void ImprimirValores(Arvore* arvore) {
  // Se a árvore estiver vazia
  if (!arvore->raiz) {
    printf("A arvore esta vazia\n");
    return;
  }

  printf("\nOs elementos da arvore seguindo o in-ordem: (*raiz*)\n");
  ImprimirValoresRecursiva(arvore, arvore->raiz);
  printf("\n\n");
}

// Função que retorna o ponteiro para a árvore
Arvore* CriarArvore() {
  Arvore* arvore = (Arvore*)malloc(sizeof(Arvore));
  arvore->raiz = NULL;
  return arvore;
}

// Função recursiva que retorna o nó que possui o valor, ou então, retorna NULL caso não for encontrado
itemNo* BuscarValorRecursiva(itemNo* no, TipoValor valor) {
  // Se o nó não existir (for NULL) retorne NULL
  if (!no) return NULL;

  // Se o valor for encontrado, retorne o nó
  if (no->valor == valor) return no;

  // Se o valor for menor que o valor do nó, busque no nó à esquerda
  if (valor < no->valor) return BuscarValorRecursiva(no->esq, valor);

  // O valor é maior, busque no nó à direita
  return BuscarValorRecursiva(no->dir, valor);
}

// Função que retorna o nó que possui o valor, ou então, retorna NULL caso não for encontrado
itemNo* BuscarValor(Arvore* arvore, TipoValor valor) {
  return BuscarValorRecursiva(arvore->raiz, valor);
}

// Função recursiva que insere um valor não existente ordenadamente
Boolean InserirValorRecursiva(itemNo* no, itemNo* noInserir) {
  // Se o valor do nó for o valor a ser inserido, o valor já existe
  if (no->valor == noInserir->valor) return FALSE;

  // Se o valor a ser inserido for menor que o do nó, prossiga à esquerda, se não à direita
  if (noInserir->valor < no->valor) {
    // Se existir nó à esquerda, prossiga
    if (no->esq)
      return InserirValorRecursiva(no->esq, noInserir);

    // Se não existir, o novo nó será o nó esquerda
    else
      no->esq = noInserir;
  } else {
    if (no->dir)
      return InserirValorRecursiva(no->dir, noInserir);
    else
      no->dir = noInserir;
  }

  return TRUE;
}

// Função recursiva que insere um valor não existente ordenadamente
Boolean InserirValor(Arvore* arvore, TipoValor valor) {
  // Declarando o novo nó a ser inserido na árvore
  itemNo* novoNo = malloc(sizeof(itemNo));
  novoNo->valor = valor;
  novoNo->esq = NULL;
  novoNo->dir = NULL;

  // Caso ainda não existir raiz
  if (!arvore->raiz) {
    arvore->raiz = novoNo;
    return TRUE;
  }

  return InserirValorRecursiva(arvore->raiz, novoNo);
}

// Função que retorna o nó pai de um nó
itemNo* RetornarNoPai(itemNo* noAtual, itemNo* noFilho) {
  // Se noAtual ou noFilho for NULL ou se o noFilho for o próprio noAtual (raiz da árvore), retorne NULL
  if (!noAtual || !noFilho || noAtual == noFilho) return NULL;

  // Se o filho da esquerda ou direita existir e for o nó passado, então retorne esse no
  if (noAtual->esq && noAtual->esq == noFilho) return noAtual;
  if (noAtual->dir && noAtual->dir == noFilho) return noAtual;

  // Se o valor do filho for menor que o do nó atual
  if (noFilho->valor < noAtual->valor) return RetornarNoPai(noAtual->esq, noFilho);

  // Por fim, busque no nó da direita
  return RetornarNoPai(noAtual->dir, noFilho);
}

// Função que retorna o ponteiro para o nó de menor valor da árvore
itemNo** RetornarPonteiroMenorNo(itemNo** noAtual) {
  // Enquanto existir nó à esquerda, avance à esquerda até chegar ao fim
  if ((*noAtual)->esq) return RetornarPonteiroMenorNo(&(*noAtual)->esq);

  return noAtual;
}

// Função que retorna o ponteiro para o nó de maior valor da árvore
itemNo** RetornarPonteiroMaiorNo(itemNo** noAtual) {
  // Enquanto existir nó à direita, avance à direita até chegar ao fim
  if ((*noAtual)->dir) return RetornarPonteiroMaiorNo(&(*noAtual)->dir);

  return noAtual;
}

// Função recursiva que remove um valor da árvore
Boolean RemoverValorRecursiva(itemNo** ponteiroNoAtual, TipoValor valor) {
  // A recursividade dessa função serve apenas para realizar uma busca até o nó daquele valor
  // e poder modificar o ponteiro para esse nó

  itemNo* noAtual = *ponteiroNoAtual;
  itemNo* auxiliar = NULL;

  // Se o nó atual for NULL, retorne FALSE
  if (!noAtual) return FALSE;

  // Se o valor for menor que o valor do nó atual, prossiga à esquerda, se for maior, prossiga à direita
  if (valor < noAtual->valor) {
    // Procurar na subárvore esquerda
    return RemoverValorRecursiva(&noAtual->esq, valor);
  } else if (valor > noAtual->valor) {
    // Procurar na subárvore direita
    return RemoverValorRecursiva(&noAtual->dir, valor);
  }

  // Se o valor for encontrado
  if (!noAtual->esq && !noAtual->dir) {  // Se o nó não tiver nenhum filho

    free(noAtual);
    *ponteiroNoAtual = NULL;

  } else if (!noAtual->esq) {  // Se tiver apenas filho à direita

    auxiliar = noAtual;
    *ponteiroNoAtual = noAtual->dir;
    free(auxiliar);

  } else if (!noAtual->dir) {  // Se tiver apenas filho à esquerda

    auxiliar = noAtual;
    *ponteiroNoAtual = noAtual->esq;
    free(auxiliar);

  } else {  // Se tiver dois filhos

    itemNo** ponteiroMenorNoADireita = RetornarPonteiroMenorNo(&noAtual->dir);

    // Armazenando o menor nó à direita
    auxiliar = *ponteiroMenorNoADireita;
    // Alterando o ponteiro do menor nó à direita para ser o nó a direita do menor
    // Ou seja, o menor nó à direita agora será, seu item à sua direita, seja ele um nó ou NULL
    *ponteiroMenorNoADireita = auxiliar->dir;
    // Modificando os filhos daquele menor nó para substituir o lugar do nó que estamos querendo remover
    auxiliar->esq = noAtual->esq;
    auxiliar->dir = noAtual->dir;
    free(noAtual);
    // Alterando o ponteiro do nó atual para ser o nó em que substituimos
    *ponteiroNoAtual = auxiliar;
  }
  return TRUE;
}

// Função que remove um valor da árvore
Boolean RemoverValor(Arvore* arvore, TipoValor valor) {
  if (!arvore->raiz) return FALSE;

  return RemoverValorRecursiva(&arvore->raiz, valor);
}

// Função recursiva que limpa a árvore
void LimparArvoreRecursiva(itemNo* no) {
  // Limpe a árvore pelo percurso pos-ordem
  if (!no) return;
  LimparArvoreRecursiva(no->esq);
  LimparArvoreRecursiva(no->dir);
  free(no);
}

// Função que limpa a árvore
void LimparArvore(Arvore* arvore) {
  LimparArvoreRecursiva(arvore->raiz);
  arvore->raiz = NULL;
}

// Função recursiva que conta quantos valores a árvore tem
int ContarValoresRecursiva(itemNo* no) {
  if (!no) return 0;

  return 1 + ContarValoresRecursiva(no->esq) + ContarValoresRecursiva(no->dir);
}

// Função que conta quantos valores a árvore tem
int ContarValores(Arvore* arvore) {
  return ContarValoresRecursiva(arvore->raiz);
}

// Função que imprime os valores desde a raiz até o nó
void ImprimirRotaDoNoValores(Arvore* arvore, itemNo* no) {
  if (!no) return;

  itemNo* noPai = RetornarNoPai(arvore->raiz, no);

  ImprimirRotaDoNoValores(arvore, noPai);

  if (no == arvore->raiz) {
    printf("%d", no->valor);
  } else {
    printf("->%d", no->valor);
  }
}

// Função que imprime os lados seguidos desde a raiz até o nó
void ImprimirRotaDoNoLados(Arvore* arvore, itemNo* noPai, itemNo* no) {
  if (!noPai) return;

  itemNo* noAvo = RetornarNoPai(arvore->raiz, noPai);

  ImprimirRotaDoNoLados(arvore, noAvo, noPai);

  if (noPai->esq == no) {
    printf("->Esq");
  } else {
    printf("->Dir");
  }
}

// Função que imprime tanto os valores quanto os lados seguidos desde a raiz até o nó
void ImprimirRotaDoNo(Arvore* arvore, itemNo* no) {
  if (!arvore || !no) return;

  ImprimirRotaDoNoValores(arvore, no);
  printf("\n");
  itemNo* noPai = RetornarNoPai(arvore->raiz, no);
  printf("Raiz");
  ImprimirRotaDoNoLados(arvore, noPai, no);
  printf("\n\n");
}

int main(void) {
  Arvore* arvore = CriarArvore();
  TipoValor valorDigitado;
  int escolha = 1;

  while (escolha > 0 && escolha < 7) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores na arvore\n");
    printf("2 - Remover valores\n");
    printf("3 - Buscar valores\n");
    printf("4 - Ver quantos itens a arvore possui\n");
    printf("5 - Imprimir arvore\n");
    printf("6 - Limpar arvore\n");
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

          Boolean funcaoSucedida = InserirValor(arvore, valorDigitado);

          if (funcaoSucedida)
            ImprimirValores(arvore);
          else
            printf("\nO valor ja existe na arvore\n");
        }
        break;

      case 2:
        if (!arvore->raiz) {
          printf("A arvore esta vazia\n");
          break;
        }

        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          ImprimirValores(arvore);
          printf("Digite um valor para ser removido\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          Boolean funcaoSucedida = RemoverValor(arvore, valorDigitado);

          if (!funcaoSucedida) printf("\nO valor nao foi removido\n");
        }
        break;

      case 3:
        if (!arvore->raiz) {
          printf("A arvore esta vazia\n");
          break;
        }

        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          printf("Digite um valor para ser buscado\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          itemNo* noEncontrado = BuscarValor(arvore, valorDigitado);

          if (noEncontrado) {
            ImprimirValores(arvore);
            printf("Percurso do valor desde a raiz:\n");
            ImprimirRotaDoNo(arvore, noEncontrado);
          } else {
            printf("\nO valor nao foi encontrado\n");
          }
        }
        break;

      case 4:
        printf("A arvore possui %d itens\n", ContarValores(arvore));
        break;

      case 5:
        ImprimirValores(arvore);
        break;

      case 6:
        LimparArvore(arvore);
        printf("A arvore foi limpa\n");
        break;
    }
  }

  LimparArvore(arvore);
  free(arvore);

  return 0;
}