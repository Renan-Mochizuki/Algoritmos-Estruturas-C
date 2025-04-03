#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE 1
#define FormatoValor "%d"

typedef int Boolean;
typedef int TipoValor;

typedef struct {
  int numVertices;
  int numArestas;
  Boolean **matriz;
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
  grafo->matriz = malloc(sizeof(Boolean *) * maxVertices);

  // Se a alocação da array principal da matriz não foi bem sucedida
  if (!grafo->matriz) {
    free(grafo);
    return NULL;
  }

  // Loop que vai alocar uma array para cada posição da array principal
  for (int i = 0; i < maxVertices; i++) {
    grafo->matriz[i] = malloc(sizeof(Boolean) * maxVertices);

    // Caso alguma a alocação de alguma array não foi bem sucedida
    if (!grafo->matriz[i]) {
      // Libere cada item já alocado
      for (int k = 0; k < i; k++) {
        free(grafo->matriz[k]);
      }
      free(grafo->matriz);
      free(grafo);
      return NULL;
    }

    // Percorre cada item da array para inicializar a matriz com false
    for (int j = 0; j < maxVertices; j++) {
      grafo->matriz[i][j] = FALSE;
    }
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
  // Loop para imprimir os indices dos vertices
  for (int i = 0; i < nVertices; i++) {
    printf("\t%1i", i);
  }
  for (int i = 0; i < nVertices; i++) {
    printf("\n%i", i);
    // Loop que percorre cada item da matriz
    for (int j = 0; j < nVertices; j++) {
      printf("\t%1i", grafo->matriz[i][j]);
    }
  }
  printf("\n\n");
}

// Função que limpa o grafo, zerando a matriz e o número de arestas
void LimparGrafo(Grafo *grafo) {
  if (!grafo) return;

  // Loops que percorrem cada item da matriz
  for (int i = 0; i < grafo->numVertices; i++) {
    for (int j = 0; j < grafo->numVertices; j++) {
      grafo->matriz[i][j] = FALSE;
    }
  }

  grafo->numArestas = 0;
}

// Função que destroi o grafo
void DestruirGrafo(Grafo *grafo) {
  if (!grafo) return;

  // Loop que limpa cada uma das arrays da matriz
  for (int i = 0; i < grafo->numVertices; i++) {
    free(grafo->matriz[i]);
  }

  free(grafo->matriz);
  free(grafo);
}

// Função que valida os parâmetros passados
Boolean ValidarParametros(Grafo *grafo, int vertice1, int vertice2) {
  if (!grafo || vertice1 < 0 || vertice2 < 0 || vertice1 >= grafo->numVertices || vertice2 >= grafo->numVertices) {
    return FALSE;
  }
  return TRUE;
}

// Função que insere uma aresta
Boolean InserirAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;

  // Verificação para garantir que o numArestas não aumente caso a aresta já existir
  if (grafo->matriz[vertice1][vertice2] == FALSE) {
    grafo->matriz[vertice1][vertice2] = TRUE;
    grafo->numArestas++;
  }

  return TRUE;
}

// Função que remove uma aresta
Boolean RemoveAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;

  // Verificação para garantir que o numArestas não diminua caso a aresta já existir
  if (grafo->matriz[vertice1][vertice2] != FALSE) {
    grafo->matriz[vertice1][vertice2] = FALSE;
    grafo->numArestas--;
  }
  return TRUE;
}

// Função que verifica se uma aresta existe
Boolean VerificarExistenciaAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;

  // Verifica se a aresta existe
  if (grafo->matriz[vertice1][vertice2] == TRUE) {
    return TRUE;
  }
  return FALSE;
}

// Função que retorna o grau de um vértice
int RetornarGrau(Grafo *grafo, int vertice) {
  if (!ValidarParametros(grafo, vertice, 0)) return -1;

  int grau = 0;
  for (int i = 0; i < grafo->numVertices; i++) {
    // Verifica se o vertice é vizinho do vertice que está sendo verificado
    if (grafo->matriz[vertice][i] == TRUE) grau++;
    if (grafo->matriz[i][vertice] == TRUE) grau++;
  }
  return grau;
}

// Função que retorna o grau de entrada de um vértice
int RetornarGrauEntrada(Grafo *grafo, int vertice) {
  if (!ValidarParametros(grafo, vertice, 0)) return -1;

  int grauEntrada = 0;
  for (int i = 0; i < grafo->numVertices; i++) {
    if (grafo->matriz[i][vertice] == TRUE) grauEntrada++;
  }
  return grauEntrada;
}

// Função que retorna o grau de saída de um vértice
int RetornarGrauSaida(Grafo *grafo, int vertice) {
  if (!ValidarParametros(grafo, vertice, 0)) return -1;

  int grauSaida = 0;
  for (int i = 0; i < grafo->numVertices; i++) {
    if (grafo->matriz[vertice][i] == TRUE) grauSaida++;
  }
  return grauSaida;
}

// Função que verifica se um vértice possui vizinhos
Boolean VerificarPossuiVizinho(Grafo *grafo, int vertice) {
  if (!ValidarParametros(grafo, vertice, 0)) return FALSE;

  for (int i = 0; i < grafo->numVertices; i++) {
    if (grafo->matriz[vertice][i] == TRUE) return TRUE;
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
    printf("8 - Limpar arvore\n");
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

      int grauEntrada = RetornarGrauEntrada(grafo, vertice1);
      int grauSaida = RetornarGrauEntrada(grafo, vertice1);

      if (grauEntrada < 0 || grauSaida < 0){
        printf("O vertice nao existe\n");
        break;
      }

      printf("O grau de entrada do vertice %d e %d\n", vertice1, grauEntrada);
      printf("O grau de saida do vertice %d e %d\n", vertice1, grauSaida);
      printf("O grau total e %d\n", grauEntrada + grauSaida);
      break;

    case 7:
      ImprimirValores(grafo);
      break;

    case 8:
      LimparGrafo(grafo);
      printf("o Grafo foi limpo\n");
      break;
    }
  }

  DestruirGrafo(grafo);

  return 0;
}