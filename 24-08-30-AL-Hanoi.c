#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que imprime a resolução do problema das Torres de Hanoi, movendo os discos de uma origem para um destino
// Complexidade: O(2^n)
// Caso base: T(1) = 1C
// T(n) = T(n-1) + 1C + T(n-1) = 2T(n-1) + 1C
// Resolvendo: T(n) = (2^n - 1)C
void Hanoi(char origem, char destino, char auxiliar, int n) {
  // Se n for 1, ou seja, chegou no último disco, por isso, podemos mover agora a peça,
  // mova da origem ao destino
  if (n == 1) {
    printf("Move de %c para %c\n", origem, destino);
    return;
  }

  // Move todos os discos (menos o mais de baixo) da origem para o auxiliar (A até C)
  Hanoi(origem, auxiliar, destino, n - 1);

  // Move o disco mais de baixo da origem para o destino (A até B)
  // Como esse algoritmo sempre deixa uma única peça na origem nesse momento, podemos apenas mover ele
  printf("Move de %c para %c\n", origem, destino);

  // Move todos os discos que ficaram reservados no auxiliar para o destino (C até B)
  Hanoi(auxiliar, destino, origem, n - 1);
}

int main(void) {
  srand(time(NULL));
  clock_t inicioTempo, fimTempo;
  double tempoGasto;
  int discos;

  printf("Digite a quantidade de discos para mover de A para B:\n");
  scanf("%d", &discos);

  inicioTempo = clock();
  
  Hanoi('A', 'B', 'C', discos);

  fimTempo = clock();

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("Tempo de execucao para resolver as Torres de Hanoi: %.6f segundos\n", tempoGasto);

  return 0;
}
