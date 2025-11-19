#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// Desafio Tetris Stack
// Tema 3 - Integração de Fila e Pilha
// Este código inicial serve como base para o desenvolvimento do sistema de controle de peças.
// Use as instruções de cada nível para desenvolver o desafio.


    // 🧩 Nível Novato: Fila de Peças Futuras
    //
    // - Crie uma struct Peca com os campos: tipo (char) e id (int).
    // - Implemente uma fila circular com capacidade para 5 peças.
    // - Crie funções como inicializarFila(), enqueue(), dequeue(), filaCheia(), filaVazia().
    // - Cada peça deve ser gerada automaticamente com um tipo aleatório e id sequencial.
    // - Exiba a fila após cada ação com uma função mostrarFila().
    // - Use um menu com opções como:
    //      1 - Jogar peça (remover da frente)
    //      0 - Sair
    // - A cada remoção, insira uma nova peça ao final da fila.

// definição do tamanho máximo da fila
#define MAX 5

// Criação da estrutura Peca com o tipo e id de cada peça
typedef struct {
    char tipo[2];
    int id;
} Peca;

// Criação da struct fila com seus indices inicio e fim, e o total de elementos
typedef struct {
    Peca itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Função que inicializa a fila com zero os indices e o total
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total= 0;
}

// Função que verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

// Função que verifica se a fila está VAZIA
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Função de inserir (enqueue)
void inserirFila(Fila *f, Peca itens[]) {
    if (filaCheia(f)) {
        return;
    }
    int e = rand() % MAX; // escolhe a peça aleatoriamente
    f->itens[f->fim] = itens[e]; // insere o elemento no final
    f->fim = (f->fim + 1) % MAX;    // atualiza circulamente o indice
    f->total++; // Incrementa  contagem de elementos
}

// Função de remover um item (dequeue)
void removerFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila Vazio");
        return; // Evita a remoção se estiver vazia
    }
    f->inicio = (f->inicio + 1) % MAX;    // atualiza circulamente o indice inicio
    f->total--; // Decrementa  contagem de elementos
}

// Função mostrar a fila 
void mostrarFila (Fila *f) {
    printf("Fila: ");
    for (int i = 0, idx = f->inicio ; i < f->total; i++,idx = (idx + 1) % MAX) {
        printf("[ %s , %d] ",f->itens[idx].tipo,f->itens[idx].id);
    }
    printf("\n");
}

int main() {

    // Inicializa a semente
    srand(time(NULL));

    Fila f;

    inicializarFila(&f); // Inicializar fila
    
    Peca itens[]= {
        {"I",0},
        {"L",1},
        {"I",2},
        {"O",3},
        {"T",4}
    };
    
    // Preenche a fila inicial
    for (int i = 0; i < MAX; i++) {
        inserirFila(&f, itens);
    }
    mostrarFila (&f);

    int opcao;
    do {
        printf("\n1. Jogar peça (dequeue)\n");
        printf("0. Sair\n");
        printf("Escolha uma das opções: ");
        scanf("%d",&opcao);

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                removerFila(&f);
                inserirFila(&f, itens); // insere nova peça
                mostrarFila(&f);
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}


// 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha


