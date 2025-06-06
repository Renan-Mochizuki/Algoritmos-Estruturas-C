/*********************************************************************/
/**   ACH2024 - Algoritmos e Estruturas de Dados II                 **/
/**   EACH-USP - Primeiro Semestre de 2025                          **/
/**   Prof. Luciano Digiampietri                                    **/
/**                                                                 **/
/**   Primeiro Exercicio-Programa                                   **/
/**                                                                 **/
/**   Renan Mochizuki                             <N USP>           **/
/**                                                                 **/
/*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define NUM_CARACT 10
#define MAX_VALOR 99

#define true 1
#define false 0

typedef int bool;

/* Estrutura para representar nosso grafo usando matriz binaria de adjacencias */
typedef struct {
  int numVertices;
  int numArestas;
  bool **matriz;
  int **caracteristicas;
} Grafo;

// Implementação da fila
typedef struct nodeFila {
  int valor;
  int distancia;
  struct nodeFila *proximo;
} NoFila;

typedef struct {
  NoFila *primeiro;
  NoFila *ultimo;
  int tamanho;
} Fila;

// Função que retorna o ponteiro para uma fila
Fila *CriarFila() {
  Fila *fila = malloc(sizeof(Fila));
  fila->primeiro = NULL;
  fila->ultimo = NULL;
  fila->tamanho = 0;
  return fila;
}

// Função que destroi a fila
void DestruirFila(Fila *fila) {
  if (!fila) return;

  NoFila *noAtual = fila->primeiro;
  while (noAtual) {
    NoFila *noProximo = noAtual->proximo;
    free(noAtual);
    noAtual = noProximo;
  }

  free(fila);
}

// Função que vai inserir um valor no final da fila
bool InserirValorFila(Fila *fila, int valor, int distancia) {
  NoFila *novoItem = malloc(sizeof(NoFila));
  novoItem->valor = valor;
  novoItem->distancia = distancia;
  novoItem->proximo = NULL;

  // Se a fila estiver vazia
  if (!fila->primeiro) {
    fila->primeiro = novoItem;
    fila->ultimo = novoItem;
  } else { // Fila não está vazia
    NoFila *ultimoAtual = fila->ultimo;
    ultimoAtual->proximo = novoItem;

    // Atualiza o último item da fila
    fila->ultimo = novoItem;
  }

  fila->tamanho++;
  return true;
}

// Função que vai remover o primeiro valor da fila
bool RemoverValorFila(Fila *fila) {
  // Se a fila estiver vazia
  if (fila->tamanho == 0) return false;

  NoFila *primeiroItem = fila->primeiro;

  // Alterando o primeiro da fila
  fila->primeiro = primeiroItem->proximo;

  free(primeiroItem);
  fila->tamanho--;

  return true;
}

// Função que verifica se a fila está vazia
bool FilaVazia(Fila *fila) {
  if (fila->tamanho == 0) return true;
  return false;
}

/* Funcao auxiliar para o sistema de correcao automatica (nao mexer) */
void printf123() {
  // Funcao usada pelo sistema de correcao automatica (nao mexer)
}

