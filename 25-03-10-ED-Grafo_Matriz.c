#include "./Auxiliares/Fila_Ligada.h"
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
  // Verifica se vertice1 == vertice2 pois este grafo não permite self-loops
  if (vertice1 == vertice2) return FALSE;

  // Verificação para garantir que o numArestas não aumente caso a aresta já existir
  if (grafo->matriz[vertice1][vertice2] == FALSE) {
    grafo->matriz[vertice1][vertice2] = TRUE;
    grafo->matriz[vertice2][vertice1] = TRUE;
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
    grafo->matriz[vertice2][vertice1] = FALSE;
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
  }
  return grau;
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
  if (!grafo) return -1;
  return grafo->numArestas;
}

// Função recursiva que visita todos os vizinhos de um vértice passado, visitando primeiro os vizinhos dos vizinhos
void VisitarGrafoProfundidade(Grafo *grafo, int vertice, Boolean *visitado, int verticeAnterior) {
  visitado[vertice] = TRUE;
  printf("Visitando o vertice %d (anterior: %d)\n", vertice, verticeAnterior);

  // Loop que percorre cada item da matriz para um determinado vertice
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (grafo->matriz[vertice][i] == TRUE && !visitado[i]) {
      VisitarGrafoProfundidade(grafo, i, visitado, vertice);
    }
  }
}

// Função que visita o grafo por profundidade percorrendo todos os vértices
void BuscaProfundidade(Grafo *grafo) {
  if (!ValidarParametros(grafo, 0, 0)) return;

  // Alocando um array para verificar se o vertice foi visitado
  Boolean *visitado = malloc(sizeof(Boolean) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!visitado) {
    printf("Erro ao alocar memória para o array de visitados\n");
    return;
  }

  // Inicializando o array com FALSE
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = FALSE;
  }

  // Loop que percorre cada item da matriz
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice ainda não foi visitado, chama a função recursiva
    if (!visitado[i]) {
      VisitarGrafoProfundidade(grafo, i, visitado, -1);
    }
  }

  free(visitado);
}

// Função recursiva que visita todos os vizinhos de um vértice passado, visitando primeiro os vizinhos dos vizinhos
// Essa função também atribui cores e tempos de descoberta e término
void VisitarGrafoProfundidadeCores(Grafo *grafo, int vertice, int *tempo, int *cor, int *tempoDescoberta, int *tempoTermino, int *anterior) {
  // Aumentando o tempo, marcando o vertice como cinza e atribuindo o tempo de descoberta
  (*tempo)++;
  cor[vertice] = 1;
  tempoDescoberta[vertice] = *tempo;

  // Loop que percorre cada item da matriz para um determinado vertice
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (grafo->matriz[vertice][i] && cor[i] == 0) {
      anterior[i] = vertice;
      VisitarGrafoProfundidadeCores(grafo, i, tempo, cor, tempoDescoberta, tempoTermino, anterior);
    }
  }

  // Aumentando o tempo, marcando o vertice como preto e atribuindo o tempo de término
  (*tempo)++;
  cor[vertice] = 2;
  tempoTermino[vertice] = *tempo;
}

// Função que visita o grafo por profundidade percorrendo todos os vértices e armazenando as cores, tempos de descoberta e término, e o vértice anterior visitado
void BuscaProfundidadeCores(Grafo *grafo) {
  if (!ValidarParametros(grafo, 0, 0)) return;

  // Alocando um array para armazenar a cor de cada vértice;
  // Cor: 0 - Branco (Ainda não visitado), 1 - Cinza (Sendo processado), 2 - Preto (Finalizado)
  // Tempo de descoberta e término e o vértice anterior visitado de cada vértice
  int *cor = malloc(sizeof(int) * grafo->numVertices);
  int *tempoDescoberta = malloc(sizeof(int) * grafo->numVertices);
  int *tempoTermino = malloc(sizeof(int) * grafo->numVertices);
  int *anterior = malloc(sizeof(int) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!cor || !tempoDescoberta || !tempoTermino || !anterior) {
    printf("Erro ao alocar memória para a busca em profundidade\n");
    return;
  }

  // Inicializando as arrays
  for (int i = 0; i < grafo->numVertices; i++) {
    cor[i] = 0;
    tempoDescoberta[i] = -1;
    tempoTermino[i] = -1;
    anterior[i] = -1;
  }

  int tempo = 0;

  // Loop que percorre cada item da matriz
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice estiver como branco (ainda não foi visitado), chama a função recursiva
    if (cor[i] == 0) {
      VisitarGrafoProfundidadeCores(grafo, i, &tempo, cor, tempoDescoberta, tempoTermino, anterior);
    }
  }

  printf("%-8s %-10s %-12s %-10s %-4s\n", "Vertice", "Anterior", "Descoberta", "Termino", "Cor");
  for (int i = 0; i < grafo->numVertices; i++) {
    printf("%8d %10d %12d %10d %4d\n", i, anterior[i], tempoDescoberta[i], tempoTermino[i], cor[i]);
  }
  printf("\n");

  free(cor);
  free(tempoDescoberta);
  free(tempoTermino);
  free(anterior);
}

