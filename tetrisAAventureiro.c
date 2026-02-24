#include <stdint.h>
#include <stdlib.h>
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
}FilaCircular;

//Pilha linear
typedef struct 
{
    Peca itens[MAX_PILHA];
    int topo;
} PilhaReserva;

// Funçoes auxiliares
Peca gerarPeca()
{
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.tipo = tipos[rand() % 4];
    nova.id = rand() % 900 + 100;
    return nova;
}

void iniciaLizarFila(FilaCircular *f)
{
    f->frente = 0; 
    f->fim = -1; 
    f->total = 0;
    for(int i = 0; i < TAM_FILA; i++); {
        f->fim = (f->fim + 1) % TAM_FILA;
        f->itens[f->fim] = gerarPeca();
        f->total++;
    }

}

void iniciaLizarPilha(PilhaReserva *p)
{
    p->topo = -1; //A pilha começa vazia
}

void exibirEstado(FilaCircular f, PilhaReserva p) 
{
    printf("\n==== PROXIMAS PEÇAS (FILA) ====\n");
    int idx = f.frente;
    for(int i = 0; i < f.total; i++) {
        printf("[%c] ", f.itens[idx].tipo);
        idx = (idx + 1) % TAM_FILA;
    }

    printf("\n\n==== RESERVA (PILHA - Max 3) ====\n");
    if(p.topo == -1) printf("[ Vazia ]");
    else {
        for(int i = p.topo; i >= 0; i--) {
            printf("| %c | (ID: %d)\n", p.itens[i].tipo, p.itens[i].id);
        }

    }
    printf("\n==================================\n");
}

//Funçoes do jogo

void jogarPeca(FilaCircular *f)
{
    Peca removida = f->itens[f->frente];
    printf("\n VOCE JOGOU A PEÇA: %c\n", removida.tipo);
    f->frente = (f->frente + 1) % TAM_FILA;
    //Reposiçao auttomatica ao final
    f->fim = (f->fim + 1) % TAM_FILA;
    f->itens[f->fim] = gerarPeca();
}

void reservarPeca(FilaCircular *f, PilhaReserva *p) {
    if(p->topo >= MAX_PILHA - 1) 
    {
        printf("\n[!] ERRO: Reserva cheia!\n");
        return;
    }
    // Tira da frente da fila
    Peca paraReserva = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM_FILA;
    
    // Push na Pilha
    p->topo++;
    p->itens[p->topo] = paraReserva;
    
    // Repõe a fila
    f->fim = (f->fim + 1) % TAM_FILA;
    f->itens[f->fim] = gerarPeca();
    
    printf("\n>> PECA %c ENVIADA PARA RESERVA.\n", paraReserva.tipo);
}

void usarReserva(PilhaReserva *p) 
{
    if(p->topo == -1) {
        printf("\n[!] ERRO: Nao ha pecas na reserva!\n");
        return;
    }
    // Pop da Pilha
    Peca resgatada = p->itens[p->topo];
    p->topo--;
    printf("\n>> VOCE USOU A PECA RESERVADA: %c\n", resgatada.tipo);
}

int main() {
    srand(time(NULL));
    FilaCircular f;
    PilhaReserva p;
    int opcao;

    inicializarFila(&f);
    inicializarPilha(&p);

    do {
        exibirEstado(f, p);
        printf("\nMENU - NIVEL AVENTUREIRO\n");
        printf("1 - Jogar peca da fila\n");
        printf("2 - Reservar peca (Push)\n");
        printf("3 - Usar peca reservada (Pop)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: jogarPeca(&f); break;
            case 2: reservarPeca(&f, &p); break;
            case 3: usarReserva(&p); break;
        }
    } while(opcao != 0);

    return 0;
}


