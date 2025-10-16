#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Função para cadastrar os 5 territórios com IDs
void cadastrar5Territorios(Territorio* mapa) {
    for (int i = 0; i < 5; i++) {
        printf("\n=== Cadastro do Território ID %d ===\n", i);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Função para exibir todos os territórios com ID
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== ESTADO ATUAL DOS TERRITÓRIOS =====\n");
    for (int i = 0; i < n; i++) {
        printf("ID [%d] | Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simulação de ataque
void atacar(Territorio* atacante, Territorio* defensor) {
    if (strcmp(atacante->cor, defensor->cor) == 0) {
        printf("\nErro: Você não pode atacar um território da mesma cor!\n");
        return;
    }

    if (atacante->tropas < 2) {
        printf("\nErro: Tropas insuficientes para atacar (mínimo 2 tropas).\n");
        return;
    }

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- Simulação de Batalha ---\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("Resultado: Atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;

        defensor->tropas = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;
    } else {
        printf("Resultado: Defensor venceu!\n");
        atacante->tropas -= 1;
    }
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

// Função principal
int main() {
    srand(time(NULL));  // Semente para aleatoriedade

    int numTerritorios = 5;

    // Alocação dinâmica de memória
    Territorio* mapa = (Territorio*) calloc(numTerritorios, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Cadastro inicial com IDs visíveis
    cadastrar5Territorios(mapa);

    int opcao;
    do {
        exibirTerritorios(mapa, numTerritorios);

        printf("\n--- MENU ---\n");
        printf("1 - Realizar ataque\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idAtacante, idDefensor;

            printf("Informe o ID do território atacante: ");
            scanf("%d", &idAtacante);

            printf("Informe o ID do território defensor: ");
            scanf("%d", &idDefensor);

            // Verifica se os IDs estão dentro do intervalo
            if (idAtacante < 0 || idAtacante >= numTerritorios ||
                idDefensor < 0 || idDefensor >= numTerritorios) {
                printf("\nIDs inválidos. Tente novamente.\n");
            } else {
                atacar(&mapa[idAtacante], &mapa[idDefensor]);
            }
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("\nMemória liberada. Programa encerrado.\n");

    return 0;
}
