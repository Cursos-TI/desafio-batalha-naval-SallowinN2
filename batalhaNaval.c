#include <stdio.h>

#define TAM_TAB 10
#define TAM_HAB 5   // tamanho das matrizes de habilidade (5x5)
#define TAM_NAVIO 3

// Função para criar a matriz do efeito "cone" (5x5)
// Cone apontando para baixo: a linha 0 é o topo (ponto único) e a área se expande para baixo
void cria_cone(int cone[TAM_HAB][TAM_HAB]) {
    for(int i=0; i<TAM_HAB; i++) {
        for(int j=0; j<TAM_HAB; j++) {
            // Condição para formar um cone: 
            // No topo (linha 0), apenas a coluna central é 1
            // Conforme avança nas linhas, mais colunas ao redor da central são 1
            int centro = TAM_HAB/2;
            if (i == 0) {
                cone[i][j] = (j == centro) ? 1 : 0;
            } else if (i == 1) {
                cone[i][j] = (j >= centro-1 && j <= centro+1) ? 1 : 0;
            } else if (i == 2) {
                cone[i][j] = (j >= centro-2 && j <= centro+2) ? 1 : 0;
            } else if (i == 3) {
                cone[i][j] = (j >= centro-2 && j <= centro+2) ? 1 : 0;
            } else { // i == 4
                cone[i][j] = (j >= centro-2 && j <= centro+2) ? 1 : 0;
            }
        }
    }
}

// Função para criar a matriz do efeito "cruz" (5x5)
// Cruz com ponto de origem no centro
void cria_cruz(int cruz[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB/2;
    for(int i=0; i<TAM_HAB; i++) {
        for(int j=0; j<TAM_HAB; j++) {
            // A cruz tem 1 na linha central e na coluna central
            if (i == centro || j == centro) {
                cruz[i][j] = 1;
            } else {
                cruz[i][j] = 0;
            }
        }
    }
}

// Função para criar a matriz do efeito "octaedro" (5x5)
// Octaedro visto frontalmente, forma losango, ponto central marcado
void cria_octaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB/2;
    for(int i=0; i<TAM_HAB; i++) {
        for(int j=0; j<TAM_HAB; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            // Valores menores ou iguais a 2 formam o losango (octaedro)
            octaedro[i][j] = (dist <= 2) ? 1 : 0;
        }
    }
}

// Função que sobrepõe a matriz da habilidade no tabuleiro
// tabuleiro: matriz do tabuleiro
// hab: matriz da habilidade (5x5)
// origem_linha e origem_coluna: posição central da habilidade no tabuleiro
void aplica_habilidade(int tabuleiro[TAM_TAB][TAM_TAB], int hab[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    int meio = TAM_HAB / 2;

    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                int linha_tab = origem_linha + (i - meio);
                int col_tab = origem_coluna + (j - meio);

                // Verifica se está dentro do tabuleiro
                if (linha_tab >= 0 && linha_tab < TAM_TAB && col_tab >= 0 && col_tab < TAM_TAB) {
                    // Se não for navio (3), marca área afetada como 5
                    if (tabuleiro[linha_tab][col_tab] == 0) {
                        tabuleiro[linha_tab][col_tab] = 5;
                    }
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB] = {0};

    // Posiciona alguns navios fixos para exemplo (horizontal e vertical)
    // Navio horizontal no topo
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[1][2 + i] = 3;
    }
    // Navio vertical na direita
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[4 + i][7] = 3;
    }

    // Cria matrizes para as habilidades
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octaedro[TAM_HAB][TAM_HAB];

    cria_cone(cone);
    cria_cruz(cruz);
    cria_octaedro(octaedro);

    // Define pontos de origem das habilidades no tabuleiro
    int origem_cone_l = 3, origem_cone_c = 4;
    int origem_cruz_l = 6, origem_cruz_c = 6;
    int origem_octaedro_l = 8, origem_octaedro_c = 2;

    // Aplica as habilidades no tabuleiro
    aplica_habilidade(tabuleiro, cone, origem_cone_l, origem_cone_c);
    aplica_habilidade(tabuleiro, cruz, origem_cruz_l, origem_cruz_c);
    aplica_habilidade(tabuleiro, octaedro, origem_octaedro_l, origem_octaedro_c);

    // Exibe o tabuleiro com formatação
    printf("Tabuleiro (0=água, 3=navio, 5=área de habilidade):\n");
    for (int i = 0; i < TAM_TAB; i++) {
        for (int j = 0; j < TAM_TAB; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}