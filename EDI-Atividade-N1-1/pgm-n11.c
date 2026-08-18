#include <stdio.h>

void aplicarBonus(float *nota, float bonus) {
	*nota += bonus;
}

void simularAjuste(float notaOriginal, float bonus) {
	printf("--- Simulação do ajuste (passagem por valor) ---\n");
	printf("Simulação para o aluno 1: %.2f + %.2f = %.2f (não aplicado ainda)\n", notaOriginal, bonus, notaOriginal+bonus);

}

float calcularMedia(float vetor[], int tamanho) {
    // usa um laço for para somar todos os valores do vetor e dividir pelo tamanho. 
    //O vetor é passado por referência de forma automática porque o nome do vetor 
    //aponta para um ponteiro para o primeiro elemento.
	float soma;
	for (int i=0; i<tamanho; i++) {
		soma += vetor[i];
	}
	return (float) soma / tamanho;
}

void exibirCabecalho() {
	printf("=================================\n");
	printf(" SISTEMA DE NOTAS - TURMA ADS\n");
	printf("=================================\n");
}

#define TAMANHO_TURMA 5

int main()
{
	float bonus=0;
	float notas[TAMANHO_TURMA];

	exibirCabecalho();
	for (int i=0; i<TAMANHO_TURMA; i++) {
		printf("Nota do aluno %d: ", i+1);
		scanf("%f", &notas[i]);

	}

	printf("Informe o valor do bônus a aplicar: ");
	scanf("%f", &bonus);
	printf("\n");

	printf("--- Media da turma antes do ajuste ---\n");
	printf("Media inicial: %.2f\n", calcularMedia(notas, TAMANHO_TURMA));
	printf("\n");

	simularAjuste(notas[0], bonus);
	printf("Nota do aluno 1 após simulação (inalterada): %.2f\n", notas[0]);

	printf("\n");

	printf("--- Aplicacao real do bonus (passagem por referencia) ---\n");
	for (int i=0; i<TAMANHO_TURMA; i++) {
		aplicarBonus(&notas[i], bonus);
	}
	printf("Bonus de 0.50 aplicado a todas as notas da turma.\n");

	printf("\n");

	printf("--- Notas finais da turma ---\n");
	for (int i=0; i<TAMANHO_TURMA; i++) {
		printf("Aluno %d: %.2f\n", i+1, notas[i]);
	}

	printf("\n");

	printf("--- Media da turma após o reajuste ---\n");
	printf("Media final: %.2f", calcularMedia(notas, TAMANHO_TURMA));

	return 0;
}