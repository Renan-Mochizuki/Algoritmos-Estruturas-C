#include "./Auxiliares/Fila_Ligada.h"
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
    while (noAtual) {
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
    while (noAtual) {
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

  // Se a alocação não foi bem sucedida
  if (!novoNo) {
    printf("Erro ao alocar memória para o novo nó\n");
    return FALSE;
  }

  novoNo->vertice = vertice2;
  novoNo->proximo = noAtual;

  // Se não tiver anterior, então altere o primeiro nó
  if (!noAnterior) {
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

  if (noFoiInserido) {
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
  if (!noAtual || noAtual->vertice != vertice2) {
    return FALSE;
  }

  // Se não tiver anterior, então altere o primeiro nó
  if (!noAnterior) {
    grafo->lista[vertice1] = noAtual->proximo;
    free(noAtual);
    return TRUE;
  }

  noAnterior->proximo = noAtual->proximo;
  free(noAtual);

  return TRUE;
}

// Função que remove uma aresta
Boolean RemoverAresta(Grafo *grafo, int vertice1, int vertice2) {
  if (!ValidarParametros(grafo, vertice1, vertice2)) return FALSE;

  Boolean noFoiInserido = RemoverArestaLista(grafo, vertice1, vertice2);
  RemoverArestaLista(grafo, vertice2, vertice1);

  if (noFoiInserido) {
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
  if (grafo->lista[vertice]) {
    return TRUE;
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

  No *noAtual = grafo->lista[vertice];
  // Loop que percorre cada item da lista (vizinhos)
  while (noAtual) {
    // Se esse vizinho ainda não foi visitado
    if (!visitado[noAtual->vertice]) {
      VisitarGrafoProfundidade(grafo, noAtual->vertice, visitado, vertice);
    }
    noAtual = noAtual->proximo;
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

  // Loop que percorre cada vertice
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

  No *noAtual = grafo->lista[vertice];
  // Loop que percorre cada item da lista (vizinhos)
  while (noAtual) {
    int verticeAtual = noAtual->vertice;
    // Se esse vizinho ainda não foi visitado (branco)
    if (cor[verticeAtual] == 0) {
      anterior[verticeAtual] = vertice;
      VisitarGrafoProfundidadeCores(grafo, verticeAtual, tempo, cor, tempoDescoberta, tempoTermino, anterior);
    }
    noAtual = noAtual->proximo;
  }

  // Aumentando o tempo, marcando o vertice como preto e atribuindo o tempo de término
  (*tempo)++;
  cor[vertice] = 2;
  tempoTermino[vertice] = *tempo;
}

// Função que visita o grafo por profundidade percorrendo todos os vértices
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
    printf("Erro ao alocar memória para a array para a busca em profundidade\n");
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

  // Loop que percorre cada item da lista
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice estiver como branco (ainda não foi visitado), chama a função recursiva
    if (cor[i] == 0) {
      VisitarGrafoProfundidadeCores(grafo, i, &tempo, cor, tempoDescoberta, tempoTermino, anterior);
    }
  }

  // Cabeçalho: alinhado à esquerda
  printf("%-8s %-10s %-12s %-10s %-4s\n", "Vertice", "Anterior", "Descoberta", "Termino", "Cor");

  // Valores: alinhados à direita
  for (int i = 0; i < grafo->numVertices; i++) {
    printf("%8d %10d %12d %10d %4d\n", i, anterior[i], tempoDescoberta[i], tempoTermino[i], cor[i]);
  }

  printf("\n");
  free(cor);
  free(tempoDescoberta);
  free(tempoTermino);
  free(anterior);
}

// Função que cria um novo nó
No *CriarNovoNo(int vertice) {
  No *novoNo = malloc(sizeof(No));
  if (!novoNo) return NULL;
  novoNo->vertice = vertice;
  novoNo->proximo = NULL;
  return novoNo;
}

// Função que imprime os valores da lista
void ImprimirCaminhoLista(No *noLista) {
  if (!noLista) {
    return;
  }

  printf("%d", noLista->vertice);
  noLista = noLista->proximo;

  // Loop pra percorrer até o NULL
  while (noLista != NULL) {
    printf(" -> %d", noLista->vertice);
    noLista = noLista->proximo;
  }
  printf("\n\n");
}

// Função que destroi a lista
void DestruirLista(No *noLista) {
  No *noAtual = noLista;

  // Loop que percorre a lista até o NULL
  while (noAtual != NULL) {
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

  No *noAtual = grafo->lista[verticeAtual];
  // Loop que percorre cada item da lista para um determinado vertice
  while (noAtual) {
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (!visitado[noAtual->vertice]) {
      // Se a busca recursiva retornar verdadeiro, adiciona o vértice atual à lista
      if (VisitarGrafoProfundidadeCaminho(grafo, noAtual->vertice, verticeDestino, visitado, noCabeca)) {
        No *novoNo = CriarNovoNo(verticeAtual);
        novoNo->proximo = noCabeca->proximo;
        noCabeca->proximo = novoNo;
        return TRUE;
      }
    }
    noAtual = noAtual->proximo;
  }
  return FALSE;
}

// Função que encontra o caminho entre dois vértices
No *BuscaProfundidadeCaminho(Grafo *grafo, int verticeOrigem, int verticeDestino) {
  if (!ValidarParametros(grafo, verticeOrigem, verticeDestino)) {
    printf("Parâmetros inválidos\n");
    return NULL;
  }

  // Alocando um array para verificar se o vertice foi visitado
  Boolean *visitado = malloc(sizeof(Boolean) * grafo->numVertices);

  // Se a alocação não foi bem sucedida
  if (!visitado) {
    printf("Erro ao alocar memória para o array de visitados\n");
    return NULL;
  }

  // Inicializando o array com FALSE
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = FALSE;
  }

  // Criando a lista de caminho
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

  No *noAtual = grafo->lista[vertice];
  // Loop que percorre cada item da lista para um determinado vertice
  while (noAtual) {
    int verticeAtual = noAtual->vertice;
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (cor[verticeAtual] == 0) {
      // Atribuindo o vertice anterior
      anterior[verticeAtual] = vertice;
      VisitarGrafoProfundidadeVerificarCiclo(grafo, verticeAtual, tempo, cor, tempoDescoberta, tempoTermino, anterior, possuiAlgumCiclo);
    }
    // Se o vertice atual é cinza e não é o anterior, então existe um ciclo
    // Não precisa perguntar se é cinza, já que não pode ser preto
    else if (anterior[vertice] != verticeAtual) {
      printf("Ciclo encontrado entre %d e %d\n", vertice, verticeAtual);
      *possuiAlgumCiclo = TRUE;
    }
    noAtual = noAtual->proximo;
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
    printf("Erro ao alocar memória para a array para a busca em profundidade\n");
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

  // Loop que percorre cada item da lista
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

  No *noAtual = grafo->lista[vertice];
  // Loop que percorre cada item da lista para um determinado vertice
  while (noAtual) {
    // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
    if (!visitado[noAtual->vertice]) {
      VisitarGrafoProfundidadeComponenteConexo(grafo, noAtual->vertice, visitado, componenteAtual, componentesConexos);
    }
    noAtual = noAtual->proximo;
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
  if (!visitado) {
    printf("Erro ao alocar memória para o array de visitados\n");
    return NULL;
  }

  // Inicializando o array com FALSE
  for (int i = 0; i < grafo->numVertices; i++) {
    visitado[i] = FALSE;
    componentesConexos[i] = -1;
  }

  // Loop que percorre cada item da lista
  for (int i = 0; i < grafo->numVertices; i++) {
    // Se o vertice ainda não foi visitado, chama a função recursiva
    if (!visitado[i]) {
      VisitarGrafoProfundidadeComponenteConexo(grafo, i, visitado, ++componenteAtual, componentesConexos);
    }
  }

  free(visitado);
  return componentesConexos;
}

// Função que imprime os componentes conexos
void ImprimirComponentesConexos(Grafo *grafo, int *componentesConexos) {
  if (!grafo || !componentesConexos) return;

  int numVertices = grafo->numVertices;

  // Descobrir o número máximo de componentes
  int maxComponente = 0;
  for (int i = 0; i < numVertices; i++) {
    if (componentesConexos[i] > maxComponente) {
      maxComponente = componentesConexos[i];
    }
  }

  // Para cada componente, imprimir os vértices pertencentes a ele
  for (int componente = 1; componente <= maxComponente; componente++) {
    printf("Componente %d: ", componente);
    for (int i = 0; i < numVertices; i++) {
      if (componentesConexos[i] == componente) {
        printf("%d ", i);
      }
    }
    printf("\n");
  }
}

// Função recursiva que visita o grafo por largura percorrendo todos os vértices
void VisitarGrafoLargura(Grafo *grafo, int vertice, Boolean *visitado) {
  visitado[vertice] = TRUE;

  Fila *fila = CriarFila();
  InserirValorFila(fila, vertice);
  ImprimirValoresFila(fila);

  // Enquanto a fila não estiver vazia, continue visitando os vértices
  while (!FilaVazia(fila)) {
    int verticeAtual = fila->primeiro->valor;
    printf("Visitando o vertice %d\n", verticeAtual);
    RemoverValorFila(fila);

    // Reinicializar noAtual para o início da lista de adjacência do vértice atual
    No *noAtual = grafo->lista[verticeAtual];
    // Loop que percorre cada item da lista para um determinado vertice
    while (noAtual) {
      // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
      if (!visitado[noAtual->vertice]) {
        InserirValorFila(fila, noAtual->vertice);
        visitado[noAtual->vertice] = TRUE;
        ImprimirValoresFila(fila);
      }
      noAtual = noAtual->proximo;
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

    // Reinicializar noAtual para o início da lista de adjacência do vértice atual
    No *noAtual = grafo->lista[verticeAtual];
    // Loop que percorre cada item da lista para um determinado vertice
    while (noAtual) {
      int vizinho = noAtual->vertice;
      // Se o vertice i é adjacente ao vertice atual e ainda não foi visitado
      if (!visitado[vizinho]) {
        InserirValorFila(fila, vizinho);
        visitado[vizinho] = TRUE;
        anterior[vizinho] = verticeAtual;
      }
      noAtual = noAtual->proximo;
    }
  }
  DestruirFila(fila);
  return FALSE;
}

// Função que encontra o caminho entre dois vértices usando busca em largura
No *BuscaLarguraCaminho(Grafo *grafo, int verticeOrigem, int verticeDestino) {
  if (!ValidarParametros(grafo, verticeOrigem, verticeDestino)) return NULL;

  // Alocando arrays para verificar se o vertice foi visitado e seu anterior
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


  // Chamando a função recursiva
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

        Boolean funcaoSucedida = RemoverAresta(grafo, vertice1, vertice2);

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