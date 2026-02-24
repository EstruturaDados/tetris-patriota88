#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5
#define MAX_PILHA 3

typedef struct 
{
    char tipo;
    int id;
} Peca;

typedef struct 
{
    Peca itens[TAM_FILA];
    int frente, fim, total;
} FilaCircular;

typedef struct 
{
    Peca itens[MAX_PILHA];
    int topo;
}PilhaReserva;

//Funçoes de apoio
Peca gerarPeca() {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = rand() % 900 + 100;
    return nova;
}

void iniciaLizar(FilaCircular *f, PilhaReserva *p) {
    f->frente = 0;
    f->fim = -1;
    f->total = 0;
    for(int i = 0; i < TAM_FILA; i++) {
        f->fim = (f->fim + 1) % TAM_FILA;
        f->itens[f->fim] = gerarPeca();
        f->total++;
    }
}

void exibirEstado(FilaCircular f, PilhaReserva p) {
    printf("\n==== FILA (Frente -> Fim) ====\n");
    int idx = f.frente;
    for(int i = 0; i < f.total; i++) {
        printf("[%c] ", f.itens[idx].tipo);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n\n==== PILHA (Reversa) ====\n");
    if(p.topo == -1) printf("[ Vazia ]\n");
    else {
        for(int i = p.topo; i >= 0; i--) printf("| %c |\n", p.itens[i].tipo);
    }
    printf("===========================\n");
}

//Funçoes principais
void trocarPeca(FilaCircular *f, PilhaReserva *p) {
    if(p->topo == -1) {
        printf("\n[!] ERRO: Pilha vazi! Nao ha o que trocar.\n");
        return;
    }
    // Troca o topo da pilha com a frente da fila
    Peca temp = p->itens[p->topo];
    p->itens[p->topo] = f->itens[f->frente];
    f->itens[f->frente] = temp;
    printf("\n>>> PEÇAS TROCADAS COM SUCESSO!\n");
}

void inverterFila(FilaCircular *f) {
    //Para inverter a fila
    Peca aux[TAM_FILA];
    int t = 0;

    //Desempilha a fila
    while(f->total > 0) 
    {
        aux[t++] = f->itens[f->frente];
        f->frente = (f->frente + 1) % TAM_FILA;
        f->total--;
    }
    
    //Reinsere na fila
    for(int i = 0; i < t; i++) {
        f->fim = (f->fim + 1) % TAM_FILA;
        f->itens[f->fim] = aux[t - 1 - i];
        f->total++;
    }
    printf("\n >>> FILA INVERTIDA!\n");
}

void jogarPeca(FilaCircular *f) {
    printf("\n>>> JOGOU: %c\n", f->itens[f->frente].tipo);
    f->frente = (f->frente + 1) % TAM_FILA;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->itens[f->fim] = gerarPeca();
}

void reservarPeca(FilaCircular *f, PilhaReserva *p) {
    if(p->topo >= MAX_PILHA - 1) {
        printf("\n[!] ERRO: Reserva cheia!\n");
        return;
    }
    Peca p_reserva = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    p->topo++;
    p->itens[p->topo] = p_reserva;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->itens[f->fim] = gerarPeca();
    printf("\n>>> %c RESERVADA.\n", p_reserva.tipo);
}

int main() {
    srand(time(NULL));
    FilaCircular f; PilhaReserva p;
    int opcao;
    iniciaLizar(&f, &p);

    do {
        exibirEstado(f, p);
        printf("\nMENU MESTRE - TETRIS STACK\n");
        printf("1. Jogar peça\n");
        printf("2. Reservar peça\n");
        printf("3. Usar reserva\n");
        printf("4. Trocar (Topo pilha <-> Frente fila)\n");
        printf("5. Inverter fila\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        printf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            jogarPeca(&f);
            break;
        case 2:
            reservarPeca(&f, &p);
            break;
        case 3:
            if(p.topo != -1) printf("\n>>> Usou Reserva: %c\n", p.itens[p.topo--].tipo);
            else printf("\n[!] Pilha Vazia!\n");
            break;
        case 4:
            trocarPeca(&f, &p);
            break;
        case 5:
            inverterFila(&f);
            break;        
        }
    }while (opcao != 0);
   
    return 0;

}