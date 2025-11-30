#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_FILA 5

// Struct que representa uma peça do Tetris Stack
typedef struct {
    char nome; // Tipo da peça: I, O, T, L
    int id;    // Identificador único da peça
} Peca;

// Fila circular de peças
typedef struct {
    Peca fila[TAMANHO_FILA];
    int inicio; // Posição da primeira peça
    int fim;    // Posição onde a próxima peça será inserida
    int quantidade; // Quantidade atual de peças na fila
} FilaPecas;

// Gera aleatoriamente uma peça do tipo I, O, T ou L
Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.nome = tipos[rand() % 4];
    nova.id = id;
    return nova;
}

// Inicializa a fila com algumas peças
void inicializarFila(FilaPecas *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;

    for (int i = 0; i < TAMANHO_FILA; i++) {
        Peca p = gerarPeca(i);
        f->fila[f->fim] = p;
        f->fim = (f->fim + 1) % TAMANHO_FILA;
        f->quantidade++;
    }
}

// Verifica se a fila está cheia
int filaCheia(FilaPecas *f) {
    return f->quantidade == TAMANHO_FILA;
}

// Verifica se a fila está vazia
int filaVazia(FilaPecas *f) {
    return f->quantidade == 0;
}

// Remove a peça da frente da fila (dequeue)
void jogarPeca(FilaPecas *f) {
    if (filaVazia(f)) {
        printf("\nA fila está vazia! Nao ha peca para jogar.\n");
        return;
    }

    Peca removida = f->fila[f->inicio];
    printf("\nPeca jogada: [%c %d]\n", removida.nome, removida.id);

    f->inicio = (f->inicio + 1) % TAMANHO_FILA;
    f->quantidade--;
}

// Insere nova peça no final da fila (enqueue)
void inserirPeca(FilaPecas *f, int *idAtual) {
    if (filaCheia(f)) {
        printf("\nA fila está cheia! Nao e possivel adicionar nova peça.\n");
        return;
    }

    Peca nova = gerarPeca((*idAtual)++);

    f->fila[f->fim] = nova;
    f->fim = (f->fim + 1) % TAMANHO_FILA;
    f->quantidade++;

    printf("\nPeca adicionada: [%c %d]\n", nova.nome, nova.id);
}

// Exibe todas as peças da fila
void exibirFila(FilaPecas *f) {
    printf("\n=== Fila de Peças ===\n");

    if (filaVazia(f)) {
        printf("(vazia)\n");
        return;
    }

    int index = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        Peca p = f->fila[index];
        printf("[%c %d] ", p.nome, p.id);
        index = (index + 1) % TAMANHO_FILA;
    }

    printf("\n====================\n");
}

int main() {
    srand(time(NULL));

    FilaPecas fila;
    int idAtual = 5; // Como iniciamos com 5 peças, o próximo ID é 5

    inicializarFila(&fila);

    int opcao;

    do {
        exibirFila(&fila);

        printf("\nOpcoes:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                jogarPeca(&fila);
                break;
            case 2:
                inserirPeca(&fila, &idAtual);
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}
