/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2025                          **/
/**   Prof. Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Segundo Exercicio-Programa                                    **/
/**                                                                 **/
/**   Renan Mochizuki                             <N USP>           **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define true 1
#define false 0

#define INFINITO 999999

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
  int numVertices;
  int numArestas;
  bool **matriz;
} Grafo;

/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123() {
  // Funcao usada pelo sistema de correcao automatica (nao mexer)
}

/* Estrutura para representar elementos de uma lista ligada de vertices */
typedef struct aux {
  int vertice;
  struct aux *prox;
} ElementoLista, *PONT;

/* Estrutura para representar elementos de uma lista ligada com arestas
   (pares de vertices)*/
typedef struct aux2 {
  int origem;
  int destino;
  struct aux2 *prox;
} ArestaLista, *PONT2;

/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencia (preenchida com ARESTAS_INVALIDAS),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo *g, int vertices) {
  if (g == NULL || vertices < 1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool **)malloc(sizeof(bool *) * vertices);
  for (x = 0; x < vertices; x++) {
    g->matriz[x] = (bool *)malloc(sizeof(bool) * vertices);
    for (y = 0; y < vertices; y++) {
      g->matriz[x][y] = false;
    }
  }
  return true;
}

/* Funcao que libera a memoria da matriz de adjacencia do grafo cujo endereco
   foi passado como parametro.
*/
bool liberaGrafo(Grafo *g) {
  if (g == NULL) return false;
  int x;
  for (x = 0; x < g->numVertices; x++)
    free(g->matriz[x]);
  free(g->matriz);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  return true;
}

/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia.
*/
bool insereAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices) return false;
  if (g->matriz[v1][v2] == false) {
    g->matriz[v1][v2] = true;
    g->numArestas++;
  }
  return true;
}

/* Funcao que exclui a aresta entre v1 e v2 (caso exista uma aresta valida
   entre v1 e v2) e retorna true; ou retorna false, caso contrario.
*/
bool removeAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  g->matriz[v1][v2] = false;
  g->numArestas--;
  return true;
}