/* Funcao que inicializa o grafo cujo endereco foi passado como parametro.
   Isto e, cria a matriz de adjacencias (preenchida com false),
   e atribui valor para numVertices (recebendo o valor passado por parametro)
   e numArestas igual a zero.
*/
bool inicializaGrafo(Grafo *g, int vertices) {
  if (g == NULL || vertices < 1) return false;
  g->numVertices = vertices;
  g->numArestas = 0;
  int x, y;
  g->matriz = (bool **)malloc(sizeof(bool *) * vertices);
  g->caracteristicas = (int **)malloc(sizeof(int *) * vertices);
  for (x = 0; x < vertices; x++) {
    g->matriz[x] = (bool *)malloc(sizeof(bool) * vertices);
    for (y = 0; y < vertices; y++) {
      g->matriz[x][y] = false;
    }
    g->caracteristicas[x] = (int *)malloc(sizeof(int) * NUM_CARACT);
    for (y = 0; y < NUM_CARACT; y++) {
      g->caracteristicas[x][y] = -1;
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
  for (x = 0; x < g->numVertices; x++) {
    free(g->matriz[x]);
    free(g->caracteristicas[x]);
  }
  free(g->matriz);
  free(g->caracteristicas);
  g->numVertices = 0;
  g->numArestas = 0;
  g->matriz = NULL;
  g->caracteristicas = NULL;
  return true;
}

/* Funcao que retorna o numero de vertices do grafo apontado por g, caso o
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeVertices(Grafo *g) {
  if (g != NULL)
    return g->numVertices;
  else
    return -1;
}

/* Funcao que retorna o numero de arestas do grafo apontado por g, caso o
   endereco armazenado em g seja diferente de NULL. Caso contrario, retorna -1.
*/
int numeroDeArestas(Grafo *g) {
  if (g != NULL)
    return g->numArestas;
  else
    return -1;
}

/* Funcao que retorna true se o vertice v possui um ou mais
   vertices adjacentes (vizinhos).
*/
bool possuiVizinhos(Grafo *g, int v) {
  if (!g || v < 0 || v >= g->numVertices) return false;
  int x;
  for (x = 0; x < g->numVertices; x++)
    if (g->matriz[v][x]) return true;
  return false;
}

/* Funcao que insere uma nova aresta no grafo.
   Se os vertices passados como parametro forem validos, ha duas possibilidades:
   - a aresta nao existia;
   - a aresta existia.
*/
bool insereAresta(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || v1 == v2) return false;
  if (g->matriz[v1][v2] == false) {
    g->matriz[v1][v2] = true;
    g->matriz[v2][v1] = true;
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
  g->matriz[v2][v1] = false;
  g->numArestas--;
  return true;
}

/* Funcao que adiciona atualiza o valor de da caracteristica c do vertice v.
 */
bool atualizaCaracteristica(Grafo *g, int v, int c, int valor) {
  if (!g || v < 0 || c < 0 || v >= g->numVertices || c >= NUM_CARACT || valor < -1) return false;
  g->caracteristicas[v][c] = valor;
  return true;
}

/* Funcao que retorna true se existe uma aresta valida entre v1 e v2
   e false caso contrario.
*/
bool arestaExiste(Grafo *g, int v1, int v2) {
  if (!g || v1 < 0 || v2 < 0 || v1 >= g->numVertices || v2 >= g->numVertices || g->matriz[v1][v2] == false) return false;
  return true;
}

/* Funcao que cria um grafo com o numero de vertices e
   numero de arestas passados como parametro e retorna seu endereco.
*/
Grafo *criaGrafoAleatorio(int numVertices, int numArestas) {
  printf("### Criando grafo: v=%i e a=%i ###\n", numVertices, numArestas);
  int x, y, a = 0;
  if (numVertices < 1 || numArestas >= numVertices * (numVertices - 1) / 2) {
    printf("Parametros invalidos, o grafo nao sera gerado.\n");
    return NULL;
  }
  Grafo *g = (Grafo *)malloc(sizeof(Grafo));
  inicializaGrafo(g, numVertices);
  while (a < numArestas) {
    x = rand() % numVertices;
    y = rand() % numVertices;
    if (x != y && g->matriz[x][y] == false) {
      g->matriz[x][y] = true;
      g->matriz[y][x] = true;
      a++;
    }
  }
  g->numArestas = numArestas;
  for (x = 0; x < numVertices; x++) {
    for (y = 0; y < NUM_CARACT; y++) {
      if (rand() % 3 < 2) {
        g->caracteristicas[x][y] = rand() % 5;
      }
    }
  }
  return g;
}

/* Funcao desenvolvida para exibir um grafo, no formato de uma matriz
   de adjacencia.
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
  printf("\nCaracteristicas:\n");

  for (x = 0; x < g->numVertices; x++) {
    printf("[%2i]", x);
    for (y = 0; y < NUM_CARACT; y++)
      printf(" %3i", g->caracteristicas[x][y]);
    printf("\n");
  }
}

/* Funcao que exibe os valores de um arranjo de numeros reais */
void exibeArranjoReais(double *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf("  v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%3.2f\t", arranjo[x]);
  }
  printf("\n\n");
}

/* Funcao que exibe os valores de um arranjo de numeros inteiros */
void exibeArranjoInteiros(int *arranjo, int n) {
  int x;
  for (x = 0; x < n; x++)
    printf(" v%i\t", x);
  printf("\n");
  for (x = 0; x < n; x++) {
    printf("%3i\t", arranjo[x]);
  }
  printf("\n\n");
}

/* FUNCOES QUE DEVEM SER COMPLETADAS PARA RESOLVER O EP.
   A DESCRICAO DE CADA FUNCAO ESTA NO ENUNCIADO DO EP.
   www.each.usp.br/digiampietri/ACH2024/ep1/ep1.pdf        */

/* Funcao que calcula a homofilia entre o vertice v e os demais */
void homofilia(Grafo *g, int v, int *valores) {

  // Lógica: Percorrer todas as caracteristicas de todos os vertices,
  // verificando se aquela caracteristica é a mesma do vertice v

  int numComum;

  // Loop que percorre todos vertices
  for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
    numComum = 0;
    // Loop das caracteristicas
    for (int i = 0; i < NUM_CARACT; i++) {
      // Se a caracteristica do vertice atual é igual a do vertice v (e não é -1)
      if (g->caracteristicas[v][i] == g->caracteristicas[vAtual][i] && g->caracteristicas[v][i] != -1) {
        numComum++;
      }
    }
    valores[vAtual] = numComum;
  }
}