// Lista ligada que armazenará o caminho encontrado
typedef struct node {
  int vertice;
  struct node *proximo;
} No;

// Função que cria um novo nó para a lista ligada
No *CriarNovoNo(int vertice) {
  No *novoNo = malloc(sizeof(No));
  if (!novoNo) return NULL;
  novoNo->vertice = vertice;
  novoNo->proximo = NULL;
  return novoNo;
}

// Função que imprime os valores da lista
void ImprimirCaminhoLista(No *noLista) {
  if (!noLista) return;
  printf("%d", noLista->vertice);
  noLista = noLista->proximo;
  while (noLista) {
    printf(" -> %d", noLista->vertice);
    noLista = noLista->proximo;
  }
  printf("\n\n");
}

// Função que destroi a lista
void DestruirLista(No *noLista) {
  No *noAtual = noLista;
  while (noAtual) {
    No *noProximo = noAtual->proximo;
    free(noAtual);
    noAtual = noProximo;
  }
}

// Função recursiva que encontra o caminho entre dois vértices
Boolean VisitarGrafoProfundidadeCaminho(Grafo *grafo, int verticeAtual, int verticeDestino, Boolean *visitado, No *noCabeca) {
  visitado[verticeAtual] = TRUE;

  // Se o vértice atual é o destino, adiciona à lista
  if (verticeAtual == verticeDestino) {
    No *novoNo = CriarNovoNo(verticeAtual);
    novoNo->proximo = noCabeca->proximo;
    noCabeca->proximo = novoNo;
    return TRUE;
  }

  // Loop que percorre cada item da matriz para um determinado vertice
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (grafo->matriz[verticeAtual][i] && !visitado[i]) {
      // Se a busca recursiva retornar verdadeiro, adiciona o vértice atual à lista
      if (VisitarGrafoProfundidadeCaminho(grafo, i, verticeDestino, visitado, noCabeca)) {
        No *novoNo = CriarNovoNo(verticeAtual);
        novoNo->proximo = noCabeca->proximo;
        noCabeca->proximo = novoNo;
        return TRUE;
      }
    }
  }
  return FALSE;
}

// Função que encontra o caminho entre dois vértices
No *BuscaProfundidadeCaminho(Grafo *grafo, int verticeOrigem, int verticeDestino) {
  if (!ValidarParametros(grafo, verticeOrigem, verticeDestino)) return NULL;

  // Alocando um array para verificar se o vertice foi visitado
  Boolean *visitado = malloc(sizeof(Boolean) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!visitado) {
    printf("Erro ao alocar memória para o array de visitados\n");
    return NULL;
  }

  // Inicializando o array com FALSE
  for (int i = 0; i < grafo->numVertices; i++)
    visitado[i] = FALSE;

  // Criango a lista de caminho
  No *noCabeca = CriarNovoNo(-1);

  // Chamando a função recursiva
  if (VisitarGrafoProfundidadeCaminho(grafo, verticeOrigem, verticeDestino, visitado, noCabeca)) {
    No *noSemCabeca = noCabeca->proximo;
    free(noCabeca);
    free(visitado);
    return noSemCabeca;
  }

  // Se não encontrou o caminho, libera a lista e retorna NULL
  free(visitado);
  DestruirLista(noCabeca);
  return NULL;
}

