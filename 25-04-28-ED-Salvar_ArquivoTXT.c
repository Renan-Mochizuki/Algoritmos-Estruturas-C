#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que salva um arquivo texto com o nome e conteúdo especificados
// Se o arquivo já existir ele será sobrescrito
void SalvarArquivoTXT(char *nomeArquivo, char *conteudo) {
  FILE *arquivo = fopen(nomeArquivo, "w");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  fprintf(arquivo, "%s", conteudo);

  fclose(arquivo);
  printf("\nArquivo '%s' salvo com sucesso!\n", nomeArquivo);
}

// Função que adiciona conteúdo a um arquivo texto existente
// Se o arquivo não existir, ele será criado
void AdicionarConteudoEmArquivoTXT(char *nomeArquivo, char *conteudo) {
  FILE *arquivo = fopen(nomeArquivo, "a");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  char conteudoComEspaco[257] = " ";
  strcat(conteudoComEspaco, conteudo);

  fprintf(arquivo, "%s\n", conteudoComEspaco);

  fclose(arquivo);
  printf("\nConteudo adicionado ao arquivo '%s' com sucesso!\n", nomeArquivo);
}

// Função que exibe o conteúdo de um arquivo texto
void ExibirConteudoArquivoTXT(char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  char caractere;

  printf("\nConteudo do arquivo '%s':\n", nomeArquivo);
  while (fscanf(arquivo, "%c", &caractere) != EOF) {
    printf("%c", caractere);
  }

  // char linha[256];
  // while (fgets(linha, sizeof(linha), arquivo) != NULL) {
  //   printf("%s", linha);
  // }

  fclose(arquivo);
  printf("\n");
}

int main(void) {
  char nomeArquivo[64];
  char conteudo[256];
  char caminhoArquivo[76] = "../Arquivos/";

  int escolha = 1;

  while (escolha > 0 && escolha < 4) {
    printf("\nQual acao deseja realizar?\n");
    printf("1 - Salvar um arquivo .txt\n");
    printf("2 - Adicionar conteudo a um arquivo .txt\n");
    printf("3 - Exibir conteudo de um arquivo .txt\n");
    printf("4 - Sair\n");

    strcpy(caminhoArquivo, "../Arquivos/");

    scanf("%d", &escolha);
    printf("\n");

    switch (escolha) {
    case 1:
      printf("Digite o nome do arquivo a ser salvo em .txt: (max de 63 caracteres)\n");
      scanf(" %63[^\n]", nomeArquivo);
      printf("Digite o conteudo do arquivo .txt: (max de 255 caracteres)\n");
      scanf(" %255[^\n]", conteudo);

      strcat(caminhoArquivo, nomeArquivo);
      strcat(caminhoArquivo, ".txt");
      SalvarArquivoTXT(caminhoArquivo, conteudo);
      break;

    case 2:
      printf("Digite o nome do arquivo a ser salvo em .txt: (max de 63 caracteres)\n");
      scanf(" %63[^\n]", nomeArquivo);
      printf("Digite o conteudo do arquivo .txt: (max de 255 caracteres)\n");
      scanf(" %255[^\n]", conteudo);

      strcat(caminhoArquivo, nomeArquivo);
      strcat(caminhoArquivo, ".txt");
      AdicionarConteudoEmArquivoTXT(caminhoArquivo, conteudo);
      break;

    case 3:
      printf("Digite o nome do arquivo para exibir seu conteudo:\n");
      scanf(" %63[^\n]", nomeArquivo);

      strcat(caminhoArquivo, nomeArquivo);
      strcat(caminhoArquivo, ".txt");
      ExibirConteudoArquivoTXT(caminhoArquivo);
      break;
    }
  }

  return 0;
}