#include <stdio.h>
#include <stdlib.h>

// Tempo de complexidade assintótica O(2^n)
// n representa a quantidade de discos sendo considerados
void hanoi(char origem, char destino, char auxiliar, int n) {
  // Se n for 1, ou seja, chegou no último disco, por isso, podemos mover agora a peça,
  // mova da origem ao destino
  if (n == 1) {
    printf("Move de %c para %c\n", origem, destino);
    return;
  }

  // Move todos os discos (menos o mais de baixo) da origem para o auxiliar (A até C)
  hanoi(origem, auxiliar, destino, n - 1);

  // Move o disco mais de baixo da origem para o destino (A até B)
  // Como esse algoritmo sempre deixa uma única peça na origem nesse momento, podemos apenas mover ele
  printf("Move de %c para %c\n", origem, destino);

  // Move todos os discos que ficaram reservados no auxiliar para o destino (C até B)
  hanoi(auxiliar, destino, origem, n - 1);
}

int main(void) {
  hanoi('A', 'B', 'C', 4);

  return 0;
}
