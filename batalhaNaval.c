#include <stdio.h>

#define TAM_TAB 10       // Tamanho do tabuleiro 10x10
#define TAM_NAVIO 3      // Tamanho fixo dos navios

// Função que verifica se há sobreposição ao posicionar o navio
// tabuleiro: matriz do jogo
// linhas e colunas dos pontos do navio: arrays
// tamanho: tamanho do navio
// Retorna 1 se sobrepor, 0 caso contrário
int verifica_sobreposicao(int tabuleiro[TAM_TAB][TAM_TAB], int linhas[], int colunas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (tabuleiro[linhas[i]][colunas[i]] == 3) {
            return 1;  // Sobreposição detectada
        }
    }
    return 0;
}

// Função para posicionar navio no tabuleiro
// tabuleiro: matriz do jogo
// linhas e colunas dos pontos do navio: arrays
// tamanho: tamanho do navio
void posiciona_navio(int tabuleiro[TAM_TAB][TAM_TAB], int linhas[], int colunas[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linhas[i]][colunas[i]] = 3;
    }
}

int main() {
    int tabuleiro[TAM_TAB][TAM_TAB] = {0}; // Inicializa todo o tabuleiro com 0 (água)

    // Definindo navios:
    // 1) Navio horizontal
    int h_linha = 1, h_coluna = 2;
    int h_linhas[TAM_NAVIO], h_colunas[TAM_NAVIO];
    for (int i = 0; i < TAM_NAVIO; i++) {
        h_linhas[i] = h_linha;
        h_colunas[i] = h_coluna + i;
    }

    // 2) Navio vertical
    int v_linha = 4, v_coluna = 7;
    int v_linhas[TAM_NAVIO], v_colunas[TAM_NAVIO];
    for (int i = 0; i < TAM_NAVIO; i++) {
        v_linhas[i] = v_linha + i;
        v_colunas[i] = v_coluna;
    }

    // 3) Navio diagonal principal (linha e coluna aumentam juntos)
    int d1_linha = 5, d1_coluna = 1;
    int d1_linhas[TAM_NAVIO], d1_colunas[TAM_NAVIO];
    for (int i = 0; i < TAM_NAVIO; i++) {
        d1_linhas[i] = d1_linha + i;
        d1_colunas[i] = d1_coluna + i;
    }

    // 4) Navio diagonal anti (linha aumenta, coluna diminui)
    int d2_linha = 2, d2_coluna = 8;
    int d2_linhas[TAM_NAVIO], d2_colunas[TAM_NAVIO];
    for (int i = 0; i < TAM_NAVIO; i++) {
        d2_linhas[i] = d2_linha + i;
        d2_colunas[i] = d2_coluna - i;
    }

    // Validação dos limites de tabuleiro para cada navio
    int valid = 1;

    // Função lambda-like inline para validar limites (linha e coluna entre 0 e 9)
    #define valida_limites(linhas, colunas) ({ \
        int ok = 1; \
        for (int _i=0; _i < TAM_NAVIO; _i++) { \
            if (linhas[_i] < 0 || linhas[_i] >= TAM_TAB || colunas[_i] < 0 || colunas[_i] >= TAM_TAB) { \
                ok = 0; break; \
            } \
        } \
        ok; \
    })

    if (!valida_limites(h_linhas, h_colunas)) {
        printf("Navio horizontal fora dos limites!\n");
        valid = 0;
    }
    if (!valida_limites(v_linhas, v_colunas)) {
        printf("Navio vertical fora dos limites!\n");
        valid = 0;
    }
    if (!valida_limites(d1_linhas, d1_colunas)) {
        printf("Navio diagonal principal fora dos limites!\n");
        valid = 0;
    }
    if (!valida_limites(d2_linhas, d2_colunas)) {
        printf("Navio diagonal anti fora dos limites!\n");
        valid = 0;
    }

    if (!valid) return 1; // Para o programa se algum navio está fora do tabuleiro

    // Verificar sobreposição entre todos os navios, posicionando um por um e checando antes
    // Como não vamos posicionar diretamente, verificamos possíveis sobreposições

    // Verificar sobreposição dos 4 navios entre si
    // Simples: checar cada navio contra os já "confirmados" no tabuleiro (inicialmente vazio)
    
    // Posicionar navio horizontal (não há nada no tabuleiro ainda)
    if (verifica_sobreposicao(tabuleiro, h_linhas, h_colunas, TAM_NAVIO)) {
        printf("Sobreposição detectada no navio horizontal\n");
        return 1;
    }
    posiciona_navio(tabuleiro, h_linhas, h_colunas, TAM_NAVIO);

    // Verificar navio vertical
    if (verifica_sobreposicao(tabuleiro, v_linhas, v_colunas, TAM_NAVIO)) {
        printf("Sobreposição detectada no navio vertical\n");
        return 1;
    }
    posiciona_navio(tabuleiro, v_linhas, v_colunas, TAM_NAVIO);

    // Navio diagonal principal
    if (verifica_sobreposicao(tabuleiro, d1_linhas, d1_colunas, TAM_NAVIO)) {
        printf("Sobreposição detectada no navio diagonal principal\n");
        return 1;
    }
    posiciona_navio(tabuleiro, d1_linhas, d1_colunas, TAM_NAVIO);

    // Navio diagonal anti
    if (verifica_sobreposicao(tabuleiro, d2_linhas, d2_colunas, TAM_NAVIO)) {
        printf("Sobreposição detectada no navio diagonal anti\n");
        return 1;
    }
    posiciona_navio(tabuleiro, d2_linhas, d2_colunas, TAM_NAVIO);

    // Exibir o tabuleiro com espaçamento para melhor visualização
    printf("Tabuleiro 10x10 (0 = água, 3 = navio):\n");
    for (int linha = 0; linha < TAM_TAB; linha++) {
        for (int coluna = 0; coluna < TAM_TAB; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }

    return 0;
}