// Função recursiva que visita todos os vértices adjacentes a um vértice passado, verificando se existe algum ciclo
void VisitarGrafoProfundidadeVerificarCiclo(Grafo *grafo, int vertice, int *tempo, int *cor, int *tempoDescoberta, int *tempoTermino, int *anterior, int *possuiAlgumCiclo) {
  // Aumentando o tempo, marcando o vertice como cinza e atribuindo o tempo de descoberta
  (*tempo)++;
  cor[vertice] = 1;
  tempoDescoberta[vertice] = *tempo;

  // Loop que percorre cada item da matriz para um determinado vertice
  for (int i = 0; i < grafo->numVertices; i++) {
    if (grafo->matriz[vertice][i]) {
      // Se o vertice i ainda não foi visitado (branco)
      if (cor[i] == 0) {
        // Atribui o vertice atual como anterior do vertice i
        anterior[i] = vertice;
        VisitarGrafoProfundidadeVerificarCiclo(grafo, i, tempo, cor, tempoDescoberta, tempoTermino, anterior, possuiAlgumCiclo);
      }
      // Se o vertice atual é cinza e não é o anterior, então existe um ciclo
      // Não precisa perguntar se é cinza, já que não pode ser preto
      else if (anterior[vertice] != i) {
        printf("Ciclo encontrado entre %d e %d\n", vertice, i);
        *possuiAlgumCiclo = TRUE;
      }
    }
  }

  // Aumentando o tempo, marcando o vertice como preto e atribuindo o tempo de término
  (*tempo)++;
  cor[vertice] = 2;
  tempoTermino[vertice] = *tempo;
}

// Função que verifica se existe algum ciclo no grafo
Boolean BuscaProfundidadeVerificarCiclo(Grafo *grafo) {
  if (!ValidarParametros(grafo, 0, 0)) return FALSE;

  Boolean possuiAlgumCiclo = FALSE;

  // Alocando um array para armazenar a cor de cada vértice, tempo de descoberta e término e o vértice anterior visitado de cada vértice
  int *cor = malloc(sizeof(int) * grafo->numVertices);
  int *tempoDescoberta = malloc(sizeof(int) * grafo->numVertices);
  int *tempoTermino = malloc(sizeof(int) * grafo->numVertices);
  int *anterior = malloc(sizeof(int) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!cor || !tempoDescoberta || !tempoTermino || !anterior) {
    printf("Erro ao alocar memória para a busca em profundidade\n");
    return FALSE;
  }

  // Inicializando as arrays
  for (int i = 0; i < grafo->numVertices; i++) {
    cor[i] = 0;
    tempoDescoberta[i] = -1;
    tempoTermino[i] = -1;
    anterior[i] = -1;
  }

  int tempo = 0;

  // Loop que percorre cada item da matriz
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice estiver como branco (ainda não foi visitado), chama a função recursiva
    if (cor[i] == 0) {
      VisitarGrafoProfundidadeVerificarCiclo(grafo, i, &tempo, cor, tempoDescoberta, tempoTermino, anterior, &possuiAlgumCiclo);
    }
  }

  free(cor);
  free(tempoDescoberta);
  free(tempoTermino);
  free(anterior);

  return possuiAlgumCiclo;
}

// Função recursiva que visita todos os vértices adjacentes a um vértice passado, atribuindo componentes conexos
void VisitarGrafoProfundidadeComponenteConexo(Grafo *grafo, int vertice, Boolean *visitado, int componenteAtual, int *componentesConexos) {
  visitado[vertice] = TRUE;
  componentesConexos[vertice] = componenteAtual;

  printf("Visitando o vertice %d (componente: %d)\n", vertice, componenteAtual);

  // Loop que percorre cada item da matriz para um determinado vertice
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (grafo->matriz[vertice][i] && !visitado[i]) {
      VisitarGrafoProfundidadeComponenteConexo(grafo, i, visitado, componenteAtual, componentesConexos);
    }
  }
}

// Função que encontra os componentes conexos do grafo usando busca em profundidade e retorna uma array com os componentes conexos
int *BuscaProfundidadeComponenteConexo(Grafo *grafo) {
  if (!ValidarParametros(grafo, 0, 0)) return NULL;

  // Alocando um array para verificar se o vertice foi visitado e um array para armazenar os componentes conexos
  Boolean *visitado = malloc(sizeof(Boolean) * grafo->numVertices);
  int *componentesConexos = malloc(sizeof(int) * grafo->numVertices);

  int componenteAtual = 0;

  // Se a alocação não foi bem sucedida
  if (!visitado || !componentesConexos) {
    printf("Erro ao alocar memória\n");
    return NULL;
  }

  // Inicializando as arrays
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = FALSE;
    componentesConexos[i] = -1;
  }

  // Loop que percorre cada item da matriz
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice ainda não foi visitado, chama a função recursiva
    if (!visitado[i]) {
      VisitarGrafoProfundidadeComponenteConexo(grafo, i, visitado, ++componenteAtual, componentesConexos);
    }
  }
  free(visitado);
  return componentesConexos;
}

