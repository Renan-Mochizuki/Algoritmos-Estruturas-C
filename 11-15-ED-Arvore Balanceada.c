#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
  if (!no) return;
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
    printf("\nA arvore esta vazia\n\n");
    return;
  }

  printf("\nOs elementos da arvore seguindo o in-ordem: (*raiz*)\n");
  ImprimirValoresRecursiva(arvore, arvore->raiz);
  printf("\n\n");
}

void ImprimirArvore(Arvore* arvore);

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
    ImprimirArvore(arvore);
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

// Função recursiva que calcula a altura de uma árvore
int CalcularAlturaRecursiva(itemNo* no) {
  // Se o nó for NULL, a altura é -1
  if (!no) return -1;

  // Calcula a altura das subárvores esquerda e direita
  int alturaEsquerda = CalcularAlturaRecursiva(no->esq);
  int alturaDireita = CalcularAlturaRecursiva(no->dir);

  // Retorna a maior altura entre as subárvores da esquerda e direita mais 1
  return RetornarMaior(alturaEsquerda, alturaDireita) + 1;
}

// Função que retorna a altura da árvore
int CalcularAltura(Arvore* arvore) {
  return CalcularAlturaRecursiva(arvore->raiz);
}

/* -- Estruturas e funções para fazer a impressão da árvore -- */
typedef struct nodeLista {
  TipoValor *valores;
  int livre;
  struct nodeLista *proximo;
} itemNoLista;

typedef struct {
  int tamanho;
  itemNoLista *primeiro;
} ListaLigada;

ListaLigada *CriarLista() {
  ListaLigada *lista = malloc(sizeof(ListaLigada));
  lista->tamanho = 0;
  lista->primeiro = NULL;
  return lista;
}

itemNoLista *CriarNoLista(int indice) {
  itemNoLista *itemNovo = malloc(sizeof(itemNoLista));
  // Definindo a quantidade máxima sendo 2^nivel
  int quantidadeMaximaPorNivel = (int)pow(2, indice);
  itemNovo->valores = malloc(sizeof(TipoValor) * quantidadeMaximaPorNivel);
  itemNovo->livre = 0;
  itemNovo->proximo = NULL;
  return itemNovo;
}

void InserirLista(ListaLigada *lista, TipoValor valor, int indice) {
  if(!lista->primeiro) {
    itemNoLista *itemNovo = CriarNoLista(indice);
    lista->tamanho++;
    lista->primeiro = itemNovo;
  }

  itemNoLista *itemAtual = lista->primeiro;
  itemNoLista *itemAnterior = NULL;
  
  // Loop que percorre até o nó do indice passado
  for(int i = 0; i < indice && itemAtual; i++) {
    itemAnterior = itemAtual;
    itemAtual = itemAtual->proximo;
  }

  // Declarando novo nó
  if(!itemAtual){
    itemNoLista *itemNovo = CriarNoLista(indice);
    lista->tamanho++;
    itemAnterior->proximo = itemNovo;
    itemAtual = itemNovo;
  }

  // Insere o valor no nó
  itemAtual->valores[itemAtual->livre] = valor;
  itemAtual->livre++;
}

void LimparLista(ListaLigada *lista) {
  itemNoLista *itemAtual = lista->primeiro;

  // Loop que percorre a lista até o NULL
  while (itemAtual != NULL) {
    itemNoLista *itemProximo = itemAtual->proximo;
    // Libera o itemAtual e avança para o próximo
    free(itemAtual);
    itemAtual = itemProximo;
  }
}

// Função recursiva que percorre a árvore na pré-ordem e insere os valores em uma lista ligada
void PercorrerArvoreLista(itemNo* no, int alturaAtual, ListaLigada* lista, int maiorAltura) {
  // Se o no passado não existir (chegou ao fim da subárvore), insira o valor -1
  if (!no) {
    InserirLista(lista, -1, alturaAtual);

    // Loop para garantir que a visualização esteja correta quando houver um outro nó dois níveis 
    // mais baixo (desbalanceamento), inserindo dois valores vazios no filho
    for(int i = alturaAtual + 1; i < maiorAltura + 1; i++) {
      // Loop para inserir o valor vazio a quantidade de vezes de acordo com a maior altura
      for(int j = 0; j < (int)pow(2, i - maiorAltura + 1); j++) {
        InserirLista(lista, -1, i);
      }
    }
    return;
  }

  InserirLista(lista, no->valor, alturaAtual);

  PercorrerArvoreLista(no->esq, alturaAtual + 1, lista, maiorAltura);

  PercorrerArvoreLista(no->dir, alturaAtual + 1, lista, maiorAltura);
}

