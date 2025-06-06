#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função que retorna o número de Fibonacci passando um indice
// Complexidade: O(2^n)
// Caso base: T(1) = 1C
// T(n) = T(n-1) + T(n-2) + 1C
long Fibonacci(long numero) {
  // Critério de parada
  // Os valores que realmente serão retornados é o 1, além do 0 para realizar a soma corretamente
  // Caso for digitado 0 ou um número negativo, já retorna esse número
  if (numero <= 1)
    return numero;

  // Como o valor de um dos quadrados de Fibonacci é igual a soma dos dois anteriores
  // Retornamos a soma do valor anterior e anterior do anterior
  return Fibonacci(numero - 1) + Fibonacci(numero - 2);
}

int main(void) {
  srand(time(NULL));
  clock_t inicioTempo, fimTempo;
  double tempoGasto;
  long limite;

  printf("Digite o limite de numeros de Fibonacci que deseja imprimir:\n");
  scanf("%ld", &limite);

  inicioTempo = clock();

  for (long i = 1; i < limite; i++) {
    printf("%ld, ", Fibonacci(i));
  }

  fimTempo = clock();

  tempoGasto = ((double)(fimTempo - inicioTempo)) / CLOCKS_PER_SEC;
  printf("\nTempo de execucao para todos calculos de Fibonacci: %.6f segundos\n", tempoGasto);

  return 0;
}