// Função que imprime os componentes conexos do grafo
void ImprimirComponentesConexos(Grafo *grafo, int *componentesConexos) {
  if (!grafo || !componentesConexos) return;

  int numVertices = grafo->numVertices;

  // Descobrir o número máximo de componentes
  int maxComponente = 0;
  for (int i = 0; i < numVertices; i++) {
    if (componentesConexos[i] > maxComponente) maxComponente = componentesConexos[i];
  }

  // Para cada componente, imprime os vértices que pertencem a ele
  for (int componente = 1; componente <= maxComponente; componente++) {
    printf("Componente %d: ", componente);
    for (int i = 0; i < numVertices; i++) {
      if (componentesConexos[i] == componente) printf("%d ", i);
    }
    printf("\n");
  }
}

// Função que visita o grafo por largura percorrendo todos os vértices, usando uma fila
void VisitarGrafoLargura(Grafo *grafo, int vertice, Boolean *visitado) {
  visitado[vertice] = TRUE;

  Fila *fila = CriarFila();
  InserirValorFila(fila, vertice);
  ImprimirValoresFila(fila);

  // Enquanto a fila não estiver vazia, continua visitando os vértices
  while (!FilaVazia(fila)) {
    int verticeAtual = fila->primeiro->valor;
    printf("Visitando o vertice %d\n", verticeAtual);
    RemoverValorFila(fila);

    // Reinicializar noAtual para o início da lista de adjacência do vértice atual
    for (int i = 0; i < grafo->numVertices; i++) {
      // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
      if (grafo->matriz[verticeAtual][i] == TRUE && !visitado[i]) {
        InserirValorFila(fila, i);
        visitado[i] = TRUE;
        ImprimirValoresFila(fila);
      }
    }
  }
  DestruirFila(fila);
}

// Função que visita o grafo por largura percorrendo todos os vértices
void BuscaLargura(Grafo *grafo) {
  if (!ValidarParametros(grafo, 0, 0)) return;

  // Alocando um array para verificar se o vertice foi visitado
  Boolean *visitado = malloc(sizeof(Boolean) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!visitado) {
    printf("Erro ao alocar memória para o array de visitados\n");
    return;
  }

  // Inicializando o array com FALSE
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = FALSE;
  }

  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice ainda não foi visitado, chama a função recursiva
    if (!visitado[i]) {
      VisitarGrafoLargura(grafo, i, visitado);
    }
  }
  free(visitado);
}

// Função recursiva que visita o grafo por largura começando por uma origem e para até achar um vértice destino
Boolean VisitarGrafoLarguraCaminho(Grafo *grafo, int verticeOrigem, int verticeDestino, Boolean *visitado, int *anterior) {
  Fila *fila = CriarFila();
  InserirValorFila(fila, verticeOrigem);
  visitado[verticeOrigem] = TRUE;
  anterior[verticeOrigem] = -1;

  while (!FilaVazia(fila)) {
    int verticeAtual = fila->primeiro->valor;
    RemoverValorFila(fila);

    // Se o destino foi encontrado
    if (verticeAtual == verticeDestino) {
      DestruirFila(fila);
      return TRUE;
    }

    for (int i = 0; i < grafo->numVertices; i++) {
      // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
      if (grafo->matriz[verticeAtual][i] && !visitado[i]) {
        InserirValorFila(fila, i);
        visitado[i] = TRUE;
        anterior[i] = verticeAtual;
      }
    }
  }
  DestruirFila(fila);
  return FALSE;
}

