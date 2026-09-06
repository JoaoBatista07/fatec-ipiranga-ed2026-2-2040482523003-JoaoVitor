#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VALOR_PREMIUM 100.0

/* - - - - - - - - -- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - - - -*
 * Disciplina : Estrutura de Dados *
 * Prof . Verissimo *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -*
 * Objetivo do Programa : O Objetivo é gerenciar o atendimento do lava-rápido usando recursividade *
 * Data - 06/09/2026 *
 * Autor : João Vitor Bispo Batista *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -- - - -*/

typedef struct {
    char placa[8];
    float valor;
} Veiculo;

// Cabeçalho
void exibirCabecalho(void) {
    printf("=================================\n");
    printf("LAVA - RAPIDO BRILHO TOTAL - FILA DE ATENDIMENTO\n");
    printf("=================================\n");
}

// Preenchimento
void preencherFrota(Veiculo *frota, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("Placa do veiculo %d: ", i + 1);
        scanf("%s", (frota + i)->placa);

        printf("Valor do servico (R$): ");
        scanf("%f", &(frota + i)->valor);
    }
}

// Exibição recursiva
void exibirFrotaRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) return; // caso base

    printf("%d) Placa : %s | Valor : R$ %.2f\n",indice + 1, frota[indice].placa, frota[indice].valor);

    exibirFrotaRecursivo(frota, indice + 1, quantidade);
}

// Soma recursiva
float calcularValorTotalRecursivo(Veiculo *frota, int indice, int quantidade) {
    // Caso base
    if (indice == quantidade) return 0.0f;

    return frota[indice].valor +
           calcularValorTotalRecursivo(frota, indice + 1, quantidade);
}

// Busca recursiva
int buscarVeiculoRecursivo(Veiculo *frota, int indice, int quantidade, char placa[8]) {
    if (indice == quantidade) return -1; // caso base 1

    if (strcmp(frota[indice].placa, placa) == 0)
        return indice; // caso base 2

    return buscarVeiculoRecursivo(frota, indice + 1, quantidade, placa);    
}

// Contagem recursiva
int contarPremiumRecursivo(Veiculo *frota, int indice, int quantidade) {
    if (indice == quantidade) return 0;

    int soma=0; 
    if(frota[indice].valor >= VALOR_PREMIUM){
        soma = 1;
    }
    else{
        soma = 0;
    }

    return soma + contarPremiumRecursivo(frota, indice + 1, quantidade);
}

int main() {
    int quantidade;
    char placaBusca[8];

    exibirCabecalho();

    printf("Quantos veiculos serao atendidos hoje? ");
    scanf("%d", &quantidade);

    // Alocação dinâmica
    Veiculo *frota = (Veiculo *) malloc(quantidade * sizeof(Veiculo));

    if (frota == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    preencherFrota(frota, quantidade);

    printf("\n");
    printf("--- Veiculos atendidos hoje ---\n");
    exibirFrotaRecursivo(frota, 0, quantidade);
    printf("\n");

    printf("--- Busca recursiva por placa ---\n");
    printf("Placa a ser pesquisada: ");
    scanf("%s", placaBusca);

    int pos = buscarVeiculoRecursivo(frota, 0, quantidade, placaBusca);

    if (pos == -1) {
        printf("Veiculo nao encontrado na frota.\n");
    } else {
        printf("Veiculo encontrado na posicao %d! Placa : %s | Valor : R$ %.2f\n",pos + 1, frota[pos].placa, frota[pos].valor);
    }
    printf("\n");

    printf("--- Resumo do dia ---\n");
    printf("Total de veiculos atendidos : %d\n", quantidade);

    int premium = contarPremiumRecursivo(frota, 0, quantidade);
    printf("Servicos premium ( >= R$ 100.00) : %d\n", premium);

    float total = calcularValorTotalRecursivo(frota, 0, quantidade);
    printf("Valor total arrecadado : R$ %.2f\n", total);

    free(frota);
    frota = NULL;

    printf("\n");
    printf("Memoria da frota liberada com sucesso. Sistema encerrado.\n");

    return 0;
}