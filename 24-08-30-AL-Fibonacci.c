#include <stdio.h>

// Tempo de complexidade O(2^n)
int Fibonacci(int numero) {
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
  int limite;
  printf("Digite o limite de numeros de Fibonacci que deseja imprimir:\n");
  scanf("%d", &limite);

  for (int i = 1; i < limite; i++) {
    printf("%d, ", Fibonacci(i));
  }
  return 0;
}