// Função que encontra o caminho entre dois vértices usando busca em largura
No *BuscaLarguraCaminho(Grafo *grafo, int verticeOrigem, int verticeDestino) {
  if (!ValidarParametros(grafo, verticeOrigem, verticeDestino)) return NULL;

  // Alocando um array para verificar se o vertice foi visitado e um array para armazenar o vértice anterior visitado
  Boolean *visitado = malloc(sizeof(Boolean) * grafo->numVertices);
  int *anterior = malloc(sizeof(int) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!visitado || !anterior) {
    printf("Erro ao alocar memória\n");
    return NULL;
  }

  // Inicializando os arrays
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = FALSE;
    anterior[i] = -1;
  }

  // Chamando a função recursiva para encontrar o caminho
  if (VisitarGrafoLarguraCaminho(grafo, verticeOrigem, verticeDestino, visitado, anterior)) {
    // Diferentemente da busca em profundidade, em que o caminho de uma origem a qualquer destino pode ser
    // construido usando a pilha de chamadas atual, na busca em largura são construidos todos caminhos para quaisquer
    // destinos, então é necessário que separemos o caminho que queremos
    int atual = verticeDestino;
    No *caminho = NULL;
    while (atual != -1) {
      No *novoNo = CriarNovoNo(atual);
      novoNo->proximo = caminho;
      caminho = novoNo;
      atual = anterior[atual];
    }
    free(visitado);
    free(anterior);
    return caminho;
  }
  
  // Se não encontrou o caminho, libera a lista e retorna NULL
  free(visitado);
  free(anterior);
  return NULL;
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

  while (escolha > 0 && escolha < 18) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Inserir uma aresta\n");
    printf("2 - Remover uma aresta\n");
    printf("3 - Verificar quantas arestas o grafo possui\n");
    printf("4 - Verificar se uma aresta existe\n");
    printf("5 - Verificar se um vertice possui vizinhos\n");
    printf("6 - Calcular grau de um vertice\n");
    printf("7 - Imprimir grafo\n");
    printf("8 - Visitar grafo por profundidade\n");
    printf("9 - Visitar grafo por profundidade mostrando cores e tempo\n");
    printf("10 - Encontrar caminho ate um destino (Profundidade)\n");
    printf("11 - Verificar ciclos\n");
    printf("12 - Verificar componentes conexos\n");
    printf("13 - Visitar grafo por largura\n");
    printf("14 - Encontrar caminho ate um destino (Largura)\n");
    printf("17 - Limpar grafo\n");
    printf("18 - Sair\n");

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

      if (grau < 0) {
        printf("O vertice nao existe\n");
        break;
      }

      printf("O grau do vertice %d e %d\n", vertice1, grau);
      break;

    case 7:
      ImprimirValores(grafo);
      break;

    case 8:
      printf("Visitando o grafo por profundidade\n");
      BuscaProfundidade(grafo);
      break;

    case 9:
      printf("Visitando o grafo por profundidade utilizando cores\n");
      BuscaProfundidadeCores(grafo);
      break;

    case 10:
      printf("Digite o vertice de origem\n");
      scanf("%d", &vertice1);

      if (vertice1 < 0) break;

      printf("Digite o vertice de destino\n");
      scanf("%d", &vertice2);

      if (vertice2 < 0) break;

      No *noListaCaminho = BuscaProfundidadeCaminho(grafo, vertice1, vertice2);

      if (noListaCaminho) {
        printf("O caminho entre os vertices %d e %d e:\n", vertice1, vertice2);
        ImprimirCaminhoLista(noListaCaminho);
        DestruirLista(noListaCaminho);
      } else {
        printf("Nao existe caminho entre os vertices %d e %d\n", vertice1, vertice2);
      }

      break;

    case 11:
      printf("Verificando se o grafo tem ciclos\n");

      if (BuscaProfundidadeVerificarCiclo(grafo)) {
        printf("O grafo é cíclico\n");
      } else {
        printf("O grafo é acíclico\n");
      }

      break;

    case 12:
      printf("Verificando componentes conexos\n");
      int *componentesConexos = BuscaProfundidadeComponenteConexo(grafo);
      if (componentesConexos) {
        printf("\nComponentes conexos:\n");
        ImprimirComponentesConexos(grafo, componentesConexos);
        free(componentesConexos);
      } else {
        printf("Erro ao verificar componentes conexos\n");
      }
      break;

    case 13:
      printf("Visitando o grafo por largura\n");
      BuscaLargura(grafo);
      break;

    case 14:
      printf("Digite o vertice de origem\n");
      scanf("%d", &vertice1);

      if (vertice1 < 0) break;

      printf("Digite o vertice de destino\n");
      scanf("%d", &vertice2);

      if (vertice2 < 0) break;

      No *noListaCaminhoLargura = BuscaLarguraCaminho(grafo, vertice1, vertice2);

      if (noListaCaminhoLargura) {
        printf("O caminho entre os vertices %d e %d e:\n", vertice1, vertice2);
        ImprimirCaminhoLista(noListaCaminhoLargura);
        DestruirLista(noListaCaminhoLargura);
      } else {
        printf("Nao existe caminho entre os vertices %d e %d\n", vertice1, vertice2);
      }
      break;

    case 17:
      LimparGrafo(grafo);
      printf("O grafo foi limpo\n");
      break;
    }
  }

  DestruirGrafo(grafo);

  return 0;
}