/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo *criaGrafoAleatorio(int numVertices, int numArestas) {
  int x, y, a, total;
  if (numVertices < 1 || numArestas >= numVertices * numVertices / 2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;
  }
  Grafo *g = (Grafo *)malloc(sizeof(Grafo));
  inicializaGrafo(g, numVertices);

  a = 0;
  while (a < numArestas) {
    x = rand() % numVertices;
    y = rand() % numVertices;
    if (g->matriz[x][y] == false) {
      g->matriz[x][y] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  return g;
}

/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencias.
*/
void exibeGrafo(Grafo *g) {
  if (!g) return;
  int x, y;
  printf("\nImprimindo grafo (v=%i; a=%i)\n   ", g->numVertices, g->numArestas);
  for (x = 0; x < g->numVertices; x++)
    printf(" %3i", x);
  printf("\n");
  for (x = 0; x < g->numVertices; x++) {
    printf("%3i", x);
    for (y = 0; y < g->numVertices; y++)
      printf(" %3i", g->matriz[x][y]);
    printf("\n");
  }
  printf("\n");
}

/* Funcao que calcula a distancia e o predecedor considerando todos os pares
   vertices (distancia de todos para todos), com base no algoritmo de
   Floyd-Warshall.
*/
void calculaDistanciaFloydWarshall(Grafo *g, int **dist, int **pred) {
  int i, j, k, n;
  n = g->numVertices;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (g->matriz[i][j] != false) {
        dist[i][j] = g->matriz[i][j];
        pred[i][j] = i;
      } else {
        dist[i][j] = INFINITO;
        pred[i][j] = -1;
      }
  for (i = 0; i < n; i++) {
    dist[i][i] = 0;
    pred[i][i] = i;
  }

  for (k = 0; k < n; k++)
    for (i = 0; i < n; i++)
      for (j = 0; j < n; j++)
        if (dist[i][j] > dist[i][k] + dist[k][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          pred[i][j] = pred[k][j];
        }
}

/* Funcao que exibe uma matriz de distancias.
   Caso a distancia seja INFINITO, imprime '-'.
*/
void exibeMatrizDistancias(int **matriz, int n) {
  printf("Exibindo matriz de distancias.\n");
  int x, y;
  for (x = 0; x < n; x++)
    printf("\t%3i", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%i", x);
    for (y = 0; y < n; y++) {
      if (matriz[x][y] == INFINITO)
        printf("\t-");
      else
        printf("\t%3i", matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

/* Funcao que exibe uma matriz de predecessores.
   Caso a distancia seja INFINITO, imprime '-'.
*/
void exibeMatrizPredecessores(int **matriz, int n) {
  printf("Exibindo matriz de predecessores.\n");
  int x, y;
  for (x = 0; x < n; x++)
    printf("\t%3i", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%i", x);
    for (y = 0; y < n; y++) {
      printf("\t%3i", matriz[x][y]);
    }
    printf("\n");
  }
  printf("\n");
}

/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(double *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf("  v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%4.3f\t", arranjo[x]);
  }
  printf("\n\n");
}

/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep2/ep2.pdf        */

/* Funcao que calcula a Centralidade de Grau de todos os vertices. */
void centralidadeDeGrau(Grafo *g, double *valores) {
  // Loop para percorrer todos os vertices do grafo
  for (int verticeAtual = 0; verticeAtual < g->numVertices; verticeAtual++) {
    // Resetando a array com 0
    valores[verticeAtual] = 0.0;

    // Loop para calcular o grau do vertice atual
    double grau = 0;
    for (int i = 0; i < g->numVertices; i++) {
      // Verifica se existe uma aresta entre o vertice atual e o vertice i
      // e i != verticeAtual para evitar o auto-laço
      if (g->matriz[i][verticeAtual] == true && i != verticeAtual) {
        grau++;
      }
    }

    // Atribui o grau ao valor de centralidade
    valores[verticeAtual] = grau / (g->numVertices - 1);
  }
}

/* Funcao que calcula a Centralidade de Proximidade de todos os vertices. */
void centralidadeDeProximidade(Grafo *g, double *valores) {
  // Alocando arrays
  int **dist = malloc(sizeof(int) * g->numVertices);
  int **pred = malloc(sizeof(int) * g->numVertices);

  for (int i = 0; i < g->numVertices; i++) {
    dist[i] = malloc(sizeof(int) * g->numVertices);
    pred[i] = malloc(sizeof(int) * g->numVertices);
  }

  calculaDistanciaFloydWarshall(g, dist, pred);

  // Loop para percorrer todos os vertices do grafo
  for (int verticeAtual = 0; verticeAtual < g->numVertices; verticeAtual++) {
    // Resetando a array com 0
    valores[verticeAtual] = 0.0;

    // Calcula a soma das distancias do vertice atual para todos os outros vertices
    double somaDistancias = 0.0;
    for (int i = 0; i < g->numVertices; i++) {
      // Se existir uma distancia
      if (i != verticeAtual && dist[verticeAtual][i] != INFINITO) {
        somaDistancias += dist[verticeAtual][i];
      }
    }

    // Atribui o valor da centralidade de proximidade
    if (somaDistancias > 0.0)
      valores[verticeAtual] = (g->numVertices - 1) / somaDistancias;
    else
      valores[verticeAtual] = 0.0;
  }

  // Liberando a memoria alocada
  for (int i = 0; i < g->numVertices; i++) {
    free(dist[i]);
    free(pred[i]);
  }
  free(dist);
  free(pred);
}

// Função auxiliar que conta os caminhos de um verticeOrigem que passam pelo verticeAtual
// isso inclui tanto os caminhos em que o predessor é verticeAtual
// quanto os caminhos que passam por verticeAtual, mas o predessor pode ser outro
int contarCaminhos(Grafo *g, int **pred, int verticeOrigem, int verticeAtual) {
  int cont = 0;
  // Loop que percorre todos os vertices do grafo como verticeDestino
  for (int verticeDestino = 0; verticeDestino < g->numVertices; verticeDestino++) {
    // Se o predessor do verticeOrigem e verticeDestino for igual ao verticeAtual,
    // contaremos mais 1, e agora iremos chamar recursivamente, para verificar se há um outro caminho
    // que o predecessor é esse verticeDestino
    if (pred[verticeOrigem][verticeDestino] == verticeAtual) {
      cont++;
      cont = cont + contarCaminhos(g, pred, verticeOrigem, verticeDestino);
    }
  }
  return cont;
}

/* Funcao que calcula a Centralidade de Intermediacao de todos os vertices. */
void centralidadeDeIntermediacao(Grafo *g, double *valores) {
  // Alocando arrays
  int **dist = malloc(sizeof(int *) * g->numVertices);
  int **pred = malloc(sizeof(int *) * g->numVertices);

  for (int i = 0; i < g->numVertices; i++) {
    dist[i] = malloc(sizeof(int) * g->numVertices);
    pred[i] = malloc(sizeof(int) * g->numVertices);
  }

  calculaDistanciaFloydWarshall(g, dist, pred);

  int n = g->numVertices;

  // Iremos achar quantos caminhos que de um vertice origem até todos os outros vertices passam pelo vertice atual
  // sendo o vertice origem todos os vertices do grafo excluindo o atual

  for (int verticeAtual = 0; verticeAtual < g->numVertices; verticeAtual++) {
    int contAtual = 0;
    // Resetando a array com 0
    valores[verticeAtual] = 0.0;

    for (int verticeOrigem = 0; verticeOrigem < g->numVertices; verticeOrigem++) {
      // Se o vertice origem for igual ao vertice atual, pula para o proximo
      if (verticeOrigem == verticeAtual) continue;

      contAtual = contAtual + contarCaminhos(g, pred, verticeOrigem, verticeAtual);
    }

    valores[verticeAtual] = (double)contAtual / ((n - 1) * (n - 2));
  }

  // Liberando a memoria alocada
  for (int i = 0; i < g->numVertices; i++) {
    free(dist[i]);
    free(pred[i]);
  }
  free(dist);
  free(pred);
}

/* Funcao que calcula a Centralidade Page Rank de todos os vertices. */
void centralidadePageRank(Grafo *g, double *valores, int iteracoes) {
  int n = g->numVertices;
  double d = 0.85;

  // Declarando uma array que armazenara o grau de saida de cada vertice
  int grauSaidas[g->numVertices];

  // Conta o grau de saída de cada vértice
  for (int i = 0; i < n; i++) {
    grauSaidas[i] = 0;
    for (int j = 0; j < n; j++) {
      // Se existe uma aresta do vértice i para o vértice j e não é um autolaço, incrementa o grau de saída
      if (g->matriz[i][j] == true && i != j) {
        grauSaidas[i]++;
      }
    }
  }

  // A implementação com recursividade, que calcula PR(t) chamando recursivamente PR(t-1) para cada vértice de entrada
  // não era eficiente e travava, por isso, faremos de maneira iterativa, começando do PR(0) e indo até PR(t)

  // Inicializa o vetor com PR(0)
  for (int i = 0; i < n; i++) {
    valores[i] = 1.0 / n;
  }

  // Declarando array que armazenará os valores somatórios de cada vértice
  // que serão usados para calcular o PageRank
  double valoresSomatorios[g->numVertices];

  // Loop que fará a iteração do PR(0) até PR(t)
  // Iremos calcular o PageRank de todos os vértices ao mesmo tempo, para cada iteração, pois caso contrário
  // calcular o PageRank para um vértice de cada vez, não estava sendo eficiente
  for (int it = 0; it < iteracoes; it++) {
    // Zera o vetor
    for (int i = 0; i < n; i++) {
      valoresSomatorios[i] = 0.0;
    }

    // Loop que percorre todos os vertices do grafo
    // e pega todos os vertices de entrada
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < n; i++) {
        // Se existe uma aresta do vértice i para o vértice j e não é um autolaço
        if (g->matriz[i][j] == true && i != j) {
          valoresSomatorios[j] += valores[i] / grauSaidas[i];
        }
      }
    }

    // Faz a formula do PageRank
    for (int i = 0; i < n; i++) {
      valores[i] = ((1 - d) / n) + d * valoresSomatorios[i];
    }
  }
}

/* FIM DAS FUNCOES QUE DEVEM SER COMPLETADAS */

/* Funcao que invoca e exibe os valores de cada uma das funcoes que voces
   devem implementar neste EP.
*/
void testaFuncoes(Grafo *g, int n) {

  double *valoresReais = (double *)malloc(sizeof(double) * n);

  printf("Centralidade de Grau:\n");
  centralidadeDeGrau(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Proximidade:\n");
  centralidadeDeProximidade(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade de Intermediacao:\n");
  centralidadeDeIntermediacao(g, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 0 iteracoes\n");
  centralidadePageRank(g, valoresReais, 0);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 1 iteracao\n");
  centralidadePageRank(g, valoresReais, 1);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 10 iteracoes\n");
  centralidadePageRank(g, valoresReais, 10);
  exibeArranjoReais(valoresReais, n);

  printf("Centralidade Page Rank: 100 iteracoes\n");
  centralidadePageRank(g, valoresReais, 100);
  exibeArranjoReais(valoresReais, n);

  free(valoresReais);
}

/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;
  double *valoresReais = (double *)malloc(sizeof(double) * n);

  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1, 0, 1);
  insereAresta(&g1, 1, 2);
  insereAresta(&g1, 2, 3);
  insereAresta(&g1, 3, 4);
  insereAresta(&g1, 4, 0);
  insereAresta(&g1, 0, 2);
  insereAresta(&g1, 1, 4);
  insereAresta(&g1, 1, 3);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);

  printf("\n\nSEGUNDO EXEMPLO [auto-lacos]\n");
  insereAresta(&g1, 0, 0);
  insereAresta(&g1, 2, 2);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n);

  printf("\n\nTERCEIRO EXEMPLO\n");
  Grafo g2;
  inicializaGrafo(&g2, n);
  insereAresta(&g2, 0, 2);
  insereAresta(&g2, 1, 2);
  insereAresta(&g2, 3, 2);
  insereAresta(&g2, 4, 2);
  insereAresta(&g2, 2, 0);
  insereAresta(&g2, 2, 1);
  insereAresta(&g2, 2, 3);
  insereAresta(&g2, 2, 4);

  exibeGrafo(&g2);

  testaFuncoes(&g2, n);

  printf("\n\nQUARTO EXEMPLO (grafo aleatorio)\n\n");
  n = 10;
  int arestas = 40;

  Grafo *g3 = criaGrafoAleatorio(n, arestas);

  exibeGrafo(g3);

  testaFuncoes(g3, n);

  return 0;
}