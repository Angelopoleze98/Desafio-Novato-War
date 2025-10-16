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

// Função para cadastrar os 5 territórios
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

// Função para exibir todos os territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n===== ESTADO ATUAL DOS TERRITÓRIOS =====\n");
    for (int i = 0; i < n; i++) {
        printf("ID [%d] | Nome: %s | Cor: %s | Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simula um ataque entre dois territórios
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

// Sorteia uma missão para o jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missão ao jogador no início
void exibirMissao(char* missao) {
    printf("\n>>> Sua missão: %s\n", missao);
}

// Verifica se a missão foi cumprida (exemplo simples)
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {
    // Exemplo de verificação:
    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho - 1; i++) {
            if (strcmp(mapa[i].cor, mapa[i+1].cor) == 0) {
                consecutivos++;
                if (consecutivos >= 2) return 1;
            } else {
                consecutivos = 0;
            }
        }
    } else if (strcmp(missao, "Eliminar todas as tropas da cor vermelha") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0) {
                return 0;
            }
        }
        return 1;
    }
    // Outras missões podem ser adicionadas com novas regras
    return 0;
}

// Libera memória alocada
void liberarMemoria(Territorio* mapa, char* missao1, char* missao2) {
    free(mapa);
    free(missao1);
    free(missao2);
}

// Função principal
int main() {
    srand(time(NULL));

    int numTerritorios = 5;
    Territorio* mapa = (Territorio*) calloc(numTerritorios, sizeof(Territorio));
    if (!mapa) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    // Vetor de missões possíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar 2 territórios com mais de 10 tropas",
        "Controlar o território chamado Fortaleza",
        "Ter tropas em todos os territórios"
    };
    int totalMissoes = 5;

    // Alocação e atribuição das missões dos 2 jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Cadastro inicial
    cadastrar5Territorios(mapa);

    // Exibe missão apenas uma vez
    printf("\n=== Missão do Jogador 1 ===\n");
    exibirMissao(missaoJogador1);
    printf("\n=== Missão do Jogador 2 ===\n");
    exibirMissao(missaoJogador2);

    int turno = 1;
    int opcao;
    do {
        printf("\n======= TURNO %d =======\n", turno);
        exibirTerritorios(mapa, numTerritorios);

        printf("\n--- MENU ---\n");
        printf("1 - Realizar ataque\n");
        printf("0 - Sair do jogo\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idAtacante, idDefensor;

            printf("Informe o ID do território atacante: ");
            scanf("%d", &idAtacante);
            printf("Informe o ID do território defensor: ");
            scanf("%d", &idDefensor);

            if (idAtacante < 0 || idAtacante >= numTerritorios ||
                idDefensor < 0 || idDefensor >= numTerritorios) {
                printf("IDs inválidos!\n");
            } else {
                atacar(&mapa[idAtacante], &mapa[idDefensor]);

                // Verifica se algum jogador venceu após o ataque
                if (verificarMissao(missaoJogador1, mapa, numTerritorios)) {
                    printf("\n*** Jogador 1 VENCEU! Missão cumprida! ***\n");
                    break;
                }
                if (verificarMissao(missaoJogador2, mapa, numTerritorios)) {
                    printf("\n*** Jogador 2 VENCEU! Missão cumprida! ***\n");
                    break;
                }
            }
            turno++;
        }

    } while (opcao != 0);

    liberarMemoria(mapa, missaoJogador1, missaoJogador2);
    printf("\nMemória liberada. Programa encerrado.\n");

    return 0;
}