// Função que imprime a árvore de maneira gráfica
void ImprimirArvore(Arvore* arvore) {
  // Se a árvore estiver vazia
  if (!arvore->raiz) {
    printf("\nA arvore esta vazia\n\n");
    return;
  }

  ListaLigada *lista = CriarLista();
  int maiorAltura = CalcularAltura(arvore);
  int tamanhoCaractere = 2;

  PercorrerArvoreLista(arvore->raiz, 0, lista, maiorAltura);

  itemNoLista *itemAtual = lista->primeiro;
  // Subtraindo 2 para não imprimir o último nível
  int ultimoNivel = lista->tamanho - 2;

  printf("\nArvore:\n");

  // Loop que percorre os nós da lista
  for(int i = 0; i < lista->tamanho - 1; i++) {
    int quantidadeMaximaPorNivel = (int)pow(2, i);
    int larguraCantos = (int)pow(2, ultimoNivel - i - 1) * 2 - 1;
    int larguraMeio = (int)pow(2, ultimoNivel - i) * 2 - 1;

    // Loop para imprimir os espaços vazios antes dos valores (formato de pirâmide)
    for(int j = 0; j < larguraCantos * tamanhoCaractere; j++){
      printf(" ");
    }

    // Loop que percorre os valores da array do nó atual
    for(int k = 0; k < quantidadeMaximaPorNivel; k++) {

      // Se k for maior que a quantidade de valores do nó atual, continue para evitar acesso indevido
      if (k >= itemAtual->livre) continue;

      int valorAtual = itemAtual->valores[k];
      int quantidadeDigitos = valorAtual == 0 ? 1 : (int)log10(valorAtual) + 1;

      // Se o valor for -1, imprima espaços vazios
      if(valorAtual == -1) {
        // Loop para imprimir espaços vazios de acordo com o tamanho do caractere
        for(int l=0; l < tamanhoCaractere; l++){
          printf(" ");
        }
      } else {
        // Cálculo de quantos espaços vazios deverão ser impressos ao redor do valor de acordo com seus digitos
        int espacosNecessarios = tamanhoCaractere - quantidadeDigitos;
        int espacoAntes = espacosNecessarios / 2;
        int espacoDepois = espacosNecessarios - espacoAntes;
        for(int m = 0; m < espacoAntes; m++){
          printf(" ");
        }
        printf("%d", valorAtual);
        for(int n = 0; n < espacoDepois; n++){
          printf(" ");
        }
      }
    
      // Imprimindo espaços vazios entre os valores de acordo com o tamanho do caractere
      for(int o = 0; o < larguraMeio * tamanhoCaractere; o++){
        printf(" ");
      }
    }
    printf("\n");
    // Passando pro próximo nó
    itemAtual = itemAtual->proximo;
  }
  printf("\n");
  LimparLista(lista);
  free(lista);
}

int main(void) {
  Arvore* arvore = CriarArvore();
  TipoValor valorDigitado;
  int escolha = 1;

  while (escolha > 0 && escolha < 9) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir valores na arvore\n");
    printf("2 - Remover valores\n");
    printf("3 - Buscar valores\n");
    printf("4 - Imprimir valores\n");
    printf("5 - Imprimir arvore\n");
    printf("6 - Ver quantos itens a arvore possui\n");
    printf("7 - Ver altura da arvore\n");
    printf("8 - Limpar arvore\n");
    printf("9 - Sair\n");

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
            ImprimirArvore(arvore);
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
          ImprimirArvore(arvore);
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
            ImprimirArvore(arvore);
            printf("Percurso do valor desde a raiz:\n");
            ImprimirRotaDoNo(arvore, noEncontrado);
          } else {
            printf("\nO valor nao foi encontrado\n");
          }
        }
        break;

      case 4:
        ImprimirValores(arvore);
        break;

      case 5:
        ImprimirArvore(arvore);
        break;

      case 6:
        printf("A arvore possui %d itens\n", ContarValores(arvore));
        break;

      case 7:
        printf("A arvore "); // Cortando o texto para poder declarar uma variavel dentro de um case
        int altura = CalcularAltura(arvore);
        printf(" possui altura %d, sendo assim, %d subniveis\n", altura, altura + 1);
        break;

      case 8:
        LimparArvore(arvore);
        printf("A arvore foi limpa\n");
        break;
    }
  }

  LimparArvore(arvore);
  free(arvore);

  return 0;
}