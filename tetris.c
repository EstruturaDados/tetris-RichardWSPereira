#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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

// definição do tamanho máximo da fila
#define MAX_Fila 5
#define MAX_Pilha 3

// Criação da estrutura Peca com o tipo e id de cada peça
typedef struct {
    char tipo; // tipo da peça (ex: 'I', 'L', 'O', 'T')
    int id; // id sequencial
} Peca;

// Criação da struct fila com seus indices inicio e fim, e o total de elementos
typedef struct {
    Peca itens[MAX_Fila];
    int inicio; // índice do primeiro elemento
    int fim;    // índice do próximo espaço livre (após o último)
    int total;  // quantidade atual
} Fila;

// Função que inicializa a fila com zero os indices e o total
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total= 0;
}

// Função que verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == MAX_Fila;
}

// Função que verifica se a fila está VAZIA
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Função de inserir (enqueue)
int InserirPeca(Fila *f, Peca peca) {
    if (filaCheia(f)) {
        return 0; // Falha
    }
    f->itens[f->fim] = peca; // insere o elemento no final
    f->fim = (f->fim + 1) % MAX_Fila;    // atualiza circulamente o indice
    f->total++; // Incrementa  contagem de elementos
    return 1; // sucesso
}

// Função de remover um item (dequeue)
int removerFila(Fila *f, Peca *removida) {
    if (filaVazia(f)) {
        printf("Fila Vazio");
        return 0; // Evita a remoção se estiver vazia
    }
    if (removida) {
        *removida = f->itens[f->inicio];
    }
    f->inicio = (f->inicio + 1) % MAX_Fila;    // atualiza circulamente o indice inicio
    f->total--; // Decrementa  contagem de elementos
    return 1;
}

// Função mostrar a fila 
void mostrarFila (Fila *f) {
    printf("Fila: ");
    if (f->total == 0) {
        printf("(vazia)");
    }
    int idx = f->inicio;
    for (int i = 0; i < f->total; i++) {
        printf("[ %c , %d ] ", f->itens[idx].tipo, f->itens[idx].id);
        idx = (idx + 1) % MAX_Fila;
    }    
    printf("\n");
}


// Criação da struct pilha com seu indice topo, e o total de elementos que serão 3
typedef struct {
    Peca elementos[MAX_Pilha];
    int topo;
} Pilha;

// Função que inicializa a pilha com -1 o topo para indicar que a pilha estará vazia
void inicializarPilha(Pilha *p){
    p->topo = -1;
}

// Função que verifica se a pilha está cheia
int PilhaCheia(Pilha *p) {
    return p->topo == MAX_Pilha - 1;
}

// Função que verifica se a pilha está VAZIA, comparando o topo com o -1 (vazia)
int PilhaVazia(Pilha *p) {
    return p->topo == -1;
}

// Função de inserir (PUSH)
int push(Pilha *p, Peca peca) {
    if (PilhaCheia(p)) {
        printf("Pilha Cheia. Não é possível inserir. \n");
        return 0;
    }
    p->topo++; // Incrementa +1 indice no topo
    p->elementos[p->topo] = peca; // insere o elemento no topo
    return 1;
}

// Função de remover o topo (pop)
int pop(Pilha *p, Peca *removida) {
    if (PilhaVazia(p)) {
        printf("Pilha Vazia");
        return 0; // Evita a remoção se estiver vazia
    }
    if (removida) {
        *removida = p->elementos[p->topo];   // grava a peça removida antes da atualização do topo
    }
    p->topo--; // Decrementa -1 indice no topo
    return 1;
}

// Função mostrar a pilha
void mostrarPilha(Pilha *p) {
    printf("Pilha (topo -> base): ");
    if (PilhaVazia(p)) {
        printf("(vazia)\n");
        return;
    }
    for (int i = p->topo;i >= 0; i--) {
        printf("[ %c , %d] ",p->elementos[i].tipo,p->elementos[i].id);
    }
    printf("\n");
}


// FUnção para gerar a peça de cada item
Peca gerarPeca(int proximoId, const char tipos[], int nTipos) {
    Peca p;
    p.tipo = tipos[rand() % nTipos];
    p.id = proximoId;
    return p;
}

// Troca a peça da frente da fila com o topo da pilha
int trocarFrenteComTopo(Fila *f, Pilha *p) {
    if (filaVazia(f) || PilhaVazia(p)) {
        return 0;
    }
    int idxFrente = f->inicio;
    Peca tmp = f->itens[idxFrente];
    f->itens[idxFrente] = p->elementos[p->topo];
    p->elementos[p->topo] = tmp;
    return 1;
}

