#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define ESQUERDO 1
#define DIREITO 2
#define INDEFINIDO 0
#define FormatoValor "%d"
#define FormatoLado "%d"

typedef int Boolean;
typedef int TipoValor;
typedef int Lado;

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

  // Se o valor ainda não for encontrado, busque no nó à esquerda
  itemNo* auxiliar = BuscarValorRecursiva(no->esq, valor);

  // Se o valor for encontrado retorne o nó
  if (auxiliar) return auxiliar;

  // Se o valor ainda não for encontrado, por fim, busque no nó à direita
  return BuscarValorRecursiva(no->dir, valor);
}

// Função que retorna o nó que possui o valor, ou então, retorna NULL caso não for encontrado
itemNo* BuscarValor(Arvore* arvore, TipoValor valor) {
  return BuscarValorRecursiva(arvore->raiz, valor);
}

// Função que insere um valor ainda não existente na árvore
Boolean InserirValor(Arvore* arvore, itemNo* noPai, TipoValor valor, Lado lado) {
  // Caso o valor já exista na árvore, retorne FALSE
  if (BuscarValor(arvore, valor)) {
    return FALSE;
  }

  // Declarando o novo nó a ser inserido na árvore
  itemNo* novoNo = malloc(sizeof(itemNo));
  novoNo->valor = valor;
  novoNo->esq = NULL;
  novoNo->dir = NULL;

  // Se a árvore estiver vazia, o novo nó será a raiz
  if (!arvore->raiz || !noPai) {
    novoNo->esq = arvore->raiz;
    arvore->raiz = novoNo;
    return TRUE;
  }

  if (lado == ESQUERDO) {
    // Atribua o nó conectado à esquerda do pai para o novo nó
    // Conecte o novo nó ao pai
    novoNo->esq = noPai->esq;
    noPai->esq = novoNo;
  } else {
    // Atribua o nó conectado à direita do pai para o novo nó
    // Conecte o novo nó ao pai
    novoNo->dir = noPai->dir;
    noPai->dir = novoNo;
  }

  return TRUE;
}

// Função que retorna o nó pai de um nó
// (Uma solução mais eficiente seria lidar com ponteiros duplos, porém para manter a simplicidade, foi feito utilizando um nó pai)
itemNo* RetornarNoPai(itemNo* noAtual, itemNo* noFilho) {
  // Se noAtual for NULL ou se o noFilho for o próprio noAtual (raiz da árvore), retorne NULL
  if (!noAtual || noAtual == noFilho) return NULL;

  // Se o filho da esquerda ou direita existir e for o nó passado, então retorne esse no
  if (noAtual->esq && noAtual->esq == noFilho) return noAtual;
  if (noAtual->dir && noAtual->dir == noFilho) return noAtual;

  // Se ainda não for encontrado, busque no nó da esquerda
  itemNo* auxiliar = RetornarNoPai(noAtual->esq, noFilho);
  if (auxiliar) return auxiliar;

  // Por fim, busque no nó da direita
  return RetornarNoPai(noAtual->dir, noFilho);
}

// Função que retorna o último nó que se chega ao percorrer à esquerda de um dado nó
itemNo* RetornarUltimoNoEsquerda(itemNo* noAtual) {
  // Enquanto existir nó à esquerda, avance à esquerda até chegar ao fim
  if (noAtual->esq) return RetornarUltimoNoEsquerda(noAtual->esq);

  return noAtual;
}

// Função que remove um valor da árvore
Boolean RemoverValor(Arvore* arvore, TipoValor valor) {
  itemNo* noRemover = BuscarValor(arvore, valor);
  if(!noRemover) return FALSE;

  itemNo* noPai = RetornarNoPai(arvore->raiz, noRemover);

  // NULL já é o valor para quando o nó a ser removido não tiver nenhum valor
  itemNo* noAPendurarNoPai = NULL;

  if (!noRemover->esq) {  // Se tiver apenas filho à direita
    noAPendurarNoPai = noRemover->dir;
  } else if (!noRemover->dir) {  // Se tiver apenas filho à esquerda
    noAPendurarNoPai = noRemover->esq;
  } else {  // Se tiver dois filhos
    itemNo* ultimoNoEsquerda = RetornarUltimoNoEsquerda(noRemover);
    itemNo* paiUltimoNoEsquerda = RetornarNoPai(noRemover, ultimoNoEsquerda);
    // Atribuindo os itens da direita do ultimo nó à esquerda para o pai (já que não há nada na esquerda do último nó)
    paiUltimoNoEsquerda->esq = ultimoNoEsquerda->dir;
    // Modificando os filhos do último nó para substituir o lugar do nó que estamos querendo remover
    ultimoNoEsquerda->esq = noRemover->esq;
    ultimoNoEsquerda->dir = noRemover->dir;
    // Alterando o ponteiro do pai do nó a ser removido
    noAPendurarNoPai = ultimoNoEsquerda;
  }

  if(noRemover != arvore->raiz) {
    // Se o nó a ser removido for o filho da esquerda ou direita do pai, altera aquele lado
    if (noPai->esq && noPai->esq == noRemover) noPai->esq = noAPendurarNoPai;
    if (noPai->dir && noPai->dir == noRemover) noPai->dir = noAPendurarNoPai;
  } else {
    // Se o nó a remover for a raiz, então altere a raiz da arvore
    arvore->raiz = noAPendurarNoPai;
  }

  free(noRemover);
  return TRUE;
}

