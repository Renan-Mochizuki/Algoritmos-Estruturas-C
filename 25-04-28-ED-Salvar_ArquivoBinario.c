#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função que salva um arquivo texto com o nome e conteúdo especificados
// Se o arquivo já existir ele será sobrescrito
void SalvarArquivo(char *nomeArquivo, char *conteudo, int tamanhoConteudo) {
  FILE *arquivo = fopen(nomeArquivo, "w");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  fwrite(conteudo, 1, tamanhoConteudo, arquivo);

  fclose(arquivo);
  printf("\nArquivo '%s' salvo com sucesso!\n", nomeArquivo);
}

// Função que adiciona conteúdo a um arquivo texto existente
// Se o arquivo não existir, ele será criado
void AdicionarConteudoEmArquivo(char *nomeArquivo, char *conteudo, int tamanhoConteudo) {
  FILE *arquivo = fopen(nomeArquivo, "a");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  char conteudoComEspaco[257] = " ";
  strcat(conteudoComEspaco, conteudo);

  fwrite(conteudoComEspaco, 1, tamanhoConteudo + 1, arquivo);

  fclose(arquivo);
  printf("\nConteudo adicionado ao arquivo '%s' com sucesso!\n", nomeArquivo);
}

// Função que exibe o conteúdo de um arquivo texto
void ExibirConteudoArquivo(char *nomeArquivo) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    perror("Erro ao abrir o arquivo");
    return;
  }

  char caractere;

  printf("\nConteudo do arquivo '%s':\n", nomeArquivo);
  while (caractere = fgetc(arquivo), caractere != EOF) {
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
      printf("Digite o nome do arquivo a ser salvo: (max de 63 caracteres)\n");
      scanf(" %63[^\n]", nomeArquivo);
      printf("Digite o conteudo do arquivo: (max de 255 caracteres)\n");
      scanf(" %255[^\n]", conteudo);

      strcat(caminhoArquivo, nomeArquivo);
      strcat(caminhoArquivo, ".txt");
      SalvarArquivo(caminhoArquivo, conteudo, strlen(conteudo));
      break;

    case 2:
      printf("Digite o nome do arquivo a ser salvo: (max de 63 caracteres)\n");
      scanf(" %63[^\n]", nomeArquivo);
      printf("Digite o conteudo do arquivo: (max de 255 caracteres)\n");
      scanf(" %255[^\n]", conteudo);

      strcat(caminhoArquivo, nomeArquivo);
      strcat(caminhoArquivo, ".txt");
      AdicionarConteudoEmArquivo(caminhoArquivo, conteudo, strlen(conteudo));
      break;

    case 3:
      printf("Digite o nome do arquivo para exibir seu conteudo:\n");
      scanf(" %63[^\n]", nomeArquivo);

      strcat(caminhoArquivo, nomeArquivo);
      strcat(caminhoArquivo, ".txt");
      ExibirConteudoArquivo(caminhoArquivo);
      break;
    }
  }

  return 0;
}