// Troca os 3 primeiros da fila com as 3 da pilha (exatamente 3 na pilha, ao menos 3 na fila)
int trocarTres(Fila *f, Pilha *p) {
    if (p->topo != 2 || f->total < 3) { // topo==2 => exatamente 3 elementos
        return 0;
    }
    for (int k = 0; k < 3; k++) {
        int idxFila = (f->inicio + k) % MAX_Fila;
        Peca tmp = f->itens[idxFila];
        f->itens[idxFila] = p->elementos[p->topo - k];
        p->elementos[p->topo - k] = tmp;
    }
    return 1;
}

// -------------------------
// Programa principal
// -------------------------

int main(void) {

    // Inicializa a semente
    srand((unsigned)time(NULL));

    Fila f;
    Pilha p;

    inicializarFila(&f); // Inicializar fila
    inicializarPilha(&p); // Inicializar pilha
    
    // Tipos de peças possíveis
    const char tipos[] = {'I','L','O','T'};
    const int nTipos = (int)(sizeof(tipos) / sizeof(tipos[0]));
    
    
    int proximoId = 1;
    
    // Preenche a fila inicial
    while (!filaCheia(&f)) {
        Peca nova = gerarPeca(proximoId++, tipos, nTipos);
        InserirPeca(&f, nova);
    }

    printf("Estado inicial:\n");
    mostrarFila(&f);
    mostrarPilha(&p);

    int opcao;
    do {
        printf("\n1 - Jogar peça (dequeue)\n");
        printf("2 - Enviar peça da fila para a reserva (pilha) \n");
        printf("3 - Usar peça da reserva (remover do topo da pilha)\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar 3 primeiros da fila com as 3 da pilha\n");
        printf("0. Sair\n");     
        printf("Escolha uma das opções: ");
        if (scanf("%d", &opcao) != 1) {
            // Limpa entrada inválida
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
        }

        switch (opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            case 1:
                {
                    // Jogar peça: remove da fila e repõe uma nova para manter 5
                    Peca jogada;
                    if (!removerFila(&f, &jogada)) {
                        printf("Fila vazia. Não há peça para jogar.\n");
                    } else {
                        printf("Jogou peça: [ %c , %d ]\n", jogada.tipo, jogada.id);
                        Peca nova = gerarPeca(proximoId++, tipos, nTipos);
                        InserirPeca(&f, nova);
                    }
                    mostrarFila(&f);
                    mostrarPilha(&p);
                } break;
            case 2: {
                // Enviar peça da fila para a pilha de reserva
                if (PilhaCheia(&p)) {
                    printf("Pilha cheia. Não é possível enviar peça para reserva.\n");
                } else if (filaVazia(&f)) {
                    printf("Fila vazia. Não há peça para enviar à reserva.\n");
                } else {
                    Peca frente;
                    removerFila(&f, &frente);
                    push(&p, frente);
                    printf("Enviada à reserva: [ %c , %d ]\n", frente.tipo, frente.id);
                    // Repor fila para manter 5
                    Peca nova = gerarPeca(proximoId++, tipos, nTipos);
                    InserirPeca(&f, nova);
                }
                mostrarFila(&f);
                mostrarPilha(&p);
            } break;

            case 3: {
                // Usar peça da reserva (retirar do topo)
                Peca usada;
                if (!pop(&p, &usada)) {
                    printf("Pilha vazia. Não há peça na reserva.\n");
                } else {
                    printf("Usou peça da reserva: [ %c , %d ]\n", usada.tipo, usada.id);
                }
                // A fila permanece com 5; não precisa repor aqui
                mostrarFila(&f);
                mostrarPilha(&p);
            } break;

            case 4: {
                // Troca frente da fila com topo da pilha
                if (!trocarFrenteComTopo(&f, &p)) {
                    printf("Não foi possível trocar. Verifique se a fila não está vazia e a pilha possui ao menos 1 peça.\n");
                } else {
                    printf("Troca realizada: frente da fila <-> topo da pilha.\n");
                }
                mostrarFila(&f);
                mostrarPilha(&p);
            } break;

            case 5: {
                // Troca 3 primeiros da fila com as 3 peças da pilha
                if (!trocarTres(&f, &p)) {
                    printf("Não foi possível trocar 3. A pilha precisa ter exatamente 3 peças e a fila ao menos 3.\n");
                } else {
                    printf("Troca de 3 realizada: primeiros da fila <-> pilha completa.\n");
                }
                mostrarFila(&f);
                mostrarPilha(&p);
            } break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}


   


