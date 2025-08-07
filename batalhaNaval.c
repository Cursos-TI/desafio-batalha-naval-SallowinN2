#include <stdio.h>

#define TAM_TAB 10       // Tamanho do tabuleiro (10x10)
#define TAM_NAVIO 3      // Tamanho fixo dos navios

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB] = {0};  // Inicializa tabuleiro com 0 (água)
    
    // Coordenadas iniciais dos navios (definidas diretamente)
    // Navio horizontal: linha 2, coluna 4 (exemplo)
    int nav_h_linha = 2;
    int nav_h_coluna = 4;

    // Navio vertical: linha 5, coluna 7 (exemplo)
    int nav_v_linha = 5;
    int nav_v_coluna = 7;

    // Função simples para verificar se navio horizontal cabe no tabuleiro
    if (nav_h_coluna < 0 || nav_h_coluna + TAM_NAVIO > TAM_TAB || nav_h_linha < 0 || nav_h_linha >= TAM_TAB) {
        printf("Navio horizontal fora dos limites do tabuleiro!\n");
        return 1;
    }

    // Função simples para verificar se navio vertical cabe no tabuleiro
    if (nav_v_linha < 0 || nav_v_linha + TAM_NAVIO > TAM_TAB || nav_v_coluna < 0 || nav_v_coluna >= TAM_TAB) {
        printf("Navio vertical fora dos limites do tabuleiro!\n");
        return 1;
    }

    // Verificar sobreposição (simplificada)
    // Checa se alguma posição do navio vertical coincide com o navio horizontal
    int sobreposicao = 0;
    for (int i = 0; i < TAM_NAVIO; i++) {
        int h_l = nav_h_linha;
        int h_c = nav_h_coluna + i;

        int v_l = nav_v_linha + i;
        int v_c = nav_v_coluna;

        // Checar todas as posições do navio horizontal contra vertical
        // Como o tamanho é fixo e navios são ortogonais, basta verificar intersecção simples
        for (int j = 0; j < TAM_NAVIO; j++) {
            if ( (v_l == h_l) && (v_c == (nav_h_coluna + j)) ) {
                sobreposicao = 1;
                break;
            }
            if ( (v_l == (nav_v_linha + j)) && (v_c == h_c) ) {
                sobreposicao = 1;
                break;
            }
        }
        if (sobreposicao) break;
    }

    if (sobreposicao) {
        printf("Navios estão sobrepostos! Posicione-os em locais diferentes.\n");
        return 1;
    }

    // Posicionar navio horizontal no tabuleiro
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[nav_h_linha][nav_h_coluna + i] = 3;
    }

    // Posicionar navio vertical no tabuleiro
    for (int i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[nav_v_linha + i][nav_v_coluna] = 3;
    }

    // Exibir o tabuleiro
    printf("Tabuleiro 10x10 (0 = água, 3 = navio):\n");
    for (int linha = 0; linha < TAM_TAB; linha++) {
        for (int coluna = 0; coluna < TAM_TAB; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}