/* Funcao que pondera as caracteristicas comuns entre o vertice v e os demais
   de acordo com sua raridade. */
void raridade(Grafo *g, int v, double *valores) {

  // Lógica: Percorrer todas as caracteristicas de todos os vertices,
  // verificando se aquela caracteristica é a mesma do vertice v
  // contudo, é necessário fazer outro loop antes para contarmos quantas
  // ocorrências aquela caracteristica tem, para assim, realizar o calculo da raridade

  // Zerando a array valores
  for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
    valores[vAtual] = 0;
  }

  // Loop que percorre todas as caracteristicas, analisando as caracteristicas de v
  // e armazena quantas caracteristicas em comum v tem com todos outros vertices
  for (int i = 0; i < NUM_CARACT; i++) {
    int caracteristicaAtual = g->caracteristicas[v][i];
    if (caracteristicaAtual == -1) continue;

    // Conta quantos vértices têm essa característica
    int contagemCaracteristica = 0;
    for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
      if (g->caracteristicas[vAtual][i] == caracteristicaAtual) {
        contagemCaracteristica++;
      }
    }

    // Agora que temos quantos vertices que possuem essa mesma caracteristica,
    // podemos fazer o calculo da raridade
    // Não é preciso verificar se caracteristica é -1, pois já foi verificado
    for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
      if (g->caracteristicas[vAtual][i] == caracteristicaAtual) {
        valores[vAtual] += (double)1 / contagemCaracteristica;
      }
    }
  }
}

/* Funcao que da mais pesos as caracteristicas mais presentes nos amigos
   do vertice v e calcula a influencia social entre o vertice v e os demais */
