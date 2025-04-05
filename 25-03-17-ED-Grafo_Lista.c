#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct node {
  int vertice;
  struct node *proximo;
} No;

typedef struct {
  int numVertices;
  int numArestas;
  No **lista;
} Grafo;

// Função que retorna o ponteiro para um grafo se passando o número de vértices
Grafo *CriarGrafo(int maxVertices) {
  Grafo *grafo = malloc(sizeof(Grafo));

  // Se a alocação não foi bem sucedida ou foi passado menos de um vértice
  if (!grafo || maxVertices < 1)
    return NULL;

  grafo->numVertices = maxVertices;
  grafo->numArestas = 0;

  // Alocando uma array do tamanho dos vértices
  grafo->lista = malloc(sizeof(No *) * maxVertices);

  // Se a alocação da array principal da lista não foi bem sucedida
  if (!grafo->lista) {
    free(grafo);
    return NULL;
  }

  // Loop que vai preencher a array de nós com NULL
  for (int i = 0; i < maxVertices; i++) {
    grafo->lista[i] = NULL;
  }

  return grafo;
}

// Função que imprime os valores do grafo
void ImprimirValores(Grafo *grafo) {
  if (!grafo) {
    printf("Grafo não existe\n");
    return;
  }

  int nVertices = grafo->numVertices;

  printf("Grafo com %d vertices e %d arestas:\n", nVertices, grafo->numArestas);

  for (int i = 0; i < nVertices; i++) {
    No *noAtual = grafo->lista[i];
    printf("[%i]", i);
    while (noAtual) {
      printf(" -> %i", noAtual->vertice);
      noAtual = noAtual->proximo;
    }
    printf("\n");
  }
  printf("\n");
}

// Função que limpa o grafo, limpando todas as listas e o número de arestas
void LimparGrafo(Grafo *grafo) {
  if (!grafo) return;

  // Loops que percorrem cada item da array e apaga cada nó
  for (int i = 0; i < grafo->numVertices; i++) {
    No *noAtual = grafo->lista[i];
    while(noAtual){
      No *apagar = noAtual;
      noAtual = noAtual->proximo;
      free(apagar);
    }
  }

  grafo->numArestas = 0;
}

// Função que destroi o grafo
void DestruirGrafo(Grafo *grafo) {
  if (!grafo) return;

  // Loops que percorrem cada item da array e apaga cada nó
  for (int i = 0; i < grafo->numVertices; i++) {
    No *noAtual = grafo->lista[i];
    while(noAtual){
      No *apagar = noAtual;
      noAtual = noAtual->proximo;
      free(apagar);
    }
  }

  free(grafo->lista);
  free(grafo);
}

// Função que valida os parâmetros passados
Boolean ValidarParametros(Grafo *grafo, int vertice1, int vertice2) {
  if (!grafo || vertice1 < 0 || vertice2 < 0 || vertice1 >= grafo->numVertices || vertice2 >= grafo->numVertices) {
    return FALSE;
  }
  return TRUE;
}

// Função que insere uma aresta na lista de adjacência de forma ordenada
Boolean InserirArestaLista(Grafo *grafo, int vertice1, int vertice2) {
  No *noAtual = grafo->lista[vertice1];
  No *noAnterior = NULL;

  // Loop que percorre a lista até a posição de ordenação correta ou até o NULL 
  while (noAtual && noAtual->vertice < vertice2) {
    noAnterior = noAtual;
    noAtual = noAtual->proximo;
  }

  // Se o nó já existe, não insere
  if (noAtual && noAtual->vertice == vertice2) {
    return FALSE;
  }

  No *novoNo = malloc(sizeof(No));
  novoNo->vertice = vertice2;
  novoNo->proximo = noAtual;

  // Se não tiver anterior, então altere o primeiro nó
  if(!noAnterior) {
    grafo->lista[vertice1] = novoNo;
    return TRUE;
  }
  
  noAnterior->proximo = novoNo;

  return TRUE;
}

// Função que insere uma aresta
Boolean InserirAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;
  // Verifica se vertice1 == vertice2 pois este grafo não permite self-loops
  if (vertice1 == vertice2) return FALSE;

  Boolean noFoiInserido = InserirArestaLista(grafo, vertice1, vertice2);
  InserirArestaLista(grafo, vertice2, vertice1);
  
  if(noFoiInserido) {
    grafo->numArestas++;
  }

  return TRUE;
}

// Função que remove uma aresta na lista de adjacência
Boolean RemoverArestaLista(Grafo *grafo, int vertice1, int vertice2) {
  No *noAtual = grafo->lista[vertice1];
  No *noAnterior = NULL;

  // Loop que percorre a lista até a posição de ordenação correta ou até o NULL 
  while (noAtual && noAtual->vertice < vertice2) {
    noAnterior = noAtual;
    noAtual = noAtual->proximo;
  }

  // Se o nó não foi encontrado, retorne falso
  if (noAtual && noAtual->vertice != vertice2) {
    return FALSE;
  }

  // Se não tiver anterior, então altere o primeiro nó
  if(!noAnterior) {
    grafo->lista[vertice1] = noAtual->proximo;
    free(noAtual);
    return TRUE;
  }
  
  noAnterior->proximo = noAtual->proximo;
  free(noAtual);

  return TRUE;
}

// Função que remove uma aresta
Boolean RemoveAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;

  Boolean noFoiInserido = RemoverArestaLista(grafo, vertice1, vertice2);
  RemoverArestaLista(grafo, vertice2, vertice1);
  
  if(noFoiInserido) {
    grafo->numArestas--;
  }

  return TRUE;
}

