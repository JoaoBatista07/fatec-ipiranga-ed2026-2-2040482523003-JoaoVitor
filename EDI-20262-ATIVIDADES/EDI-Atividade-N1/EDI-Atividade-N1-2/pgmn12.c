#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ESTOQUE 5
#define ESTOQUE_MINIMO 10

int estoque[TAMANHO_ESTOQUE];

void exibirCabecalho(void) {
    printf("=================================\n");
    printf("SISTEMA DE ESTOQUE- LOJA CONSTRUMAIS\n");
    printf("=================================\n");
}

void preencherEstoque(void) {
    int *p = estoque;
    int valor;
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Quantidade do produto %d: ", i + 1);
        scanf("%d", &valor);
        *(p + i) = valor; 
    }
}

float calcularMediaEstoque(void) {
    int *p = estoque;
    float soma = 0;
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {

        soma += *(p + i); /* o (p+i) significa o endereço de memória
        e o *(p+i) pega o valor dentro da memória*/
    }
    
    return soma / TAMANHO_ESTOQUE;
}

void exibirEstoque(int momento) {
    int *p = estoque;
    
    if (momento == 0) {
        printf("-- Estoque atual (antes da reposicao) --\n");
    } else if (momento == 1) {
        printf("-- Estoque final (apos reposicao) --\n");
    }
    else{
        printf("Número inválido");
    }

    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        printf("Produto %d: %d unidades\n", i + 1, *(p + i));
    }
}


void simularReposicao(int quantidadeAtual, int reposicao) {
    int simulacao = quantidadeAtual + reposicao;
    printf("-- Simulacao de reposicao (passagem por valor) --\n");
    printf("Simulacao para o produto 1: %d + %d = %d (nao aplicado ainda)\n", 
           quantidadeAtual, reposicao, simulacao);
}

void aplicarReposicaoGeral(int reposicao) {
    int *p = estoque;
    
    printf("-- Aplicacao real da reposicao (ponteiro interno ao vetor global) --\n");
    printf("Reposicao de %d unidades aplicada a todos os produtos do estoque.\n", reposicao);
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        *(p + i) += reposicao; 
    }
}

void identificarEstoqueCritico(int minimo) {
    int *p = estoque;
    int contadorCriticos = 0;
    
    printf("-- Analise de estoque critico (minimo = %d unidades) --\n", minimo);
    
    for (int i = 0; i < TAMANHO_ESTOQUE; i++) {
        if (*(p + i) < minimo) {
            printf("Produto %d esta em nivel critico: %d unidades (abaixo do minimo)\n", i + 1, *(p + i));
            contadorCriticos++;
        }
    }
    
    if (contadorCriticos == 0) {
        printf("Estoque regularizado. Nenhum produto em estado critico.\n");
    }
}

int main() {
    int loteReposicao;
    
    exibirCabecalho();
    preencherEstoque();
    
    printf("Quantidade de reposicao a aplicar: ");
    scanf("%d", &loteReposicao);
    printf("\n"); 
    exibirEstoque(0);
    printf("\n");
    simularReposicao(estoque[0], loteReposicao);
    printf("Quantidade do produto 1 apos a simulacao (inalterada): %d\n", estoque[0]); 
    printf("\n");
    aplicarReposicaoGeral(loteReposicao);
    
    printf("\n");
    exibirEstoque(1);
    printf("\n");
    printf("-- Media geral do estoque --\n");
    printf("Media final: %.2f unidades\n", calcularMediaEstoque());
    
    printf("\n");
    identificarEstoqueCritico(ESTOQUE_MINIMO);
    
    return 0;
}