// Função recursiva que limpa a árvore
void LimparArvoreRecursiva(itemNo* no) {
  if (!no) return;

  // Limpe a árvore pelo percurso pos-ordem
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

// Função recursiva para encontrar o nó com espaço livre mais próximo da raiz
void EncontrarNoLivreRecursiva(itemNo* no, int alturaAtual, int* menorAltura, itemNo** noLivre) {
  // Se o no passado não existir, finalize a função
  if (!no) return;

  // Se o nó atual tem espaço vazio
  if (!no->esq || !no->dir) {
    // Se a altura atual for menor que a menor altura encontrada até então
    if (alturaAtual < *menorAltura) {
      // Altere a nova altura menor e o nó livre
      *menorAltura = alturaAtual;
      *noLivre = no;
    }
  }

  // Verifica o lado esquerdo e direito aumentando a alturaAtual
  EncontrarNoLivreRecursiva(no->esq, alturaAtual + 1, menorAltura, noLivre);
  EncontrarNoLivreRecursiva(no->dir, alturaAtual + 1, menorAltura, noLivre);
}

// Função que retorna um nó livre mais próximo da raiz (menor altura)
itemNo* EncontrarNoLivre(Arvore* arvore) {
  // Se a árvore estiver vazia
  if (arvore->raiz == NULL) return NULL;

  itemNo* noLivre = NULL;
  int menorAltura = INT_MAX;

  EncontrarNoLivreRecursiva(arvore->raiz, 0, &menorAltura, &noLivre);

  return noLivre;
}

// Função que insere um valor na árvore sem precisar passar um nó pai
Boolean InserirValorAutomaticamente(Arvore* arvore, TipoValor valor) {
  // Encontra um nó livre
  itemNo* noLivre = EncontrarNoLivre(arvore);
  Lado lado = INDEFINIDO;

  // Verifica qual lado que está livre
  if (noLivre && !noLivre->esq)
    lado = ESQUERDO;
  else if (noLivre && !noLivre->dir)
    lado = DIREITO;

  return InserirValor(arvore, noLivre, valor, lado);
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
  ImprimirRotaDoNoValores(arvore, no);
  printf("\n");
  itemNo* noPai = RetornarNoPai(arvore->raiz, no);
  printf("Raiz");
  ImprimirRotaDoNoLados(arvore, noPai, no);
  printf("\n");
}

int main(void) {
  Arvore* arvore = CriarArvore();
  TipoValor valorDigitado, valorNoPai;
  Lado lado = INDEFINIDO;
  int escolha = 1;

  while (escolha > 0 && escolha < 8) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores na arvore automaticamente\n");
    printf("2 - Inserir valores na arvore escolhendo o no pai\n");
    printf("3 - Remover valores\n");
    printf("4 - Buscar valores\n");
    printf("5 - Ver quantos itens a arvore possui\n");
    printf("6 - Imprimir arvore\n");
    printf("7 - Limpar arvore\n");
    printf("8 - Sair\n");

    scanf("%d", &escolha);
    printf("\n");

    valorDigitado = 0;
    valorNoPai = 0;

    switch (escolha) {
      case 1:
        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          printf("Digite um valor para ser inserido\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          Boolean funcaoSucedida = InserirValorAutomaticamente(arvore, valorDigitado);

          if (funcaoSucedida)
            ImprimirValores(arvore);
          else
            printf("\nO valor ja existe na arvore\n");
        }
        break;

      case 2:
        printf("Digite um valor negativo para parar\n");
        while (valorDigitado >= 0) {
          printf("Digite um valor para ser inserido\n");
          scanf(FormatoValor, &valorDigitado);

          if (valorDigitado < 0) break;

          itemNo* noPai = NULL;

          if (arvore->raiz) {
            while (!noPai) {
              ImprimirValores(arvore);
              printf("Digite o valor do no que deseja inserir em baixo dele\n");
              scanf(FormatoValor, &valorNoPai);

              if (valorNoPai < 0) break;

              noPai = BuscarValor(arvore, valorNoPai);
            }
            if (valorNoPai < 0) break;

            printf("\nDigite qual lado deseja\n");
            printf("Esquerdo (1), Direito (2)\n");
            scanf(FormatoLado, &lado);
          } else {
            printf("A arvore esta vazia, o valor sera a raiz\n");
          }

          Boolean funcaoSucedida = InserirValor(arvore, noPai, valorDigitado, lado);

          if (funcaoSucedida)
            ImprimirValores(arvore);
          else
            printf("\nO valor ja existe na arvore\n");
        }
        break;

      case 3:
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

      case 4:
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

      case 5:
        printf("A arvore possui %d itens\n", ContarValores(arvore));
        break;

      case 6:
        ImprimirValores(arvore);
        break;

      case 7:
        LimparArvore(arvore);
        printf("A arvore foi limpa\n");
        break;
    }
  }

  LimparArvore(arvore);
  free(arvore);

  return 0;
}