// Função que verifica se uma aresta existe
Boolean VerificarExistenciaAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;

  No *noAtual = grafo->lista[vertice1];

  // Loop que percorre a lista até a posição de ordenação correta ou até o NULL
  while (noAtual && noAtual->vertice < vertice2) {
    noAtual = noAtual->proximo;
  }

  // Se o nó foi encontrado, retorne verdadeiro
  if (noAtual && noAtual->vertice == vertice2) {
    return TRUE;
  }

  return FALSE;
}

// Função que retorna o grau de um vértice
int RetornarGrau(Grafo *grafo, int vertice) {
  if (!ValidarParametros(grafo, vertice, 0)) return -1;

  int grau = 0;
  
  No *noAtual = grafo->lista[vertice];
  while (noAtual) {
    grau++;
    noAtual = noAtual->proximo;
  }

  return grau;
}

// Função que verifica se um vértice possui vizinhos
Boolean VerificarPossuiVizinho(Grafo *grafo, int vertice) {
  if (!ValidarParametros(grafo, vertice, 0)) return FALSE;

  // Se existir um nó na lista de adjacência do vértice, então ele possui vizinhos
  if(grafo->lista[vertice]) {
    return TRUE;
  }

  return FALSE;
}

// Função que retorna o número de arestas
int RetornarNumeroArestas(Grafo *grafo) { 
  if(!grafo) return -1;
  return grafo->numArestas; 
}

int main(void) {
  TipoValor valorDigitado = 0;
  int tamanhoDigitado = 0;
  int escolha = 1;

  printf("Digite o tamanho do grafo\n");
  scanf("%d", &tamanhoDigitado);

  Grafo *grafo = CriarGrafo(tamanhoDigitado);

  if (!grafo) {
    printf("Erro ao criar o grafo\n");
    return 1;
  }

  while (escolha > 0 && escolha < 9) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir uma aresta\n");
    printf("2 - Remover uma aresta\n");
    printf("3 - Verificar quantas arestas o grafo possui\n");
    printf("4 - Verificar se uma aresta existe\n");
    printf("5 - Verificar se um vertice possui vizinhos\n");
    printf("6 - Calcular grau de um vertice\n");
    printf("7 - Imprimir grafo\n");
    printf("8 - Limpar grafo\n");
    printf("9 - Sair\n");

    scanf("%d", &escolha);
    printf("\n");

    valorDigitado = 0;

    int vertice1, vertice2;

    switch (escolha) {
    case 1:
      printf("Digite um valor negativo para parar\n");
      while (valorDigitado >= 0) {
        printf("Digite o primeiro vertice que deseja conectar\n");
        scanf("%d", &vertice1);

        if (vertice1 < 0) break;

        printf("Digite o segundo vertice que deseja conectar\n");
        scanf("%d", &vertice2);

        if (vertice2 < 0) break;

        Boolean funcaoSucedida = InserirAresta(grafo, vertice1, vertice2);

        if (funcaoSucedida)
          ImprimirValores(grafo);
        else
          printf("\nA aresta nao foi inserida\n");
      }
      break;

    case 2:
      printf("Digite um valor negativo para parar\n");
      while (valorDigitado >= 0) {
        printf("Digite o primeiro vertice da aresta que deseja remover\n");
        scanf("%d", &vertice1);

        if (vertice1 < 0) break;

        printf("Digite o segundo vertice da aresta que deseja remover\n");
        scanf("%d", &vertice2);

        if (vertice2 < 0) break;

        Boolean funcaoSucedida = RemoveAresta(grafo, vertice1, vertice2);

        if (funcaoSucedida)
          ImprimirValores(grafo);
        else
          printf("\nO valor nao foi removido\n");
      }
      break;

    case 3:
      printf("O grafo possui %d arestas\n", RetornarNumeroArestas(grafo));
      break;

    case 4:
      printf("Digite o primeiro vertice\n");
      scanf("%d", &vertice1);

      if (vertice1 < 0) break;

      printf("Digite o segundo vertice\n");
      scanf("%d", &vertice2);

      if (vertice2 < 0) break;

      Boolean arestaExiste = VerificarExistenciaAresta(grafo, vertice1, vertice2);

      if (arestaExiste) {
        printf("A aresta de vertices %d e %d existe\n", vertice1, vertice2);
      } else {
        printf("A aresta nao existe\n");
      }
      break;

    case 5:
      printf("Digite o vertice\n");
      scanf("%d", &vertice1);

      if (vertice1 < 0) break;

      Boolean possuiVizinho = VerificarPossuiVizinho(grafo, vertice1);

      if (possuiVizinho) {
        printf("O vertice possui vizinhos\n");
      } else {
        printf("O vertice nao possui vizinhos\n");
      }
      break;

    case 6:
      printf("Digite o vertice\n");
      scanf("%d", &vertice1);

      if (vertice1 < 0) break;

      int grau = RetornarGrau(grafo, vertice1);

      if (grau >= 0) {
        printf("O grau do vertice %d e %d\n", vertice1, grau);
      } else {
        printf("O vertice nao existe\n");
      }
      break;

    case 7:
      ImprimirValores(grafo);
      break;

    case 8:
      LimparGrafo(grafo);
      printf("O grafo foi limpo\n");
      break;
    }
  }

  DestruirGrafo(grafo);

  return 0;
}