void influenciaSocial(Grafo *g, int v, int *valores) {

  // Lógica: Percorrer todas as caracteristicas de todos os vertices,
  // e então, verificar se aquele vertice é vizinho de v e se a caracteristica
  // é a mesma do vertice vAtual, somando +1 para cada caracteristica em comum

  for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
    valores[vAtual] = 0;

    // Loop para percorrer todas as caracteristicas do vAtual
    for (int iCaract = 0; iCaract < NUM_CARACT; iCaract++) {
      if (g->caracteristicas[vAtual][iCaract] == -1) continue;

      // Loop que percorre todos os vertices do grafo
      for (int i = 0; i < g->numVertices; i++) {
        // Se o vertice i é um vizinho e esse vizinho possui a mesma caracteristica que o vAtual
        if (g->matriz[v][i] == true && g->caracteristicas[i][iCaract] == g->caracteristicas[vAtual][iCaract]) {
          valores[vAtual]++;
        }
      }
    }
  }
}

/* Funcao que calcula o numero de amigos em comum entre o vertice v
   e os demais */
void amizadesEmComum(Grafo *g, int v, int *valores) {

  // Lógica: Percorrer todos os vertices do grafo, comparando os vizinhos
  // do vertice atual com os vizinhos do vertice v
  // ou seja, teremos que percorrer todos os vertices para cada vertice

  int numComum;

  for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
    numComum = 0;
    for (int i = 0; i < g->numVertices; i++) {
      // Se o vertice i é vizinho do vertice atual e também é vizinho do vertice v
      if (g->matriz[v][i] == true && g->matriz[vAtual][i] == true) {
        numComum++;
      }
    }
    valores[vAtual] = numComum;
  }
}

// Função auxiliar para visitar o grafo em largura
// Marcando a distância de cada vértice a partir do vértice inicial
void VisitarGrafoLargura(Grafo *grafo, int vertice, bool *visitado, int *distancias) {
  int distanciaPercorrida = 0;
  Fila *fila = CriarFila();

  visitado[vertice] = true;

  InserirValorFila(fila, vertice, distanciaPercorrida);

  // Loop até a fila ficar vazia
  while (!FilaVazia(fila)) {
    int verticeAtual = fila->primeiro->valor;
    // Como vamos começar a percorrer a partir do verticeAtual
    // Atualizamos a distanciaPercorrida para corresponder a esse verticeAtual
    distanciaPercorrida = fila->primeiro->distancia;
    distancias[verticeAtual] = distanciaPercorrida;
    RemoverValorFila(fila);

    // Loop que percorre todos os vertices do grafo
    for (int i = 0; i < grafo->numVertices; i++) {
      // Se o vertice i é vizinho do vertice atual e ainda não foi visitado
      if (grafo->matriz[verticeAtual][i] == true && !visitado[i]) {
        InserirValorFila(fila, i, distanciaPercorrida + 1);
        visitado[i] = true;
      }
    }
  }
  DestruirFila(fila);
}

// Função que faz a busca em largura no grafo e calcula as distâncias
// entre o vértice inicial e os demais vértices
void BuscaLargura(Grafo *grafo, int vertice, int *distancias) {

  // Alocando um array para verificar se o vertice foi visitado
  bool *visitado = malloc(sizeof(bool) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!visitado) {
    printf("Erro ao alocar memória para o array de visitados\n");
    return;
  }

  // Inicializando o array com FALSE
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = false;
  }

  VisitarGrafoLargura(grafo, vertice, visitado, distancias);

  for (int i = 0; i < grafo->numVertices; i++) {
    if (!visitado[i]) {
      // Se o vertice não foi visitado, atribui numVertices
      distancias[i] = grafo->numVertices;
    }
  }

  free(visitado);
}

/* Funcao que calcula a distancia entre o vertice v e os demais */
void proximidadeSocial(Grafo *g, int v, int *valores) {

  // Lógica: Usar a busca em largura que implementa uma fila na qual cada nó possui
  // um valor distancia, armazenando a distancia no proprio nó de acordo, aumentando-a
  // de acordo com que a busca vai avançando, isso foi feito para que possamos acompanhar
  // a distância correta quando a busca continua em vertices anteriores.
  // Se fosse busca em profundidade poderiamos apenas lidar com isso por meio de uma variavel
  // int nos parametros da função recursiva

  // Chamando a funcao de busca em largura que irá calcular as distâncias
  BuscaLargura(g, v, valores);
}

