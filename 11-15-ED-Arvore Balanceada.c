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
  int h;
  struct arvoreNo* esq;
  struct arvoreNo* dir;
} itemNo;

// Declarando struct da árvore
typedef struct arvore {
  itemNo* raiz;
} Arvore;

// Função recursiva que imprime os elementos da árvore
void ImprimirValoresRecursiva(Arvore* arvore, itemNo* no) {
  // Faça o percurso in-ordem
  if (no) {
    ImprimirValoresRecursiva(arvore, no->esq);
    // Destacando a raiz na impressão
    if (no == arvore->raiz)
      printf("*%d* ", no->valor);
    else
      printf("%d ", no->valor);
    ImprimirValoresRecursiva(arvore, no->dir);
  }
}

// Função que imprime os elementos da árvore
void ImprimirValores(Arvore* arvore) {
  // Se a árvore estiver vazia
  if (!arvore->raiz) {
    printf("\nA arvore esta vazia\n\n");
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

// Função que retorna o balanço de um nó
int CalcularBalanco(itemNo* no) {
  // Se o nó for NULL, retorne 0
  if (!no) return 0;

  // Se o nó não existir, a altura daquele lado é -1
  int altura_esq = (no->esq) ? no->esq->h : -1;
  int altura_dir = (no->dir) ? no->dir->h : -1;

  return altura_dir - altura_esq;
}

// Função que retorna o maior valor entre dois
int RetornarMaior(int a, int b) {
  return a > b ? a : b;
}

// Função que atualiza o parâmetro de altura de um nó, tendo todos seus nós filhos já atualizados
void AtualizarAlturaDoNo(itemNo* no) {
  if (no->esq && no->dir) // Se o nó tiver filho à esquerda e direita
    no->h = RetornarMaior(no->esq->h, no->dir->h) + 1;
  else if (no->dir) // Se o nó tiver filho apenas à direita
    no->h = no->dir->h + 1;
  else if (no->esq) // Se o nó tiver filho apenas à esquerda
    no->h = no->esq->h + 1;
  else // Se o nó não tiver nenhum filho
    no->h = 0;
}

// Função que realiza a rotação da esquerda e retorna a raiz da subárvore depois da rotação
itemNo *RotacionarL(itemNo *p) {
  itemNo *u = p->esq;
  int balancoU = CalcularBalanco(u);

  // Rotação LL:
  //     P
  //   U    =>    U
  // V          V   P
  if (balancoU == -1 || balancoU == 0) {
    // Descendo P. Colocando os itens da direita de U em P e anexando P na direita de U
    p->esq = u->dir;
    u->dir = p;
    // Atualizando altura
    AtualizarAlturaDoNo(p);
    AtualizarAlturaDoNo(u);
    return u;
  }

  // Rotação LR:
  //   P
  // U      =>    V
  //   V        U   P
  if (balancoU == 1) {
    itemNo *v = u->dir;
    // Descendo U. Colocando os itens da esquerda de V em U e anexando U na esquerda de V
    u->dir = v->esq;
    v->esq = u;
    // Descendo P. Colocando os itens da direita de V em P e anexando P na direita de V
    p->esq = v->dir;
    v->dir = p;
    // Atualizando altura
    AtualizarAlturaDoNo(u);
    AtualizarAlturaDoNo(p);
    AtualizarAlturaDoNo(v);
    return v;
  }

  return NULL;
}

// Função que realiza a rotação da direita e retorna a raiz da subárvore depois da rotação
itemNo *RotacionarR(itemNo *p) {
  itemNo *u = p->dir;
  int balancoU = CalcularBalanco(u);

  // Rotação RR:
  // P
  //   U    =>    U
  //     V      P   V
  if (balancoU == 1 || balancoU == 0) {
    // Descendo P
    p->dir = u->esq;
    u->esq = p;
    // Atualizando altura
    AtualizarAlturaDoNo(p);
    AtualizarAlturaDoNo(u);
    return u;
  }

  // Rotação RL:
  //   P
  //     U  =>    V
  //   V        P   U
  if (balancoU == -1) {
    itemNo *v = u->esq;
    // Descendo U
    u->esq = v->dir;
    v->dir = u;
    // Descendo P
    p->dir = v->esq;
    v->esq = p;
    // Atualizando altura
    AtualizarAlturaDoNo(u);
    AtualizarAlturaDoNo(p);
    AtualizarAlturaDoNo(v);
    return v;
  }

  return NULL;
}

// Função que imprime um aviso para quando a árvore estiver desbalanceada
void ImprimirAvisoDesbalanceamento(itemNo *no, Lado lado) {
  int balancoNo = CalcularBalanco(no);
  int balancoNoFilho;
  printf("\nNo de valor %d desbalanceado. h = %d, balanco = %d\n", no->valor, no->h, balancoNo);
  if(lado == ESQUERDO){
    balancoNoFilho = CalcularBalanco(no->esq);
    if(balancoNoFilho == -1 || balancoNoFilho == 0) printf("Fazendo rotacao LL\n");
    else if(balancoNoFilho == 1) printf("Fazendo rotacao LR\n");
  } else {
    balancoNoFilho = CalcularBalanco(no->dir);
    if(balancoNoFilho == 1 || balancoNoFilho == 0) printf("Fazendo rotacao RR\n");
    else if(balancoNoFilho == -1) printf("Fazendo rotacao RL\n");
  }
}

// Função recursiva que insere um valor na árvore
Boolean InserirValorRecursiva(Arvore *arvore, itemNo *noAtual, itemNo *noPai, itemNo *novoNo) {
  itemNo *raizDaRotacao, *noAProsseguir;
  Lado lado;

  // Se o valor já existir na árvore, retorne FALSE
  if (novoNo->valor == noAtual->valor) return FALSE;

  // Se o valor a ser inserido for menor que o valor do nó atual, prossiga à esquerda
  if (novoNo->valor < noAtual->valor) {
    // Se o nó à esquerda não existir, insira o novo nó à esquerda
    if (!noAtual->esq) {
      noAtual->esq = novoNo;
      // Se não existir nada a direita, atualize a altura
      if (!noAtual->dir) noAtual->h = 1;
      return TRUE;
    }
    lado = ESQUERDO;
    noAProsseguir = noAtual->esq;
  }
  // Se o valor a ser inserido for maior que o valor do nó atual, prossiga à direita
  else {
    // Se o nó à direita não existir, insira o novo nó à direita
    if (!noAtual->dir) {
      noAtual->dir = novoNo;
      // Se não existir nada a esquerda, atualize a altura
      if (!noAtual->esq) noAtual->h = 1;
      return TRUE;
    }
    lado = DIREITO;
    noAProsseguir = noAtual->dir;
  }

  // Chama a função até que seja achado um nó vazio para inserir o valor de maneira ordenada
  Boolean funcaoSucedida = InserirValorRecursiva(arvore, noAProsseguir, noAtual, novoNo);
  AtualizarAlturaDoNo(noAtual);
  int balancoNoAtual = CalcularBalanco(noAtual);

  // Se a função não foi bem sucedida (já existe o valor), retorne FALSE
  if(!funcaoSucedida) return FALSE;

  // Se o nó estiver desbalanceado
  if (balancoNoAtual >= 2 || balancoNoAtual <= -2) {
    ImprimirValores(arvore);
    ImprimirAvisoDesbalanceamento(noAtual, lado);

    if(lado == ESQUERDO) 
      raizDaRotacao = RotacionarL(noAtual);
    else 
      raizDaRotacao = RotacionarR(noAtual);

    // Se o nó atual for a raiz, atualize a raiz da árvore
    if (!noPai) {
      arvore->raiz = raizDaRotacao;
      return TRUE;
    }

    // Verifica qual lado está o nó atual e troca pela raiz da rotação
    if (noPai->esq == noAtual) noPai->esq = raizDaRotacao;
    else if (noPai->dir == noAtual) noPai->dir = raizDaRotacao;
  }

  return TRUE;
}

// Função que insere um valor na árvore
Boolean InserirValor(Arvore *arvore, TipoValor valor) {
  // Declarando o novo nó a ser inserido na árvore
  itemNo *novoNo = malloc(sizeof(itemNo));
  novoNo->valor = valor;
  novoNo->esq = NULL;
  novoNo->dir = NULL;
  novoNo->h = 0;

  // Caso ainda não existir raiz
  if (!arvore->raiz){
    arvore->raiz = novoNo;
    return TRUE;
  } 

  return InserirValorRecursiva(arvore, arvore->raiz, NULL, novoNo);
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

Boolean RemoverValorRecursiva(itemNo** ponteiroNoAtual, TipoValor valor) {
  itemNo* noAtual = *ponteiroNoAtual;

  // Se o nó atual for NULL, retorne FALSE
  if (!noAtual) return FALSE;

  // Se o valor for menor que o valor do nó atual, prossiga à esquerda, se for maior, prossiga à direita
  if (valor < noAtual->valor) {
    // Procurar na subárvore esquerda
    if (!RemoverValorRecursiva(&noAtual->esq, valor)) return FALSE;
  } else if (valor > noAtual->valor) {
    // Procurar na subárvore direita
    if (!RemoverValorRecursiva(&noAtual->dir, valor)) return FALSE;
  } else {
    // Se o valor for encontrado
    if (!noAtual->esq && !noAtual->dir) {  // Se o nó não tiver nenhum filho
      free(noAtual);
      *ponteiroNoAtual = NULL;
    } else if (!noAtual->esq) {  // Se tiver apenas filho à direita
      *ponteiroNoAtual = noAtual->dir;
      free(noAtual);
    } else if (!noAtual->dir) {  // Se tiver apenas filho à esquerda
      *ponteiroNoAtual = noAtual->esq;
      free(noAtual);
    } else {  // Se tiver dois filhos
      itemNo** ponteiroMenorNoADireita = RetornarPonteiroMenorNo(&noAtual->dir);
      itemNo* menorNoADireita = *ponteiroMenorNoADireita;
      // Alterando o ponteiro do menor nó à direita para ser o nó a direita do menor
      // Ou seja, o menor nó à direita agora será, seu item à sua direita, seja ele um nó ou NULL
      *ponteiroMenorNoADireita = menorNoADireita->dir;
      // Modificando os filhos daquele menor nó para substituir o lugar do nó que estamos querendo remover
      menorNoADireita->esq = noAtual->esq;
      menorNoADireita->dir = noAtual->dir;
      free(noAtual);
      // Alterando o ponteiro do nó atual para ser o nó em que substituimos
      *ponteiroNoAtual = menorNoADireita;
    }
  }

  // Atualizar altura do nó atual
  if (*ponteiroNoAtual) {
    AtualizarAlturaDoNo(*ponteiroNoAtual);

    // Verificar o balanço e realizar rotações, se necessário
    int balanco = CalcularBalanco(*ponteiroNoAtual);

    // Rotação LL
    if (balanco < -1 && CalcularBalanco((*ponteiroNoAtual)->esq) <= 0) {
      ImprimirAvisoDesbalanceamento(*ponteiroNoAtual, ESQUERDO);
      *ponteiroNoAtual = RotacionarL(*ponteiroNoAtual);
    }

    // Rotação LR
    if (balanco < -1 && CalcularBalanco((*ponteiroNoAtual)->esq) > 0) {
      ImprimirAvisoDesbalanceamento(*ponteiroNoAtual, ESQUERDO);
      (*ponteiroNoAtual)->esq = RotacionarR((*ponteiroNoAtual)->esq);
      *ponteiroNoAtual = RotacionarL(*ponteiroNoAtual);
    }

    // Rotação RR
    if (balanco > 1 && CalcularBalanco((*ponteiroNoAtual)->dir) >= 0) {
      ImprimirAvisoDesbalanceamento(*ponteiroNoAtual, DIREITO);
      *ponteiroNoAtual = RotacionarR(*ponteiroNoAtual);
    }

    // Rotação RL
    if (balanco > 1 && CalcularBalanco((*ponteiroNoAtual)->dir) < 0) {
      ImprimirAvisoDesbalanceamento(*ponteiroNoAtual, DIREITO);
      (*ponteiroNoAtual)->dir = RotacionarL((*ponteiroNoAtual)->dir);
      *ponteiroNoAtual = RotacionarR(*ponteiroNoAtual);
    }
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
  if (no) {
    LimparArvoreRecursiva(no->esq);
    LimparArvoreRecursiva(no->dir);
    free(no);
  }
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

  return 0;
}