#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura do Nó da Fila
typedef struct no {
    int id;
    char nome[50];
    struct no *prox;
} No;

typedef No* NoPtr;

// Estrutura do Cabeçalho da Fila
typedef struct {
    NoPtr ini;
    NoPtr fim;
} Cabecalho;

typedef Cabecalho* Fila;

// 1. Criação da Fila Dinâmica
Fila Criar() {
    Fila f = (Fila) malloc(sizeof(Cabecalho));
    if (f != NULL) {
        f->ini = NULL;
        f->fim = NULL;
    }
    return f;
}

// 2. Verificação de Fila Vazia (Função Auxiliar)
int vazia(Fila f) {
    if (f == NULL || f->ini == NULL) {
        return 1; // Retorna 1 se estiver vazia ou nula
    }
    return 0; // Retorna 0 se possuir elementos
}

// 3. Inserir Paciente na Fila (Enqueue)
int inserir(Fila f, int id, const char *nome) {
    if (f == NULL) return 0;
    
    NoPtr novo = (NoPtr) malloc(sizeof(No));
    if (novo == NULL) return 0;

    novo->id = id;
    strncpy(novo->nome, nome, sizeof(novo->nome) - 1);
    novo->nome[sizeof(novo->nome) - 1] = '\0';
    novo->prox = NULL;

    if (vazia(f)) {
        f->ini = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
    return 1;
}

// 4. Atendimento do Paciente (Remover / Desenfileirar / Dequeue)
int atenderPaciente(Fila f) {
    if (vazia(f)) {
        printf("\n[AVISO] Nao ha pacientes na fila para atendimento.\n");
        return 0;
    }

    NoPtr aux = f->ini;
    printf("\n>>> ATENDENDO PACIENTE <<<\n");
    printf("ID: %d | Nome: %s\n", aux->id, aux->nome);
    printf("---------------------------\n");

    f->ini = f->ini->prox;
    
    // Se a fila ficou vazia após remover o elemento
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(aux); // Libera a memória alocada para o nó removido
    return 1;
}

// 5. Consulta do Próximo Paciente (Primeiro / Peek)
void proximoPaciente(Fila f) {
    if (vazia(f)) {
        printf("\n[AVISO] A fila esta vazia.\n");
        return;
    }
    printf("\n=== PROXIMO PACIENTE A SER ATENDIDO ===\n");
    printf("ID: %d | Nome: %s\n", f->ini->id, f->ini->nome);
    printf("=======================================\n");
}

// 6. Tamanho da Fila (Contagem)
int tamanhoFila(Fila f) {
    if (vazia(f)) return 0;

    int cont = 0;
    NoPtr atual = f->ini;
    while (atual != NULL) {
        cont++;
        atual = atual->prox;
    }
    return cont;
}

// 7. Listar Fila de Pacientes
void listarFila(Fila f) {
    if (vazia(f)) {
        printf("\n[AVISO] A fila esta vazia.\n");
        return;
    }

    NoPtr atual = f->ini;
    printf("\n=== FILA DE PACIENTES (%d aguardando) ===\n", tamanhoFila(f));
    while (atual != NULL) {
        printf("ID: %d | Nome: %s\n", atual->id, atual->nome);
        atual = atual->prox;
    }
    printf("=======================================\n");
}

// 8. Esvaziar / Desalocar Toda a Fila
void destruirFila(Fila f) {
    if (f == NULL) return;

    NoPtr atual = f->ini;
    while (atual != NULL) {
        NoPtr temp = atual;
        atual = atual->prox;
        free(temp); // Libera cada nó de paciente
    }

    free(f); // Libera o cabeçalho da fila
}

// --- MAIN COM MENU INTERATIVO EXPANDIDO ---
int main() {
    Fila filaAtendimento = Criar();
    int opcao, id;
    char nome[50];

    do {
        printf("\n--- SISTEMA HOSPITALAR (FATEC IPIRANGA) ---\n");
        printf("1. Chegada de Paciente (Inserir na Fila)\n");
        printf("2. Atender Paciente (Remover da Fila)\n");
        printf("3. Consultar Proximo Paciente (Inicio)\n");
        printf("4. Listar Fila de Pacientes\n");
        printf("5. Exibir Quantidade de Pacientes na Fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            opcao = -1;
            while(getchar() != '\n'); // Limpa buffer de entrada inválida
        }

        switch (opcao) {
            case 1:
                printf("Informe o ID do paciente: ");
                scanf("%d", &id);
                getchar(); // Limpar buffer do teclado
                printf("Informe o Nome do paciente: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = 0; // Remover quebra de linha

                if (inserir(filaAtendimento, id, nome)) {
                    printf(">> Paciente inserido com sucesso!\n");
                } else {
                    printf(">> Erro ao inserir paciente.\n");
                }
                break;

            case 2:
                atenderPaciente(filaAtendimento);
                break;

            case 3:
                proximoPaciente(filaAtendimento);
                break;

            case 4:
                listarFila(filaAtendimento);
                break;

            case 5:
                printf("\nTotal de pacientes aguardando: %d\n", tamanhoFila(filaAtendimento));
                break;

            case 0:
                printf("\nDesalocando memoria e encerrando o sistema...\n");
                destruirFila(filaAtendimento);
                printf("Sistema encerrado com sucesso.\n");
                break;

            default:
                printf("\nOpcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}