// Bibliotecas necessárias
#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Essa estrutura representa um território com nome, cor do exército e número de tropas
typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército que ocupa o território
    int tropas;      // Quantidade de tropas alocadas
} Territorio;

int main() {
    // Declaração de um vetor de 5 estruturas do tipo Territorio
    Territorio territorios[5];

    // Laço para entrada dos dados dos 5 territórios
    for (int i = 0; i < 5; i++) {
        printf("\nCadastro do %dº território:\n", i + 1);

        // Solicita o nome do território
        printf("Digite o nome do território: ");
        scanf(" %[^\n]", territorios[i].nome); // Lê até a quebra de linha (permite nomes com espaços)

        // Solicita a cor do exército
        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", territorios[i].cor); // Lê até a quebra de linha (permite cores com espaços)

        // Solicita o número de tropas
        printf("Digite a quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);
    }

    // Exibição dos dados após o cadastro
    printf("\n===== DADOS DOS TERRITÓRIOS CADASTRADOS =====\n");
    for (int i = 0; i < 5; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", territorios[i].nome);
        printf("Cor do exército: %s\n", territorios[i].cor);
        printf("Quantidade de tropas: %d\n", territorios[i].tropas);
    }

    return 0; // Fim do programa
}