/* Funcao que usa o principio da conexao preferencial e calcula
   o grau de cada vertice */
void conexaoPreferencial(Grafo *g, int v, int *valores) {

  // Lógica: Percorrer todos os vertices do grafo, contando quantos vizinhos
  // cada vertice tem

  int grau = 0;
  for (int vAtual = 0; vAtual < g->numVertices; vAtual++) {
    grau = 0;
    for (int i = 0; i < g->numVertices; i++) {
      // Verifica se o vertice é vizinho do vertice que está sendo verificado
      if (g->matriz[vAtual][i] == true) grau++;
    }
    valores[vAtual] = grau;
  }
}

/* FIM DAS FUNCOES QUE DEVEM SER COMPLETADAS */

/* Funcao que invoca e exibe os valores de cada uma das funcoes que voces
   devem implementar neste EP.
*/
void testaFuncoes(Grafo *g, int n, int v) {

  int *valoresInteiros = (int *)malloc(sizeof(int) * n);
  double *valoresReais = (double *)malloc(sizeof(double) * n);

  printf("\nRealizando analise em relacao ao vertice %i.\n", v);

  printf("Homofilia:\n");
  homofilia(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Raridade:\n");
  raridade(g, v, valoresReais);
  exibeArranjoReais(valoresReais, n);

  printf("Influencia Social:\n");
  influenciaSocial(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Amizades em Comum:\n");
  amizadesEmComum(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Proximidade Social:\n");
  proximidadeSocial(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  printf("Conexao Preferencial:\n");
  conexaoPreferencial(g, v, valoresInteiros);
  exibeArranjoInteiros(valoresInteiros, n);

  free(valoresInteiros);
  free(valoresReais);
}

/* Funcao main para testar as funcoes implementadas neste EP.
   Esta parte do codigo nao sera usada na correcao do EP e nao contempla
   todos os testes possiveis.
   Fique a vontade para realizar testes adicionais.
*/
int main() {

  int n = 5;

  Grafo g1;

  printf("PRIMEIRO EXEMPLO\n");

  inicializaGrafo(&g1, n);
  insereAresta(&g1, 0, 1);
  insereAresta(&g1, 0, 2);
  insereAresta(&g1, 1, 4);
  insereAresta(&g1, 1, 3);
  insereAresta(&g1, 2, 3);

  atualizaCaracteristica(&g1, 0, 2, 2);
  atualizaCaracteristica(&g1, 0, 1, 1);
  atualizaCaracteristica(&g1, 1, 1, 1);
  atualizaCaracteristica(&g1, 1, 2, 2);
  atualizaCaracteristica(&g1, 1, 3, 3);
  atualizaCaracteristica(&g1, 2, 2, 2);
  atualizaCaracteristica(&g1, 3, 2, 2);
  atualizaCaracteristica(&g1, 4, 3, 3);
  atualizaCaracteristica(&g1, 4, 2, 5);
  atualizaCaracteristica(&g1, 4, 4, 4);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n, 0);

  printf("\n\nSEGUNDO EXEMPLO\n");

  // Excluindo duas arestas do grafo
  removeAresta(&g1, 0, 2);
  removeAresta(&g1, 2, 3);

  exibeGrafo(&g1);

  testaFuncoes(&g1, n, 0);

  printf("\n\nTERCEIRO EXEMPLO\n");
  // Analisando outro vertice

  exibeGrafo(&g1);

  testaFuncoes(&g1, n, 3);

  /* Grafo gerado aleatoriamente - pode ficar diferente
     de acordo com o compilador usado.                 */
  printf("\n\nQUARTO EXEMPLO\n\n");
  n = 6;
  int arestas = 8;

  Grafo *g2 = criaGrafoAleatorio(n, arestas);

  exibeGrafo(g2);

  testaFuncoes(g2, n, 1);

  return 0;
}